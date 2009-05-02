// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\baro_UT_helper.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include "classics\new.h"
#include "classics\pointers.h"
#include "classics\thread.h"
#include "ratwin\tasking\CriticalSection.h"
#include "ratwin\utilities.h"
#include "classics\exception.h"
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using namespace ratwin::tasking;
const int iteration_count= 1000;
const int thread_count= 4; // how many threads
const int asize= 100;
__declspec(thread) int myID;
classics::atomic_counter<int> id= 0;

bool verbose= false;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class lock {
   static CRITICAL_SECTION cs;
public:
   static void init() { InitializeCriticalSection (cs); }
   lock() { EnterCriticalSection (cs); }
   ~lock() { LeaveCriticalSection (cs); }
   };
   
CRITICAL_SECTION lock::cs;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct log_t {
   enum type_t { destruct, accept, reject }  rectype;
   const void* ref;
   int thread_ID;
   };

// =============================================

const int max_log_size= iteration_count*thread_count+asize;
log_t Log[max_log_size];
classics::atomic_counter<int> logpos= 0;

// =============================================

void logit (log_t::type_t type, const classics::lifetime* ref)
 {
 log_t& x= Log[logpos++];
 x.thread_ID= myID;
 x.rectype= type;
 x.ref= ref;
 }

// =============================================

void dumplog()
 {
 const char* names[3]= {"destruct", "accept", "reject" };
 for (int loop= 0;  loop < logpos;  loop++) {
    log_t& x= Log[loop];
    const char* s= names[x.rectype];
    cout << loop << ". (" << x.thread_ID << ") " << x.ref << ' ' << s << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_object : public classics::can_handle {
   test_object (const test_object&);  //can't copy
   void operator= (const test_object&);  //can't assign
public:
   static classics::atomic_counter<int> instances;
   test_object() { ++instances; }
   ~test_object();
   void report() const;
   };

classics::atomic_counter<int> test_object::instances= 0;

// =============================================

test_object::~test_object()
 {
 logit (log_t::destruct, get_lifetime_object());
 --instances; 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int random (int range)
 {
 static int holdrand= 1;
 int x= (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
 return x % range;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class cruncher {
   const int asize;
   classics::handle<test_object>* array;
   classics::baro<test_object>* brray;
   void borrow (int);
public:
   explicit cruncher (int size);
   cruncher (const cruncher&);
   ~cruncher();
   void start();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher::~cruncher()
 {
 for (int loop= 0;  loop < asize;  loop++) {
    array[loop]= 0;
    brray[loop]= classics::baro<test_object>(0);
    }
 delete[] array;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void cruncher::borrow (int index)
 {
 try {
    if (!brray[index])  return;
    classics::handle<test_object> p (brray[index]);
    classics::lifetime* L= p->get_lifetime_object();
    logit (log_t::accept, L);
    }
 catch (classics::exception&) {
    const classics::lifetime* L= brray[index].get_lifetime_object();
    logit (log_t::reject, L);
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void cruncher::start()
 {
 myID= ++id;
 for (int loop= 0;  loop < iteration_count;  loop++) {
    array[random(asize)]= array[random(asize)];
    brray[random(asize)]= brray[random(asize)];
    brray[random(asize)]= array[random(asize)];  //new baro from handle
    borrow (random(asize));
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher::cruncher (int size)
 : asize (size)
 {
 array= new classics::handle<test_object> [asize];
 brray= new classics::baro<test_object> [asize];
 for (int loop= 0;  loop < asize;  loop++) {
    array[loop]= new test_object;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher::cruncher (const cruncher& other)
 : asize (other.asize)
 {
 array= new classics::handle<test_object> [asize];
 brray= new classics::baro<test_object> [asize];
 for (int loop= 0;  loop < asize;  loop++) {
    array[loop]= other.array[loop];
    brray[loop]= brray[loop];
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main (int argc, char* argv[])
 {
 if (argc != 2 || *argv[1] != '+') {
    cout << "baro_UT_helper.cxx -- smart pointer baro thread safety" << endl;
    cout << "run baro_UT.perl instead, to invoke this program and analyse the output." << endl;
    return 1;
    }
 lock::init();
 cruncher* testers[thread_count];
 testers[0]= new cruncher(asize);
 int loop;
 for (loop= 1;  loop < thread_count;  loop++)
    testers[loop]= new cruncher (*testers[0]);
 if (verbose)
    cout << "(1) There are " << test_object::instances << " objects." << endl;
 // perform the processing
 ratwin::types::Kernel_HANDLE handles[thread_count];
 for (loop= 0;  loop < thread_count;  loop++) {
    handles[loop]= classics::launch_thread (*testers[loop]);
    }
 ratwin::tasking::WaitForMultipleObjects (thread_count, handles, true);
 // check to see if it made a mess
 if (verbose) {
    cout << iteration_count << " iterations on " << thread_count << " threads." << endl;
    cout << "(2) There are " << test_object::instances << " objects remaining." << endl;
    }
 for (loop= 0;  loop < thread_count;  loop++)
    delete testers[loop];
 if (verbose)
    cout << "(3) There are " << test_object::instances << " objects remaining." << endl;
 if (test_object::instances != 0)
    std::cerr << "** FAILED **  baro_UT_helper reports constructor/destructor count is not ballanced" << endl;
 if (verbose)
    cout << "normal exit." << endl;
 dumplog();
 return 0;
 }
 

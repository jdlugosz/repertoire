// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\handle_UT.cxx
// Revision: public build 8, shipped on 11-July-2006

#include "classics\new.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "classics\exception.h"
#include "classics\string_ios.h"
#include <iostream>
using std::cout;
using std::endl;
using classics::ulong;

#if !defined NOTHREAD
#include "classics\critical_section.h"
#include "ratwin\utilities.h"
#include "classics\thread.h"
using classics::critical_section;
#endif

int errorcount= 0;
bool verbose= false;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// stuff used for test1 (simple)
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


class testclass : public classics::debug_can_handle, public classics::debug::noisy1 {   };


void report_life_count()
 {
 cout << "Lifetime Object count: " << classics::debug_can_handle::object_count << endl;
 }


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 typedef classics::const_handle<testclass> ht;
 cout << "test 1 -- basic sanity check.\n";
 try {
    ht p1;
    ht p2 (new testclass);
    report_life_count();
    p1= p2;
    p2= 0;
    report_life_count();
    if (!p1) {  // call operator!
       cout << "failed number 1.2" << endl;
       ++errorcount;
       }
    if (p2) { // call operator bool
       cout << "failed number 1.3" << endl;
       ++errorcount;
       }
    const ht cp2= p2;
    bool b= cp2;
    if (b) { // call operator bool on const object
       cout << "failed number 1.3" << endl;
       ++errorcount;
       }
    }
 catch (...) {
    cout << "* failed: exception thrown during test 1" << endl;
    ++errorcount;
    }
 cout << "note: ctor/dtor calling not automatically verified." << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// stuff used for tests 2 through 6 (real crunching)
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

enum {
   copy_ctor= 1,
   const_foo= 2,
   non_const_foo= 4,
   dtor= 8,
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_object : public classics::debug_can_handle {
   static ulong dump;
   ulong* flags;
public:
   int reference_count() const { return get_reference_count(); }
   int borrow_count() const { return get_lifetime_object()->unowned_count; }
   test_object (ulong* flags) : flags(flags) {}
   test_object() : flags (&dump) {}
   test_object (const test_object& other) : flags(&dump) {}
   virtual ~test_object() { *flags |= dtor; }
   test_object& operator= (const test_object&);
   void set_flag_location (ulong* p) { flags= p; }
   void foo() const  { *flags |= const_foo; }
   void foo()  { *flags |= non_const_foo; }
   virtual test_object* clone() const  { return new test_object(*this); }
   virtual int ID() const { return 1; }
   };

ulong test_object::dump= 0;

class derived_object : public test_object {
public:
   test_object* clone() const  { return new derived_object(*this); }
   int ID() const { return 2; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const int flagcount =10;
ulong flags[flagcount];  //all zero initially
ulong oldflags[flagcount];  //remember the "before" state

typedef classics::const_handle<test_object> const_handle;
typedef classics::handle<test_object> handle;
typedef classics::cow<test_object> cow;

void verify (int number, int index, ulong changes)
 {
// if (oldflags[index] | changes != flags[index])
 if ((oldflags[index] | changes) != flags[index])
    cout << "failed number " << number << endl;
 oldflags[index]= flags[index];
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test2()
 {
 cout << "test 2 -- reference counting with create/destroy/assign" << endl;
 const_handle h1 (new test_object (flags+0));
 h1->foo();  //should call const form
 verify (1, 0, const_foo);
 const_handle h2 (h1);  //copy constructor
 // h1 and h2 should point to same test object
 if (h1->reference_count() != 2 || h2->reference_count() != 2) {
    cout << "failed 2.1" << endl;
    ++errorcount;
    }
 const_handle h3 (new test_object (flags+1));
 h2= h3;  //first object down to 1, second object up to 2.
 if (h1->reference_count() != 1 || h3->reference_count() != 2) {
    cout << "failed number 2.2" << endl;
    ++errorcount;
    }
 h2= 0;
 if (h1->reference_count() != 1 || h3->reference_count() != 1) {
    cout << "failed number 2.3" << endl;
    ++errorcount;
    }
 h3= h3;    //should be no change
 verify (5, 1, 0);  //make sure no additional flags were turned on
 if (h1->reference_count() != 1 || h3->reference_count() != 1) {
    cout << "failed number 2.4" << endl;
    ++errorcount;
    }
 h3= h1;
 verify (7, 1, dtor);
 if (h3->reference_count() != 2) {
    cout << "failed number 2.5" << endl;
    ++errorcount;
    }
 h3= h1= 0;
 verify (9, 0, dtor);
 cout << "Lifetime Use Count: " << classics::lifetime::get_pool_use_count() << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void t3_helper (const_handle& x)
 {
 x->foo();  //const form.
 verify (11, 2, const_foo);
 }

void test3()
 {
 cout << "test 3 -- const/non-const semantics" << endl;
 handle h1 (new test_object (flags+2));
 h1->foo();  //should call non-const
 verify (10, 2, non_const_foo);

 // handle to const_handle reference
 t3_helper (h1);
 // handle to const_handle by copy constructor
 const_handle h2 (h1);
 if (h1->reference_count() != 2) {
    cout << "failed 3.1" << endl;
    ++errorcount;
    }
 // handle to const_handle by assignment
 handle h3 (new test_object (flags+3));
 h2= h3;
 if (h1->reference_count() != 1 || h3->reference_count() != 2) {
    cout << "failed 3.2" << endl;
    ++errorcount;
    }
 h1= 0;
 // this should be rejected by the compiler
 /*  h3= h2;  */
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test4()
 {
 cout << "test 4 -- test copy-on-write semantics" << endl;
 cow h1 (new test_object (flags+4));
 cow h2= h1;
 if (h1.const_object()->reference_count() != 2) {
    cout << "failed 4.1" << endl;
    ++errorcount;
    }
 h1->foo();
 verify (15, 4, 0);  //does NOT call foo on flags+4.
 if (h1.const_object()->reference_count() != 1 || h2.const_object()->reference_count() != 1) {
    cout << "failed 4.2" << endl;
    ++errorcount;
    }
 // test polymorphism on contained objects
 cow h3 (new derived_object);
 cow h4= h3;
 if (h4->ID() != 2) {
    // duplicates, then calls ID on the copy.
    cout << "failed 4.3" << endl;
    ++errorcount;
    }
 // assignment operator different for cow's, so test that separately.
 h1= h2;
 if (!h1.points_to (h2)) {
    cout << "failed 4.4" << endl;
    ++errorcount;
    }
 test_object* p1= new test_object;
 h1= p1;
 if (!h1.points_to(p1)) {
    cout << "failed 4.5" << endl;
    ++errorcount;
    }
 const_handle h5 (h1);  // construct const_handle from cow
 h5= h2;  // assignment operator
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

typedef classics::const_baro<test_object> const_baro;

void test5()
 {
 cout << "test 5 -- test semantics of borrowers" << endl;
 const_handle h1 (new test_object (flags+5));
 const_baro b1 (h1);
 if (h1->reference_count() != 1 || h1->borrow_count() != 1) {
    cout << "failed 5.1" << endl;
    ++errorcount;
    }
 if (true) {
    const_handle temp (b1);  //claim the borrower for use
    if (h1->reference_count() != 2 || h1->borrow_count() != 1) {
       cout << "failed 5.2" << endl;
      ++errorcount;
       }
    }
 if (h1->reference_count() != 1 || h1->borrow_count() != 1) {
    cout << "failed 5.3" << endl;
    ++errorcount;
    }
 const_baro b2;
 b2= b1;  //test assignment
 if (h1->reference_count() != 1 || h1->borrow_count() != 2) {
    cout << "failed 5.4" << endl;
    ++errorcount;
    }

 h1= 0;
 try {
    const_handle temp (b1);  //claim the borrower for use
    cout << "failed 5.5" << endl;  //can't do that!
    ++errorcount;
    }
 catch (classics::exception& X) {
    cout << "exception caught (as expected):\n";
    X.show();
    }
 // compiler should reject this:
 //-- handle h2 (b1);  //can't get a non-const handle from a const baro

 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test6()
 {
 cout << "test 6 -- owning borrowers" << endl;
 const_handle h1 (new test_object (flags+6));
 const_baro b1 (h1);
 if (h1->reference_count() != 1 || h1->borrow_count() != 1) {
    cout << "failed 6.1" << endl;
    ++errorcount;
    }
 b1.own(true);
 if (h1->reference_count() != 2 || h1->borrow_count() != 1) {
    cout << "failed 6.2" << endl;
    ++errorcount;
    }
 {
 const_baro b2 (b1);
 if (h1->reference_count() != 3 || h1->borrow_count() != 2) {
    cout << "failed 6.3" << endl;
    ++errorcount;
    }
 b1= b2;
 if (h1->reference_count() != 3 || h1->borrow_count() != 2) {
    cout << "failed 6.4" << endl;
    ++errorcount;
    }
 b1.own(false);
 if (h1->reference_count() != 2 || h1->borrow_count() != 2) {
    cout << "failed 6.5" << endl;
    ++errorcount;
    }
 b1= b2;
 if (h1->reference_count() != 3 || h1->borrow_count() != 2) {
    cout << "failed 6.6" << endl;
    ++errorcount;
    }
 } // b2 is destructed.
 if (h1->reference_count() != 2 || h1->borrow_count() != 1) {
    cout << "failed 6.7" << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int usecount;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check_leaks()
 {
 int newcount= classics::lifetime::get_pool_use_count();
 int leaks= newcount - usecount;
 if (leaks != 0) {
    cout << "possible leak: " << leaks << " lifetime objects remain behind.\n";
    usecount= newcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void callback (int mode, void* p)
 {
 static bool internal= false;
 static int counter= 0;
 counter++;
 switch (mode) {
    case 1:
       if (!internal)  cout << "mem " << p << " alloc [" << counter << "]\n";
       break;
    case 2:
       if (!internal)  cout << "mem " << p << " free  [" << counter << "]\n";
       break;
    case 3:
       internal= true;
       break;
    case 4:
       internal= false;
       break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct node {
   node* next;
   };

unsigned find_checksum (node* p)
 {
 unsigned sum= 0;
 while (p) {
    sum += unsigned (p);
    p= p->next;
    }
 return sum;
 }

// ==========================================

void validate (unsigned checksum, node* top, int LINE)
 {
 if (checksum != find_checksum (top)) {
    throw "OOps!";  //keep it simple, to avoid recursive failures!
    }
 }

// ==========================================

void fmp_friendly_callback (int mode, void* p)
 {
 static classics::general_static_fixed_memory_pool<>& Pool= classics::lifetime::pool;
 static unsigned checksum= 0;
 if (!checksum) {
    checksum= find_checksum (reinterpret_cast<node*>(Pool.get_nodelist()));  // rebuild.
    }
 switch (mode) {
    case 1:  //allocate
       // I just removed this node.
       checksum -= unsigned(p);
       validate (checksum, reinterpret_cast<node*>(Pool.get_nodelist()), __LINE__);
       break;
    case 2:  // free
       // I'm about to add this node.
       validate (checksum, reinterpret_cast<node*>(Pool.get_nodelist()), __LINE__);
       checksum += unsigned(p);
       break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
//  test 7 (thread safety) infrastructure
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
#if !defined NOTHREAD

using namespace ratwin::tasking;
const int iteration_count= 1000000;
const int thread_count= 6; // how many threads

int fromlog[iteration_count*thread_count];
int tolog[iteration_count*thread_count];
classics::atomic_counter<int> logpos (0);

critical_section cs;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class noisy1;
classics::atomic_counter<int> concount= 0;
classics::atomic_counter<int> decount= 0;
noisy1* constructed[10];
noisy1* destructed[10];

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class noisy1 {
protected:
   noisy1();
   ~noisy1();
   noisy1 (const noisy1& other);
   };

noisy1::noisy1()
 {
 if (verbose) {
    critical_section::locker k (cs);
    cout << "constructing test object at " << this << endl;
    }
 constructed[concount++] = this;
 }


noisy1::~noisy1()
 {
 if (verbose) {
    critical_section::locker k (cs);
    cout << "destructing test object at  " << this << endl;
    }
 destructed[decount++] = this;
 ratwin::util::Sleep(1);
 }


noisy1::noisy1 (const noisy1& other)
 {
 if (verbose) {
    critical_section::locker k (cs);
    cout << "copying test object to " << this << " from " << (void*)(&other) << endl;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class thread_test_object : public classics::can_handle, public noisy1 {
   thread_test_object (const thread_test_object&);  //can't copy
   void operator= (const thread_test_object&);  //can't assign
public:
   static classics::atomic_counter<int> instances;
   thread_test_object() { ++instances; }
   ~thread_test_object() { --instances; }
   // >> not "logging" destruction as in test16.cxx
   void report() const;
   };

classics::atomic_counter<int> thread_test_object::instances= 0;


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void thread_test_object::report() const
 {
 const classics::lifetime* L= get_lifetime_object();
 cout << "\towned_count= " << L->owned_count << endl;
 cout << "\tunowned_count= " << L->unowned_count << endl;
 cout << "\thold= " << L->hold << endl;
 cout << "\tdeleted= " << L->deleted << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int random (int range)
 {
 static int holdrand= 1;
 int x= (((holdrand = holdrand * 214013L + 2531011L) >> 16) & 0x7fff);
 return x % range;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class cruncher1 {
   const int asize;
   classics::handle<thread_test_object>* array;
public:
   explicit cruncher1 (int size);
   cruncher1 (const cruncher1&);
   ~cruncher1();
   void start();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher1::~cruncher1()
 {
 for (int loop= 0;  loop < asize;  loop++)  array[loop]= 0;
 delete[] array;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void cruncher1::start()
 {
 for (int loop= 0;  loop < iteration_count;  loop++) {
    const int src= random(asize);
    const int dest= random(asize);
    array[dest]= array[src];
    int pos= logpos++;
    fromlog[pos]= src;
    tolog[pos]= dest;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher1::cruncher1 (int size)
 : asize (size)
 {
 array= new classics::handle<thread_test_object> [asize];
 for (int loop= 0;  loop < asize;  loop++) {
    array[loop]= new thread_test_object;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cruncher1::cruncher1 (const cruncher1& other)
 : asize (other.asize)
 {
 array= new classics::handle<thread_test_object> [asize];
 for (int loop= 0;  loop < asize;  loop++) {
    array[loop]= other.array[loop];
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool surviving (const noisy1* p)
 {
 for (int loop= 0;  loop < decount;  loop++)
    if (p == destructed[loop])  return false;
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void post_mortem()
 {
 for (int loop= 0;  loop < 10;  loop++) {
    noisy1* object= constructed[loop];
    if (surviving(object)) {
       cout << "reporting on " << object << endl;
       thread_test_object* p= static_cast<thread_test_object*>(object);
       p->report();
       }
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void show_log()
 {
 for (int loop= 0;  loop < logpos;  loop++) {
    cout << "  assigned to #" << tolog[loop] << " from #" << fromlog[loop] << endl;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test7()
 {
 cout << "test 7 -- smart pointer thread safety" << endl;
 cruncher1* testers[thread_count];
 testers[0]= new cruncher1(10);
 int loop;
 for (loop= 1;  loop < thread_count;  loop++)
    testers[loop]= new cruncher1 (*testers[0]);
 cout << "(1) There are " << thread_test_object::instances << " objects." << endl;
 // perform the processing
 ratwin::types::Kernel_HANDLE handles[thread_count];
 for (loop= 0;  loop < thread_count;  loop++) {
    handles[loop]= classics::launch_thread (*testers[loop]);
    }
 ratwin::tasking::WaitForMultipleObjects (thread_count, handles, true);
 // check to see if it made a mess
 cout << iteration_count << " iterations on " << thread_count << " threads." << endl;
 cout << "(2) There are " << thread_test_object::instances << " objects remaining." << endl;
 for (loop= 0;  loop < thread_count;  loop++)
    delete testers[loop];
 cout << "(3) There are " << thread_test_object::instances << " objects remaining." << endl;
 if (thread_test_object::instances != 0) {
    cout << "** FAILED **" << endl;
    ++errorcount;
    }
// show_log();
// post_mortem();
// un-comment the above two calls for troubleshooting in case a
// problem is actually detected.
 }

#endif

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class backref : public classics::debug_can_handle {
   classics::baro<test_object> x;
public:
   backref (test_object* x) : x(x) {}
   };

class recursive_test_object : public test_object {
   classics::handle<backref> x;
public:
   recursive_test_object() {
      backref* p= new backref(this);
      x= classics::handle<backref> (p);
      }
   };


int test8_failed= 0;

void test8_callback (int mode, void* p)
 {
 static bool enabled= true;
 switch (mode) {
    case 2:
       if (enabled) {
          // here is what I'm watching for.
          unsigned* q= static_cast<unsigned*>(p);
          if (*q != 0) {
             // this is the owned reference count.  If it's not zero, why are we freeing it?
             // it is also used for the NEXT pointer in the freelist, so a duplicate free will
             // be detected by this test.
             ++test8_failed;
             }
          }
       break;
    case 3:
       enabled= false;
       break;
    case 4:
       enabled= true;
    }
 }

void test8()
 {
 cout << "test 8 -- recursive freeing" << endl;
 classics::lifetime::pool.callback= test8_callback;
 /* extra scope */ {
    handle h1 (new recursive_test_object);
    }
 if (test8_failed) {
    ++errorcount;
    cout << "** FAILED **"<< endl;
    }
 classics::lifetime::pool.callback= 0;  // revoke test8_callback
 }

void test9()
 {
 cout << "test 9 -- test for bad lifetime" << endl;
 try {
    handle xx;
    { // extra scope
       handle h1 (new test_object);
       memcpy (&xx, &h1, sizeof xx);  // !!!!
       }  // h1 is destroyed
//    try {
//       xx->foo();  // problem, as it's already destroyed.  But, never inspects the lifetime object.
//       }
//    catch (...) { cout << "noted foo on bad pointer.\n"; }  // it may or may not; not an issue.
    // now handle xx goes out of scope, causing a problem.
    }
 catch (...) {
    // does assert throw an exception or just terminate?
    cout << "exception caught (as expected)\n";
    return;
    }
 ++errorcount;  // should have caught a problem.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test10()
 {
 cout << "test 10 -- operator==" << endl;
 const int original_errorcount= errorcount;
 classics::handle<recursive_test_object> h1 (new recursive_test_object);
 classics::handle<recursive_test_object> h2 (new recursive_test_object);
 if (h1==h2)  ++errorcount;
 handle h3 (h1);  // uses generalized copy constructor
 if (h1==h3) {
    // tested different declared types pointing to the same complete object
    }
 else ++errorcount;
 const_handle h4 (h1);
 if (h1!=h4)  ++errorcount;
    // tested different declared types pointing to the same complete object
 if (errorcount != original_errorcount)
    cout << "Test 10 failed. " << endl;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
void access_check (T& h)
 {
 // don't have to call this; just make sure the compiler allows visibility to them.
 h.data();
 h.get_lifetime_object();
 h.is_unique();
 typename T::Type* p= 0;
 h.points_to (p);
 }

void access_check()
 {
 handle xx;
 access_check (xx);
 const_handle yy;
 access_check (yy);
 cow zz;
 access_check (zz);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// main program
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main (int argc, char* argv[])
 {
 if (argc == 2 && *argv[1] == 'v')  verbose= true;
 try {
    test1();
    //classics::lifetime::pool.callback= callback;
    // un-comment above line for additional verboseness in troubleshooting
//    classics::lifetime::pool.callback= fmp_friendly_callback;  // another one.
// note: test8 uses a callback as part of the test.  May need to disable test8 if using these global callbacks.
    // all "perminant" lifetime objects are created by this point, so now note how many.
    usecount=  classics::lifetime::get_pool_use_count();
    test2();
    check_leaks();
    test3();
    check_leaks();
    test4();
    check_leaks();
    test5();
    check_leaks();
    test6();
    check_leaks();
    #if !defined NOTHREAD
       test7();
    #else
     cout << "test 7 -- theading test disabled." << endl;
    #endif
    test8();
    check_leaks();
    #ifdef _DEBUG
//    test9();
    #endif
    test10();
    if (errorcount != 0) {
       cout << errorcount << " errors detected." << endl;
       return 10;
       }
    }
 catch (classics::exception& X) {
    cout << "unexpected exception caught:" << endl;
    X.show();
    return 10;
    }
 catch (...) {
    cout << "unknown unexpected exception caught" << endl;
    return 10;
    }
 cout << "All tests passed." << endl;
 return 0;
 }



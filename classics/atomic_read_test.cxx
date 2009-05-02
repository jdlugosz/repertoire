// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_read_test.cxx
// Revision: public build 8, shipped on 11-July-2006

// The purpose of this test is to find out whether reading a machine
// word is atomic on a multi-CPU machine.

#include "classics\new.h"
#include "classics\thread.h"
#include "ratwin\tasking\CriticalSection.h"
#include "ratwin\utilities.h"
#include <iostream>
using std::cout;
using std::endl;
using namespace ratwin::tasking;

volatile unsigned Count= 0;
const int checkpoint= 1000000;  //how often to report
int read_thread_count= 4;
int write_thread_count= 4;
int errors= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// A global critical section for protecting `cout' and 'errors'
class lock {
   static CRITICAL_SECTION cs;
public:
   static void init() { InitializeCriticalSection (cs); }
   lock() { EnterCriticalSection (cs); }
   ~lock() { LeaveCriticalSection (cs); }
   };

CRITICAL_SECTION lock::cs;
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class writer {
   const int ID;
public:
   writer (int ID) : ID(ID) {}
   void start();
   };

// ===========================================

void writer::start()
 {
 int loop=0;
 for (;;) {
    if ((loop & 15)==0)  Count= 0;
    else {
       __asm add Count, 01010101h
       }
    if (++loop % checkpoint == 0) {
       lock k;
       cout << "writer thread " << ID << " iterated " << loop << " times" << endl;
       }
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class reader {
   const int ID;
public:
   reader (int ID) : ID(ID) {}
   void start();
   };

// ===========================================

bool OK (unsigned val)
 {
 const char* const p= reinterpret_cast<char*>(&val);
 return p[0] == p[1] && p[1] == p[2] && p[2] == p[3];
 }
 
// ===========================================

void reader::start()
 {
 using std::hex;
 using std::dec;
 int loop= 0;
 for (;;) {  //loop forever
    int newval= Count;  //unprotected read.
    if (!OK(newval)) {
       lock k;
       cout << "*** ERROR *** thread " << ID << " reads value of " << hex << newval << dec << endl;
       ++errors;
       }
    if (++loop % checkpoint == 0) {
       lock k;
       if (errors)  cout << errors << " errors detected thus far." << endl;
       cout << "thread " << ID << " iterated " << loop << " times, val = " << hex << newval << dec<< endl;
       }
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 cout << "Testing atomic-ness of read operation on this machine.\nPress CTRL-C or BREAK to quit." << endl;
 lock::init();
 int ID= 1;
 int x= read_thread_count > write_thread_count ? read_thread_count : write_thread_count;
 for (int loop= 0;  loop < x;  loop++) {
    if (read_thread_count) {
       read_thread_count--;
       classics::launch_thread (*new reader (ID++));
       }
    if (write_thread_count) {
       write_thread_count--;
       classics::launch_thread (*new writer (ID++));
       }
    }
 ratwin::util::Sleep (0xffffffff);  //user kills with ctrl-C.
 return 0;
 }


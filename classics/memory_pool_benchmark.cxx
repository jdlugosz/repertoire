// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\memory_pool_benchmark.cxx
// Revision: public build 9, shipped on 18-Oct-2006

// This times the classics memory management, relative to the standard manager.

#include "classics\new.h"
#include "classics\profile_timer.h"
#include "classics\fixed_memory_pool.h"
#include <iostream>

using std::cout;
using std::endl;

classics::profile_timer timer;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
T* timetest (const char* caption)
 {
 cout << "running memory benchmark on " << caption << endl;
 const int MAX= 1000;
 const int sweep= 10;
 T* array[MAX];
 timer.reset();
 timer.start();
 for (int iteration= 0;  iteration < 100;  iteration++) {
    int loop= 0;
    while (loop < MAX-sweep) {
       for (int x= 0;  x < sweep;  x++) {
          array[loop+x]= new T(loop+x);
          }
       for (int y= 1;  y < sweep;  y++) {
          delete array[loop+y];
          }
       loop++;
       }
    }
 timer.stop();
 cout << "User time: " << timer.get_user() << ", Kernel time: " << timer.get_kernel() << endl;
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class C1 {
   const void* addr;
   int value;
public:
   C1 (int x) : addr(this), value(x) {}
   };

class C2 : public classics::pool_mixin<C2> {
   const void* addr;
   int value;
public:
   C2 (int x) : addr(this), value(x) {}
   };

class C3 : public classics::ts_pool_mixin<C3> {
   const void* addr;
   int value;
public:
   C3 (int x) : addr(this), value(x) {}
   };


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 timetest<C1> ("regular new/delete");
 timetest<C2> ("fixed pool allocator");
 timetest<C3> ("thread-safe fixed pool allocator");
 return 0;
 }
 



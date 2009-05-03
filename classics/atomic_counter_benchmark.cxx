// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter_benchmark.cxx
// Revision: public build 9, shipped on 18-Oct-2006

#define _CRT_SECURE_NO_DEPRECATE
#include "classics\atomic_counter.h"
#include "classics\profile_timer.h"
#include "classics\critical_section.h"
#include <iostream>

using classics::critical_section;
using std::cout;
using std::endl;

#pragma warning( disable : 4101)  // don't complain about padding variables

static volatile int* global;
static volatile int* global2;
static volatile int* global3;

classics::profile_timer timer;
// ========================================

void regular()
// time regular increment/decrement instructions
 {
 timer.reset();
 volatile int value;
 global= &value;  // name in scope, but now known to "others".
 timer.start();
 for (int loop= 0;  loop < 10000000;  loop++) {
    value++;  //1
    value++;  //2
    value++;  //3
    value++;  //4
    value++;  //5
    value++;  //6
    value++;  //7
    value++;  //8
    value++;  //9
    value++;  //10
    value++;  //1
    value++;  //2
    value++;  //3
    value++;  //4
    value++;  //5
    value++;  //6
    value++;  //7
    value++;  //8
    value++;  //9
    value++;  //20
    value++;  //1
    value++;  //2
    value++;  //3
    value++;  //4
    value++;  //5
    value++;  //6
    value++;  //7
    value++;  //8
    value++;  //9
    value++;  //30
    }
 timer.stop();
 global= 0;  // be kind, rewind!
 double result= (timer.get_user()/1E3) / 3E8;
 cout << "regular memory variable: " << result*1E9 << " nanoseconds" << endl;
 }

// ========================================

void regular_3X()
// time regular increment/decrement instructions
// three different variables interlaced, to check pipelining.
 {
 timer.reset();
 volatile int value1;
 global= &value1;  // name in scope, but now known to "others".
 char padding1[60];  // keep the values on different cache lines
 volatile int value2;
 global2= &value2;  // name in scope, but now known to "others".
 char padding2[60];
 volatile int value3;
 global3= &value3;  // name in scope, but now known to "others".

 timer.start();
 for (int loop= 0;  loop < 10000000;  loop++) {
    value1++;  // 1
    value2++;
    value3++;
    value1++;  // 2
    value2++;
    value3++;
    value1++;  // 3
    value2++;
    value3++;
    value1++;  // 4
    value2++;
    value3++;
    value1++;  // 5
    value2++;
    value3++;
    value1++;  // 6
    value2++;
    value3++;
    value1++;  // 7
    value2++;
    value3++;
    value1++;  // 8
    value2++;
    value3++;
    value1++;  // 9
    value2++;
    value3++;
    value1++;  // 10
    value2++;
    value3++;
    }
 timer.stop();
 global= global2= global3= 0;
 double result= (timer.get_user()/1E3) / 1E8;
 cout << "3 regular memory variables interleaved: " << result*1E9 << " nanoseconds (" << result*1E9/3 << " each)" << endl;
 }
// ========================================

void hand_coded()
// time regular increment/decrement instructions
 {
 timer.reset();
 volatile int value;
 global= &value;  // name in scope, but now known to "others".
 timer.start();
 for (int loop= 0;  loop < 10000000;  loop++) {
    __asm {
       inc [value]  //1
       inc [value]  //2
       inc [value]  //3
       inc [value]  //4
       inc [value]  //5
       inc [value]  //6
       inc [value]  //7
       inc [value]  //8
       inc [value]  //9
       inc [value]  //10
       inc [value]  //1
       inc [value]  //2
       inc [value]  //3
       inc [value]  //4
       inc [value]  //5
       inc [value]  //6
       inc [value]  //7
       inc [value]  //8
       inc [value]  //9
       inc [value]  //20
       inc [value]  //1
       inc [value]  //2
       inc [value]  //3
       inc [value]  //4
       inc [value]  //5
       inc [value]  //6
       inc [value]  //7
       inc [value]  //8
       inc [value]  //9
       inc [value]  //30
       }
    }
 timer.stop();
 global= 0;
 double result= (timer.get_user()/1E3) / 3E8;
 cout << "hand-coded INC memory variable: " << result*1E9 << " nanoseconds" << endl;
 }

// ========================================

void hand_coded_3X()
// time regular increment/decrement instructions
 {
 timer.reset();
 volatile int value1;
 global= &value1;  // name in scope, but now known to "others".
 char padding1[60];  // keep the values on different cache lines
 volatile int value2;
 global2= &value2;  // name in scope, but now known to "others".
 char padding2[60];
 volatile int value3;
 global3= &value3;  // name in scope, but now known to "others".
 timer.start();
 for (int loop= 0;  loop < 10000000;  loop++) {
    __asm {
       inc [value1]  // 1
       inc [value2]
       inc [value3]
       inc [value1]  // 2
       inc [value2]
       inc [value3]
       inc [value1]  // 3
       inc [value2]
       inc [value3]
       inc [value1]  // 4
       inc [value2]
       inc [value3]
       inc [value1]  // 5
       inc [value2]
       inc [value3]
       inc [value1]  // 6
       inc [value2]
       inc [value3]
       inc [value1]  // 7
       inc [value2]
       inc [value3]
       inc [value1]  // 8
       inc [value2]
       inc [value3]
       inc [value1]  // 9
       inc [value2]
       inc [value3]
       inc [value1]  // 10
       inc [value2]
       inc [value3]
       }
    }
 timer.stop();
 global= global2= global3= 0;
 double result= (timer.get_user()/1E3) / 1E8;
 cout << "3 hand-coded INC memory variables: " << result*1E9 << " nanoseconds (" << result*1E9/3 << " each)" << endl;
 }

// ========================================

void atomic_post_increment()
 {
 timer.reset();
 volatile classics::atomic_counter<int> value;
 timer.start();
 for (int loop= 0;  loop < 1000000;  loop++) {
    value++;  //1
    value++;  //2
    value++;  //3
    value++;  //4
    value++;  //5
    value++;  //6
    value++;  //7
    value++;  //8
    value++;  //9
    value++;  //10
    }
 timer.stop();
 double result= (timer.get_user()/1E3) / 1E7;
 cout << "atomic counter post-increment: " << result*1E9 << " nanoseconds" << endl;
 }

// ========================================

void atomic_X3()
 {
 timer.reset();
 volatile classics::atomic_counter<int> value1;
 char padding1[60];  // keep the values on different cache lines
 volatile classics::atomic_counter<int> value2;
 char padding2[60];
 volatile classics::atomic_counter<int> value3;
 timer.start();
 for (int loop= 0;  loop < 1000000;  loop++) {
    value1++;  // 1
    value2++;
    value3++;
    value1++;  // 2
    value2++;
    value3++;
    value1++;  // 3
    value2++;
    value3++;
    value1++;  // 4
    value2++;
    value3++;
    value1++;  // 5
    value2++;
    value3++;
    value1++;  // 6
    value2++;
    value3++;
    value1++;  // 7
    value2++;
    value3++;
    value1++;  // 8
    value2++;
    value3++;
    value1++;  // 9
    value2++;
    value3++;
    value1++;  // 10
    value2++;
    value3++;
    }
 timer.stop();
 double result= (timer.get_user()/1E3) / 1E7;
 cout << "3 atomic counters (post-increment) interleaved: " << result*1E9 << " nanoseconds (" << result*1E9/3 << " each)" << endl;
 }

 // ========================================

 void atomic_pre_increment()
  {
  timer.reset();
  volatile classics::atomic_counter<int> value;
  timer.start();
  for (int loop= 0;  loop < 1000000;  loop++) {
     ++value;  //1
     ++value;  //2
     ++value;  //3
     ++value;  //4
     ++value;  //5
     ++value;  //6
     ++value;  //7
     ++value;  //8
     ++value;  //9
     ++value;  //10
     }
  timer.stop();
  double result= (timer.get_user()/1E3) / 1E7;
  cout << "atomic counter pre-increment: " << result*1E9 << " nanoseconds" << endl;
  }

  // ========================================

  void atomic_inc()
   {
   timer.reset();
   volatile classics::atomic_counter<int> value;
   timer.start();
   for (int loop= 0;  loop < 1000000;  loop++) {
      value.inc();  //1
      value.inc();  //2
      value.inc();  //3
      value.inc();  //4
      value.inc();  //5
      value.inc();  //6
      value.inc();  //7
      value.inc();  //8
      value.inc();  //9
      value.inc();  //10
      }
   timer.stop();
   double result= (timer.get_user()/1E3) / 1E7;
   cout << "atomic counter inc: " << result*1E9 << " nanoseconds" << endl;
 }

// ========================================

critical_section cs;

inline void inc (volatile int& x)
 {
 critical_section::locker lock (cs);
 x++;
 }


void critical()
 {
 timer.reset();
 volatile int value;
 global= &value;  // name in scope, but now known to "others".
 timer.start();
 for (int loop= 0;  loop < 1000000;  loop++) {
    inc(value);  //1
    inc(value);  //2
    inc(value);  //3
    inc(value);  //4
    inc(value);  //5
    inc(value);  //6
    inc(value);  //7
    inc(value);  //8
    inc(value);  //9
    inc(value);  //10
    }
 timer.stop();
 global= 0;
 double result= (timer.get_user()/1E3) / 1E7;
 cout << "critical section: " << result*1E9 << " nanoseconds" << endl;
 }

// ========================================

int main()
 {
 cout << (classics::internal::SingleCPU ? "Single CPU fast-case in use" : "Multi-CPU locking in use") << endl;
 regular();
 regular_3X();
 hand_coded();
 hand_coded_3X();
 atomic_post_increment();
 atomic_X3();
 atomic_pre_increment();
 atomic_inc();
 critical();
 return 0;
 }


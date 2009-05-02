// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter_benchmark.cxx
// Revision: public build 4, shipped on 29-Aug-98

#include "classics\atomic_counter.h"
#include "classics\profile_timer.h"
#include "classics\critical_section.h"
#include <iostream>

using classics::critical_section;
using std::cout;
using std::endl;

classics::profile_timer timer;
// ========================================

void regular()
// time regular increment/decrement instructions
 {
 timer.reset();
 volatile int value;
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
    }
 timer.stop();
 double result= (timer.get_user()/1E3) / 1E8;
 cout << "regular memory variable: " << result*1E9 << " nanoseconds" << endl;
 }
 
// ========================================

void hand_coded()
// time regular increment/decrement instructions
 {
 timer.reset();
 volatile int value;
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
       }
    }
 timer.stop();
 double result= (timer.get_user()/1E3) / 1E8;
 cout << "hand-coded memory variable: " << result*1E9 << " nanoseconds" << endl;
 }
 
// ========================================

void atomic()
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
 cout << "atomic counter: " << result*1E9 << " nanoseconds" << endl;
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
 double result= (timer.get_user()/1E3) / 1E7;
 cout << "critical section: " << result*1E9 << " nanoseconds" << endl;
 }
 
// ========================================

int main()
 {
 regular();
 hand_coded();
 atomic();
 critical();
 return 0;
 }
 

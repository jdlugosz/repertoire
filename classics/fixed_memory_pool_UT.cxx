// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool_UT.cxx
// Revision: public build 5, shipped on 8-April-1999

// test of the fixed_memory_pool

#include "classics\new.h"
#include "classics\fixed_memory_pool.h"
#include <iostream>
using std::cout;
using std::endl;
int errorcount= 0;

class C : public classics::pool_mixin<C> {
   const void* addr;
   int value;
public:
   C (int x) : addr(this), value(x) {}
   void check (int val) const;
   };


void C::check (int val) const
 {
 if (addr != this || value != val) {
    cout << "failed check." << endl;
    ++errorcount;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static C* premain= new C (99);

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 cout << "Test 1 -- basic sanity test." << endl;
 const int MAX= 1000;
 C* array[MAX];
 { // extra braces to make for loop variable work correctly.
 for (int loop= 0;  loop < 1000;  loop++) {
    array[loop]= new C(loop);
    }
 }
 {
 for (int loop= 0;  loop < 1000;  loop++) {
    array[loop]->check(loop);
    }
 }
 {
 for (int loop= 0;  loop < 1000;  loop++) {
    delete array[loop];
    }
 }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test2()
 {
 cout << "Test 2 -- ...";
 const int MAX= 1000;
 const int sweep= 10;
 int count= 0;
 C* array[MAX];
 int loop= 0;
 while (loop < MAX-sweep) {
    for (int x= 0;  x < sweep;  x++) {
       array[loop+x]= new C(loop+x);
       ++count;
       }
    for (int y= 1;  y < sweep;  y++) {
       array[loop+y]->check (loop+y);
       delete array[loop+y];
       count++;
       }
    loop++;
    }
 cout << ' ' << count << " operations performed" << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test3()
// this verifies that (new C) worked before main() was called.
 {
 cout << "Test 3 -- works before main is called\n" << endl;
 premain->check (99);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 test2();
 test3();
 if (errorcount)  cout << "** There were " << errorcount << " errors detected." << endl;
 else cout << "All tests passed." << endl;
 return 0;
 }
 

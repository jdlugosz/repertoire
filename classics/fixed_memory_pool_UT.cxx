// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool_UT.cxx
// Revision: post-public build 6

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
 cout << "Test 3 -- works before main is called" << endl;
 premain->check (99);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test4()
// check out the check_address function
 {
 cout << "Test 4 -- check_address function" << endl;
 if (C::check_address (0))  { ++errorcount; cout << "Failed 4.1\n"; }
 if (!C::check_address (premain))  { ++errorcount; cout << "Failed 4.2\n"; }
 int x;
 if (C::check_address (&x))  { ++errorcount; cout << "Failed 4.3 (local variable misidentified)\n"; }
 char* p= reinterpret_cast<char*>(premain);
 if (C::check_address (1+p))  {++errorcount; cout << "Failed 4.4 (didn't catch misaligned)\n"; }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct staticbase
 {
 static int dummy;
 };

int staticbase::dummy= 0;

static int sequence= 0;

class member {
public:
   int val;
   member (int x) : val (x) {}
   void operator= (const member& other) { /* does not change value */ }
   };
   
template <typename T>
class testclass : public T {
   member s1;
   member s2;
public:
   testclass();
   bool check();
   };

template <typename T>
testclass<T>::testclass()
 : s1(sequence), s2(sequence)
 { ++sequence; }


template <typename T>
bool testclass<T>::check()
 {
 return (s1.val != s2.val);
 }
 
void test5()
// test for mixin assignment bug
 {
 cout << "Test 5 -- mixin assignment compiler bug" << endl;
 testclass<staticbase> v1;
 testclass<staticbase> v2;
 v1= v2;
 if (v1.check()) {
    bool workaround= true;
    cout << "Note: Detected compiler bug!!\n";
    testclass<classics::pool_mixin<double> > v3, v4;
    v3= v4;
    if (v3.check()) {
       ++errorcount;
       workaround= false;
       cout << "Failed 5.1 (pool_mixin doesn't work-around compiler bug)\n";
       }
    testclass<classics::ts_pool_mixin<double> > v5, v6;
    v5= v6;
    if (v5.check()) {
       ++errorcount;
       workaround= false;
       cout << "Failed 5.2 (ts_pool_mixin doesn't work-around compiler bug)\n";
       }
    if (workaround) {
       cout << "pool_mixin and ts_pool_mixin work-around the compiler bug OK.\n";
       }
    }
 else {
    cout << "Did not detect compiler bug (great!)\n";
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 test2();
 test3();
 test4();
 test5();
 if (errorcount)  cout << "** There were " << errorcount << " errors detected." << endl;
 else cout << "All tests passed." << endl;
 return 0;
 }
 

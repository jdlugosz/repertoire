// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\flagword_UT.cxx
// Revision: public build 6, shipped on 28-Nov-1999
// This verifies the implementation of the flagword class.

#include <iostream>
#include "classics\flagword.h"
using std::cout;
using std::endl;

enum color { red=1, yellow=2, blue=4, green=8, purple=16, orange=32, brown=64, black=128 };

typedef classics::flagword<color> colorflags;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check (const colorflags& x, unsigned long reference)
 {
 unsigned long data= x.data();
 unsigned long valid= x.valid();
 if (data!=reference || valid!=reference) {
    cout << "error!  have " << data << ',' << valid << " expected " << reference << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void check (const colorflags& x, unsigned long refdata, unsigned long refmask)
 {
 unsigned long data= x.data();
 unsigned long valid= x.valid();
 if (data!=refdata || valid!=refmask) {
    cout << "error!  have " << data << ',' << valid << " expected " << refdata << ',' << refmask << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 cout << "test1 -- ctor and copy" << endl;
 colorflags f1;  //default constructor
 colorflags f2= blue;  //copy-init syntax
 colorflags f3 (green);  //direct-init syntax
 check (f1,0);
 check (f2,4);
 check (f3,8);
 colorflags f4 (f2);
 colorflags f5= f2;
 f1= f2;  //copy assignment
 check (f4, 4);
 check (f5, 4);
 check (f1, 4);
 f5= green;  //assign enum to flags
 check (f5, 8);
 colorflags f6 (63, 28);
 check (f6, 63, 28);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test2()
 {
 // this just forces the template to expand and makes sure that the
 // desired syntax works.
 cout << "test2 -- basic use of | and & operators" << endl;
 colorflags f1= colorflags(red) | blue;
 check (f1, red|blue);
 f1 |= green;
 check (f1, red|blue|green);
 colorflags f2= f1 & red;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test3()
 {
 cout << "comprehensive test of & operator" << endl;
 colorflags left (0x00ff, 0x0f0f);
 colorflags right (0x3333, 0x5555);
 colorflags result= left & right;
 if (result.valid() != 0x4545)  cout << "error! truth table & mask wrong." << endl;
 unsigned long x= result.data();
 if ((x&1) != 1)  cout << "error!  truth table & result (1) wrong." << endl;
 if ((x&0x4544) != 0)  cout << "error!  truth table & result (0) wrong." << endl;
 // note: other bits are "don't care".
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test4()
 {
 cout << "comprehensive test of | operator" << endl;
 colorflags left (0x00ff, 0x0f0f);
 colorflags right (0x3333, 0x5555);
 colorflags result= left | right;
 if (result.valid() != 0x151f)  cout << "error!  truth table | mask wrong." << endl;
 unsigned long x= result.data();
 if ((x&0x111f)!=0x111f)  cout << "error!  truth table | result (1) wrong." << endl;
 if ((x&0x0400)!=0)  cout << "error!  truth table | result (0) wrong." << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test5()
 {
 cout << "comprehensive test of + operator" << endl;
 colorflags left (0x00ff, 0x0f0f);
 colorflags right (0x3333, 0x5555);
 colorflags result= left + right;
 if (result.valid() != 0x5f5f)  cout << "error!  truth table + mask wrong." << endl;
 unsigned long x= result.data();
 if ((x&0x111a)!=0x111a)  cout << "error!  truth table + result (1) wrong." << endl;
 if ((x&0x4e44)!=0)  cout << "error!  truth table + result (0) wrong." << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void T (int id, bool val)
 {
 if (!val)   cout << "*Error on id " << id << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline void F (int id, bool val)
 {
 T (id, !val);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test6()
 {
 cout << "test of is_ functions" << endl;
 colorflags fl (red|green|purple, /*out of*/ red|yellow|blue|green);

 T (1, fl.is_on(green));  // normal ON   <<==
 F (2, fl.is_on(yellow));  // normal OFF
 F (3, fl.is_on(purple));  // ON but not valid
 F (4, fl.is_on(black));  // OFF and not valid

 F (5, fl.is_off(green));  // normal ON
 T (6, fl.is_off(yellow));  // normal OFF  <<==
 F (7, fl.is_off(purple));  // ON but not valid
 F (8, fl.is_off(black));  // OFF and not valid

 T (9, fl.is_valid(green));  // normal ON
 T (10, fl.is_valid(yellow));  // normal OFF
 F (11, fl.is_valid(purple));  // ON but not valid
 F (12, fl.is_valid(black));  // OFF and not valid
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test7()
 {
 cout << "comprehensive test of match function" << endl;
 colorflags left (0x00ff, 0x0f0f);
 colorflags right (0x3333, 0x5555);
 colorflags result= left.match(right);
 if (result.valid() != 0x5555)  cout << "error!  truth table `match' mask wrong." << endl;
 unsigned long x= result.data();
 if ((x&0x0401)!=0x0401)  cout << "error!  truth table `match' result (1) wrong." << endl;
 if ((x&0x5154)!=0)  cout << "error!  truth table `match' result (0) wrong." << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test8()
 {
 cout << "test of bool conversion" << endl;
 colorflags fl (red|green|purple, /*out of*/ red|yellow|blue|green);
 colorflags m1 (red|green, red|green|blue);
 if (!fl.match(m1))  cout << "fails test8 case 1" << endl;
 m1 |= yellow;
 if (fl.match(m1))  cout << "fails test8 case 2" << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 test2();
 test3();
 test4();
 test5();
 test6();
 test7();
 test8();
 return 0;
 }
 

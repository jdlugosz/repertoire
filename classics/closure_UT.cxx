// The Repertoire Project copyright 2004 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure_UT.cxx
// Revision: updated


#include "classics\closure.h"
#include <iostream>
#include "classics\profile_timer.h"

using std::cout;
using std::endl;
int errorcount;
using classics::closure_stdcall_to_thiscall;

classics::profile_timer timer;
const int ITERATIONS= 1000000;

typedef int (__stdcall callback_t) (int);


callback_t* callback;

void burden (int count=3)
 {
 volatile xx=count;
 if (count==0) return;
 burden (count-1);
 }


int __stdcall callback1 (int x)
 {
 burden();
 return -x;
 }


class B1 { 
protected:
   int xx;
public:
   B1 (int xx) : xx(xx) {}
   virtual ~B1() {}
   };


class B2 { 
protected:
   int yy; 
//   double take_up_room;
public:
   B2 (int yy=17) : yy(yy) {}
   virtual ~B2() {}
   int callback2 (int x) 
    { 
    return x+42+yy; 
    }
   };

class C : /* public B1, */ public B2 {
   int value;
public:
   C (int x) : value(x) {}
   virtual int foo (int x) { return x*x; }
   virtual int callback (int);
   };

int C::callback (int x)
 {
// return x + value;  // can access members
 burden();
 return -x;
 }

class CM : public B1, public B2 {
   int value;
public:
   CM (int x) : B1(3), value(x) {}
   virtual int foo (int x) { return x + value + yy + xx; }
   };


class CV: virtual public B1, public B2 {
   int value;
public:
   CV (int x) : B1(5), value(x) {}
   virtual int foo (int x) { return x + value + yy + xx; }
   };


class B3 {
public:
   int xxx;
   };

class CV2: public CV, virtual public B1, public B3 {
   int value;
public:
   CV2 (int x) : B1(22), CV(1234), value(x) {}
   virtual int foo (int x) { return x + value + yy + xx; }
   };


bool verify (int output, int expected, const char* label)
 {
 if (output != expected) {
    ++errorcount;
    cout << "**Failed " << label << endl;
    return false;
    }
 return true;
 }



// Isolate the pointer call so I can see in the debugger what
// it does normally.
int showcall (CM& object, int (CM::*ptr)(int))
 {
 return (object.*ptr)(1000);
 }

int showcall (CV& object, int (CV::*ptr)(int))
 {
 return (object.*ptr)(1000);
 }

int showcall (CV2& object, int (CV2::*ptr)(int))
 {
 return (object.*ptr)(1000);
 }


int main (int argc, char* argv[])
 {
 bool benchmark= false;
 if (argc > 1 && !stricmp(argv[1], "benchmark"))  {
    benchmark= true;
    cout << "Times are in milliseconds for " << ITERATIONS*10 << " calls." << endl;
    }


 // a normal function.
 callback= &callback1;
 int input= 5;
 int output= callback (input);
 verify (output, -5, "1");
 ++input;  // don't get the same result twice.

 /////// here is the usage of the thunk maker:
 C object (99);
{ // extra scope
 // virtual member function
 cout << "size of virtual member pointer: " << sizeof (&C::callback) << endl;
 classics::member_callback_thunk<C,int,int> thunk (&object, &C::callback);
 callback= thunk.callptr();

 // then, 'callback' can be used as usual.  Thunk adds the this pointer.
 ++input;
 output= callback (input);
verify (output, /*input+99*/-input, "2");
 }



 { // extra scope
 // non-virtual member function
 classics::member_callback_thunk<C,int,int> thunk (&object, &C::callback2);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, input+42+17, "3");
 }


 CM object2 (99);
{ // extra scope
 // non-virtual member function on multiple inheritence
 int (CM::*temp)(int) = &CM::callback2;
 cout << "size of non-virtual member function pointer with multiple inheritence: " << sizeof (temp) << endl;
 cout << "size of CM object is " << sizeof(CM) << endl;
 // Here's how it is normally invoked:
 output= (object2.*temp)(1000);
 classics::member_callback_thunk<CM,int,int> thunk (&object2, &CM::callback2);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, input+42+17, "4");
 }

{ // extra scope
 // virtual member function on multiple inheritence
 int (CM::*temp)(int) = &CM::foo;
 cout << "size of virtual member function pointer with multiple inheritence: " << sizeof (temp) << endl;
 output= showcall (object2,temp);
 classics::member_callback_thunk<CM,int,int> thunk (&object2, &CM::foo);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, input+99+17+3, "5");
 }


 CV object3 (71);

{ // extra scope
 // virtual inheritence
 int (CV::*temp)(int) = &CV::foo;
 cout << "size of CV object is " << sizeof(CV) << endl;
 cout << "size of member function pointer with virtual inheritence: " << sizeof (temp) << endl;
 output= showcall (object3,temp);
 classics::member_callback_thunk<CV,int,int> thunk (&object3, &CV::foo);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, input+71+17+5, "6");
 }

{ // extra scope
 // virtual inheritence
 int (CV::*temp)(int) = &CV::callback2;
 cout << "size of member function pointer with virtual inheritence: " << sizeof (temp) << endl;
 output= showcall (object3,temp);
 classics::member_callback_thunk<CV,int,int> thunk (&object3, &CV::callback2);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, object3.callback2(input), "7");
 }

CV2 object4 (12);
{ // extra scope
 // virtual inheritence
 int (CV2::*temp)(int) = &CV2::callback2;
 cout << "size of member function pointer with virtual inheritence: " << sizeof (temp) << endl;
 output= showcall (object4,temp);
 classics::member_callback_thunk<CV,int,int> thunk (&object4, &CV2::callback2);
 callback= thunk.callptr();
 ++input;
 output= callback (input);
 verify (output, object4.callback2(input), "8");
 }

 
 ////// all done.  Report.
 if (errorcount) {
    cout << "Some tests failed." << endl;
    return 2;
    }
 cout << "All tests passed." << endl;


 return 0;
 }
 

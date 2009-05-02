// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include "classics\closure.h"
#include <iostream>
using std::cout;
using std::endl;
int errorcount;
using classics::closure_stdcall_to_thiscall;

typedef int (__stdcall callback_t) (int);


callback_t* callback;

int __stdcall callback1 (int x)
 {
 return -x;
 }


class B1 { 
   int xx;
public:
   virtual ~B1() {}
   };
class B2 { 
   int yy; 
public:
   virtual ~B2() {}
   virtual int callback2 (int) { return 42; }
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
 return x + value;  // can access members
 }



void verify (int output, int expected, const char* label)
 {
 if (output != expected) {
    ++errorcount;
    cout << "**Failed " << label << endl;
    }
 }


#if 0
template <typename T>
class member_callback_thunk : private closure_stdcall_to_thiscall {
   static void sizecheck(char (*p)[4]) {}
   static void* helper (int (T::*member)(int));
public:
   member_callback_thunk (T* object, int (T::*member)(int)) : closure_stdcall_to_thiscall (object, helper(member)) {}
   callback_t* callptr() const { return reinterpret_cast<callback_t*>(this); }
   };


template <typename T>
void* member_callback_thunk<T>::helper (int (T::*member)(int))
 {
 union {
    int (T::*p)(int);
    void* function;
    char ss[ sizeof (int (T::*)(int)) ];
    };
 sizecheck(&ss);  // Force a compile-time error if 'member' is not 4 bytes.
    // meaning single-inheritance simple case only.  More complex classes can't
    // use this.
 p= member;
 return function;
 }
#endif




int main()
 {
 callback= &callback1;
 int input= 5;
 int output= callback (input);
 verify (output, -5, "1");
 ++input;  // don't get the same result twice.

 /////// here is the usage of the thunk maker:
 C object (99);
 classics::member_callback_thunk<C,int,int> thunk (&object, &C::callback);
 callback= thunk.callptr();

 // then, 'callback' can be used as usual.  Thunk adds the this pointer.
 ++input;
 output= callback (input);
 verify (output, input+99, "3");

 ////// all done.  Report.
 if (errorcount) {
    cout << "Some tests failed." << endl;
    return 2;
    }
 cout << "All tests passed." << endl;
 return 0;
 }
 

// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception_UT.cxx
// Revision: public build 5, shipped on 8-April-1999

// This tests the exception class

#include "classics\exception.h"
#include "classics\string_ios.h"
#include <iostream>

using std::cout;
using std::endl;
using classics::wFmt;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 try {
    int value= 42;
    classics::exception X ("tests", "Test Error", __FILE__, __LINE__);
    wFmt(X) << "The value is " << value << L"." << endl;
      // why is the L needed above?  Compiler bug?
    throw X;
    }
 catch (classics::exception& X) {
    X.show();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void bar2()
 {
 int value= 42;
 classics::exception X ("tests", "Test Error", __FILE__, __LINE__);
 wFmt(X) << L"The test value is " << value << L"." << endl;
 throw X;
 }

// =============================================

void foo2()
 {
 int loop= 17;
 try {
    bar2();
    }
 catch (classics::exception& X) {
    X ("tests", "Foo Name", __FILE__, __LINE__);
    wFmt(X) << L"loop is " << loop << L"." << endl;
    throw;
    }
 }
    
// =============================================

void test2()
 {
 try {
    foo2();
    }
 catch (classics::exception& X) {
    X.show();
    }
 }
    
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 test2();
 cout << "* note: results not automatically validated." << endl;
 return 0;
 }
 

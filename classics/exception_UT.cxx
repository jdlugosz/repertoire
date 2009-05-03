// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\exception_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006

// This tests the exception class

#define _CRT_SECURE_NO_DEPRECATE
#include "classics\exception.h"
#include "classics\string_ios.h"
#include <iostream>
#include <time.h>

using std::cout;
using std::endl;
using classics::wFmt;
using classics::ustring;

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

void (*old_setup_hook) (classics::exception* self, const ustring& module, const ustring& name, const ustring& fname, int line);

void my_setup (classics::exception* self, const ustring& module, const ustring& name, const ustring& fname, int line)
 {
 old_setup_hook (self, module, name, fname, line);
 // then add my own stuff
 tm *newtime;
 time_t aclock;
 time (&aclock);
 newtime= localtime (&aclock);
 self->add_key ("Time", asctime(newtime));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test3()
 {
 cout << "testing setup_hook" << endl;
 old_setup_hook= classics::exception::setup_hook;
 classics::exception::setup_hook= my_setup;
 test1();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 test2();
 test3();
 cout << "* note: results not automatically validated." << endl;
 return 0;
 }


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\win_handle.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\win_handle.h"
#include "ratwin\tasking\basic.h"
#include "classics\string_ios.h"  //for formatting error messages

STARTWRAP
namespace classics {
using classics::wFmt;
using std::endl;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool wait (ratwin::types::Kernel_HANDLE h, unsigned timeout)
 {
 using namespace ratwin::tasking;
 unsigned retval= WaitForSingleObject (h, timeout); 
 switch (retval) {
    default: {
       classics::exception X ("Classics", "wait(HANDLE) error", __FILE__, __LINE__);
       wFmt(X) << "Waiting on a HANDLE returned an unexpected value of " << retval << endl;
       throw X;
       }
    case WAIT_FAILED: {
       classics::win_exception X ("Classics", __FILE__, __LINE__);
       X += L"Error occured waiting on a HANDLE.\n";
       throw X;
       }
    case WAIT_OBJECT_0:
       return true;  //normal completion
    case WAIT_TIMEOUT:
       return false;  //time-out completion
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end classics
ENDWRAP



// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\mutex.cpp
// Revision: post-public build 6

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\mutex.h"
#include "ratwin\tasking\Mutex.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"
#include "ratwin\handle.h"
#include "classics\win_handle.h"
const char FNAME[]= __FILE__;

STARTWRAP
namespace classics {

bool Unicode= true;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

mutex::mutex (bool blocked)
 :H(0)
 {
 H= ratwin::tasking::CreateMutex (blocked, (const char*)0);
 if (!H) {
    win_exception X ("Classics", FNAME, __LINE__);
    X += "Can't create unnamed Mutex";
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

mutex::mutex (const ustring& name, bool blocked)
 :Name(name)
 {
 int errorcode;
 if (Unicode) {
    wstring s= name;
    H= ratwin::tasking::CreateMutex (blocked, s.c_str());
    errorcode= ratwin::util::GetLastError();
    if (!H) {
       if (errorcode == win_exception::call_not_implemented_error) {
          Unicode= false;
          goto ANSI;
          }
       goto error;
       }
    }
 else {  //must be ANSI
    ANSI:
    string s= name;
    H= ratwin::tasking::CreateMutex (blocked, s.c_str());
    errorcode= ratwin::util::GetLastError();
    if (!H) {
       goto error;
       }
    }
 Created= errorcode!=183;  //already exists
 if (blocked && !Created)  enter();    //always acquires if blocked is set.
 return;
 
 error:
    win_exception X ("Classics", FNAME, __LINE__, errorcode);
    X.add_key ("name", name);
    X += "Can't create named Mutex";
    throw X;
 
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

mutex::~mutex()
 {
 ratwin::CloseHandle(H);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool mutex::wait (unsigned timeout)
 {
 try {
    return classics::wait (H, timeout);
    }
 catch (exception& X) {
    X ("Classics", "Can't wait on Mutex", FNAME, __LINE__);
    if (Name.elcount())  X.add_key ("name", Name);
    throw;
    }
 return false;  //stupid compiler!
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mutex::leave()
 {
 bool result= ratwin::tasking::ReleaseMutex (H);
 if (!result) {
    win_exception X ("Classics", FNAME, __LINE__);
    if (Name.elcount())  X.add_key ("name", Name);
    X += "Can't release mutex";
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP


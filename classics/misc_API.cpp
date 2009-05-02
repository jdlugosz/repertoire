// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\misc_API.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\misc_API.h"
#include "classics\string.h"
#include "classics\exception.h"
#include "ratwin\tasking\process.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {

static const char FNAME[]= __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring GetModuleFileName (ratwin::types::HINSTANCE hModule)
 {
 const int size= 1024;
 static bool Unicode=true;
 int bufsize= size;
 retry:
 if (Unicode) {
    wstring result (bufsize+1);  //input len does not include room for trailing NUL -- 1 more assumed.
    unsigned long len= ratwin::tasking::GetModuleFileName(hModule, result.get_buffer(), bufsize);
    if (len==0) {
       ulong err= ratwin::util::GetLastError();
       if (err==win_exception::call_not_implemented_error) {
          Unicode=false;
          goto retry;
          }
       classics::win_exception X ("Classics", FNAME, __LINE__, err);
       throw X;
       }
    else if (len == bufsize) {
       //exact fit -- maybe truncated
       bufsize *= 2;
       goto retry;
       }
    result.truncate(len);
    return result;
    }
 else {  //non-Unicode
    string result (bufsize+1);  //input len does not include room for trailing NUL -- 1 more assumed.
    unsigned long len= ratwin::tasking::GetModuleFileName(hModule, result.get_buffer(), bufsize);
    if (len==0) {
       classics::win_exception X ("Classics", FNAME, __LINE__);
       throw X;
       }
    else if (len == bufsize) {
       //exact fit -- maybe truncated
       bufsize *= 2;
       goto retry;
       }
    result.truncate(len);
    return result;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec (noreturn) void internal_error (const char* fname, int line)
 {
 classics::exception X ("Classics", "Unexpected internal error", fname, line);
 X += "This cannot happen.";
 throw X;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring as_string (const ratwin::GUID& guid)
 {
 const int size_needed =40;
 wstring result (size_needed);
 int size= guid.to_string (result.get_buffer(), size_needed);
 if (size != 39) {
    internal_error (FNAME, __LINE__);
    }
 result.truncate (size-1);
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP



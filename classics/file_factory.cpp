// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\file_factory.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\file_factory.h"
#include "ratwin\io\file.h"
#include "ratwin\handle.h"
#include "ratwin\utilities.h"
#include "classics\exception.h"
#include "classics\string_ios.h"

STARTWRAP
namespace classics {

static const char FNAME[]= __FILE__;
static const char MODULE[]= "Classics";

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HANDLE file_factory::Create (const filename_t& name) const
 {
 static bool Unicode= true;
 unsigned long errorcode;
 ratwin::types::HANDLE handle;
 if (Unicode) {
    wstring s= name.text();
    handle= ratwin::io::CreateFile (s.c_str(), access, share, how, even_more_flags);
    if (handle == ratwin::INVALID_HANDLE_VALUE) {
       errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error)
          Unicode= false;
          // and fall through to ANSI case
       else goto error;
       }
    return handle;
    }
 // must be ANSI
    {
    string s= name.text();
    handle= ratwin::io::CreateFile (s.c_str(), access, share, how, even_more_flags);
    if (handle != ratwin::INVALID_HANDLE_VALUE)
       return handle;
    }
 error:
    if (CanFail)  return handle;
    win_exception X (MODULE, FNAME, __LINE__);
    wFmt(X) << L"Error opening \"" << wstring(name.text()) << L"\".";
    // ... can add more informatioin regarding options
    throw X;
 return handle;  //stupid compiler!
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

file_factory::file_factory (construct_mode_t mode)
 {
 using namespace ratwin::io;
 even_more_flags= 0;
 CanFail= false;  //throws exception on error
 switch (mode) {
    case Read:
       access= GENERIC_READ;
       share= FILE_SHARE_READ;
       how= OPEN_EXISTING;
       break;
    case ReadWrite:
       access= GENERIC_READWRITE;
       share= FILE_SHARE_EXCLUSIVE;
       how= OPEN_ALWAYS;
       break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP


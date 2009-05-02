// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\file_factory.cpp
// Revision: public build 6

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
using std::endl;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::IO_HANDLE file_factory::Create (const filename_t& name) const
 {
 static enum { Yes, No, Maybe } Unicode= Maybe;
 unsigned long errorcode;
 ratwin::types::IO_HANDLE handle;
 switch (Unicode) {
    case Yes: {
       wstring s= name.text();
       handle= ratwin::io::CreateFile (s.c_str(), access, share, how, even_more_flags);
       if (handle != ratwin::io::INVALID_FILE)
          return handle;
       } break;

    default:
    case Maybe: {
       wstring s= name.text();
       ratwin::util::SetLastError(0);
       handle= ratwin::io::CreateFile (s.c_str(), access, share, how, even_more_flags);
       errorcode= ratwin::util::GetLastError();
       if (handle == (ratwin::types::HANDLE)0 && errorcode == win_exception::call_not_implemented_error) {
          Unicode= No;
          // fall through to ANSI case
          }
       else if (handle == ratwin::io::INVALID_FILE) {
          if (errorcode == win_exception::call_not_implemented_error)
             Unicode= No;
             // and fall through to ANSI case
          else break;
          }
       else {
          Unicode= Yes;
          return handle;
          }
       }

    case No: {
       string s= name.text();
       handle= ratwin::io::CreateFile (s.c_str(), access, share, how, even_more_flags);
       if (handle != ratwin::io::INVALID_FILE)
          return handle;
       } break;
    }

// error:
    if (CanFail)  return handle;
    win_exception X (MODULE, FNAME, __LINE__);
    X.add_key ("filename", name.text());
    X += "Error opening file.\n";
    wFmt(X) << L"access: " << access << L", share:" << share <<  L", flags:" << even_more_flags << endl;
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


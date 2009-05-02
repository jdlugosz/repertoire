// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\file.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\file.h"
#include "classics\exception.h"
#include "ratwin\handle.h"
#include "classics\string_ios.h"  //for formatting error messages

using std::endl;
using classics::wFmt;

STARTWRAP
namespace tomahawk {

using namespace ratwin::io;
using classics::string;
using classics::wstring;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

class Error : public classics::win_exception {
public:
   Error (int line);
   };
   
//=============================================

Error::Error (int line)
 :classics::win_exception("Tomahawk", __FILE__, line)
 {}
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

file::open_spec::open_spec()
 {
 access= GENERIC_READWRITE;
 share= FILE_SHARE_EXCLUSIVE;
 how= OPEN_ALWAYS;
 even_more_flags= 0;
 CanFail= false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool file::open (const open_spec& spec, wstring filename)
 {
 close();
 filename.append (L'\0');
 ratwin::types::HANDLE new_h= CreateFile (filename.get_buffer(), spec.access, spec.share, spec.how, spec.even_more_flags);
 if (new_h == 0)  throw classics::exception ("Tomahawk", "That can't happen!", __FILE__, __LINE__);
 if (new_h == ratwin::types::HANDLE(0xffffffff)) {
    if (spec.CanFail)  return false;
    else {
       Error X (__LINE__);
       wFmt(X) << L"Can't open file named \"" << filename << L"\"." << endl;
       throw X;
       }
    }
 H= new_h;
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void file::close()
 {
 if (!H)  return;
 if (!ratwin::CloseHandle(H)) {
    Error X (__LINE__);
    X += L"Can't close a file\n";
    throw X;
    }
 H=0;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__int64 file::size() const
 {
 __int64 retval= GetFileSize (H);
 if (retval == -1) {
    Error X (__LINE__);
    X += L"Error getting the file's size\n";
    }
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP


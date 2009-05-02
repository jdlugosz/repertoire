// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\cursor.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\cursor.h"
#include "ratwin\resource.h"
#include "classics\exception.h"
#include "classics\string_ios.h"  //for formatting error messages

using std::endl;
using classics::wFmt;

STARTWRAP
namespace tomahawk {

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

cursor::internal::~internal()
 {
 if (!ratwin::resource::DestroyCursor (H)) {
    Error X (__LINE__);
    X += L"Can't destroy cursor.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cursor::internal::internal (stock x)
 {
 using namespace ratwin::resource;
 cursor_id value= static_cast<cursor_id>(x);
 H= LoadCursor (0, value);
 if (!H) {
    Error X (__LINE__);
    wFmt(X) << L"Can't load stock cursor with resource ID " << value << L"." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

cursor::internal::internal (ratwin::types::HINSTANCE inst, const char* name)
 {
 H= ratwin::resource::LoadCursor (inst, name);
 if (!H)  {
    Error X (__LINE__);
    wFmt(X) << L"Can't load cursor named \"" << name << L"\" from HINSTANCE " << inst << L"." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void cursor::make_active() const
 {
 ratwin::resource::SetCursor (h());
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP


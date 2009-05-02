// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\gdi\dc.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\base.h"
#include "tomahawk\gdi\dc.h"
#include "tomahawk\color_t.h"
#include "classics\point_ios.h"
#include "ratwin\text.h"
#include "ratwin\GDI.h"
#include "classics\exception.h"
#include "classics\string_ios.h"  //for formatting error messages
#include "classics\point_ios.h"

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

point dc::text_extent (const char* buf, int len)
 {
 ratwin::types::POINT result;
 if (!ratwin::text::GetTextExtent (Handle, buf, len, result)) {
    Error X (__LINE__);
    wFmt(X) << L"Can't get text extent of " << len << L" character string \"" << classics::string(buf,len) << L"\"." << endl;
    throw X;
    }
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

color_t rendering_dc::bk_color (color_t newcolor)
 {
 return ratwin::gdi::SetBkColor (Handle, newcolor.value());
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

color_t rendering_dc::bk_color_window()
 {
 // This sets the "normal" background color for a window, as
 // specified in the Control Panel settings.  A common mistake is
 // to forget this, which looks funny for people who have other than
 // white as their window background color.  I made it easy with
 // this call, so use it!  Tip: test your program under the "Hotdog Stand"
 // color scheme.
 color_t background (ratwin::gdi::COLOR_WINDOW);
 return ratwin::gdi::SetBkColor (Handle, background.value());
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

color_t rendering_dc::text_color (color_t newcolor)
 {
 return ratwin::text::SetTextColor (Handle, newcolor.value());
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

color_t dc::text_color() const
 {
 return ratwin::text::GetTextColor (Handle);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void rendering_dc::TextOut (point pos, const char* s, int len)
 {
 if (!ratwin::text::TextOut (Handle, pos.x, pos.y, s, len)) {
    Error X (__LINE__);
    wFmt(X) << L"Failed call to TextOut (" << pos << L", " << L"0x" << Handle << L", \"" << classics::string(s,len) << L"\", " << len << L")." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}  //end namespace
ENDWRAP


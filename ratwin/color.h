// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\color.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_COLOR_INCLUDED
#define RATWIN_COLOR_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) unsigned long __stdcall GetSysColor (Dlugosz::ratwin::arg::arg32);
}


////////////////////////

STARTWRAP
namespace ratwin {

namespace color {

enum sys_color_index {
   COLOR_SCROLLBAR,
   COLOR_BACKGROUND,
   COLOR_ACTIVECAPTION,
   COLOR_INACTIVECAPTION,
   COLOR_MENU,
   COLOR_WINDOW,
   COLOR_WINDOWFRAME,
   COLOR_MENUTEXT,
   COLOR_WINDOWTEXT,
   COLOR_CAPTIONTEXT,
   COLOR_ACTIVEBORDER,
   COLOR_INACTIVEBORDER,
   COLOR_APPWORKSPACE,
   COLOR_HIGHLIGHT,
   COLOR_HIGHLIGHTTEXT,
   COLOR_BTNFACE,
   COLOR_BTNSHADOW,
   COLOR_GRAYTEXT,
   COLOR_BTNTEXT,
   COLOR_INACTIVECAPTIONTEXT,
   COLOR_BTNHIGHLIGHT,
   COLOR_3DDKSHADOW,
   COLOR_3DLIGHT,
   COLOR_INFOTEXT,
   COLOR_INFOBK,
   COLOR_DESKTOP=     COLOR_BACKGROUND,
   COLOR_3DFACE=      COLOR_BTNFACE,
   COLOR_3DSHADOW=    COLOR_BTNSHADOW,
   COLOR_3DHIGHLIGHT= COLOR_BTNHIGHLIGHT,
   COLOR_3DHILIGHT=   COLOR_BTNHIGHLIGHT,
   COLOR_BTNHILIGHT=  COLOR_BTNHIGHLIGHT,
   };

inline ulong GetSysColor (sys_color_index nIndex)
 { ulong x= nIndex; return ::GetSysColor (reinterpret_cast<arg::arg32>(x)); }

} //end color

}
ENDWRAP
#endif



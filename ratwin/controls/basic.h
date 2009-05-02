// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\basic.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\basic.h contains globals.  Use ratwin\basic=struct.h instead.
#endif

#include "ratwin\controls\basic=struct.h"
#include "classics\flagword.h"

extern "C" {
// __declspec(dllimport) void __stdcall InitCommonControls();
  // non-Ex is deprecated, and non-cloakable.
__declspec(dllimport) int __stdcall InitCommonControlsEx (Dlugosz::ratwin::arg::carg32);
}

STARTWRAP
namespace ratwin {
namespace controls {

inline bool InitCommonControls (classics::flagword<ICC_flags> flags)
 {
 INITCOMMONCONTROLSEX s= { sizeof s, flags.validdata() };
 return ::InitCommonControlsEx (reinterpret_cast<arg::carg32>(&s));
 }

} // end of controls

}
ENDWRAP


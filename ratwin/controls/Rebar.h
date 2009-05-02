// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\Rebar.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\controls\Rebar.h contains globals.  Include Rebar=struct.h instead.
#endif

#include "ratwin\controls\Rebar=struct.h"
#include "ratwin\window.h"

STARTWRAP
namespace ratwin {
namespace controls {

inline
bool InsertBand (types::HWND window, REBARBANDINFO<char>& info, int position=-1)
 {
 return ratwin::window::SendMessage (window, RB_INSERTBANDA, position, &info);
 }

inline
bool InsertBand (types::HWND window, REBARBANDINFO<wchar_t>& info, int position=-1)
 {
 return ratwin::window::SendMessage (window, RB_INSERTBANDW, position, &info);
 }

} // end of controls
}
ENDWRAP


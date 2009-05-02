// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ReBar.h
// Revision: new

#pragma once
#if defined RATWIN_NoGlobals
   #error contains globals.
#endif

#include "ratwin\controls\Rebar=struct.h"
#include "ratwin\window.h"

STARTWRAP
namespace ratwin {
namespace controls {

bool InsertBand (types::HWND window, REBARBANDINFO<char>& info, int position=-1)
 {
 return ratwin::window::SendMessage (window, RB_INSERTBANDA, position, &info);
 }

bool InsertBand (types::HWND window, REBARBANDINFO<wchar_t>& info, int position=-1)
 {
 return ratwin::window::SendMessage (window, RB_INSERTBANDW, position, &info);
 }

} // end of controls
}
ENDWRAP


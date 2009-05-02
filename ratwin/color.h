// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\color.h
// Revision: updated

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\color.h contains globals.  Use ratwin\color=struct.h instead.
#endif

#include "ratwin\color=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) unsigned long __stdcall GetSysColor (Dlugosz::ratwin::arg::arg32);
}


////////////////////////

STARTWRAP
namespace ratwin {
namespace color {


inline COLORREF GetSysColor (sys_color_index nIndex)
 {
 ulong x= nIndex; 
 return static_cast<COLORREF>(::GetSysColor (reinterpret_cast<arg::arg32>(x))); 
 }


} //end color

}
ENDWRAP



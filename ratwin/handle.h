// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\handle.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\handle.h contains globals.
#endif

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall CloseHandle (Dlugosz::ratwin::arg::arg32);

}  //end of "C"

STARTWRAP
namespace ratwin {

inline
bool CloseHandle (types::Kernel_HANDLE x)
 { return ::CloseHandle (reinterpret_cast<arg::arg32>(x)); }

// static const types::HANDLE INVALID_HANDLE_VALUE= reinterpret_cast<types::HANDLE>(-1);
//  moved to file=struct.h (but use INVALID_FILE instead)

}
ENDWRAP


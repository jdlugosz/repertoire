// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\handle.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall CloseHandle (Dlugosz::ratwin::arg::arg32);

}  //end of "C"

STARTWRAP
namespace ratwin {

inline
bool CloseHandle (types::HANDLE x)
 { return ::CloseHandle (reinterpret_cast<arg::arg32>(x)); }

static const types::HANDLE INVALID_HANDLE_VALUE= reinterpret_cast<types::HANDLE>(-1);

}
ENDWRAP


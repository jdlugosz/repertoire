// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\mailslot.h
// Revision: initial

#pragma once

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall GetComputerNameA (Dlugosz::ratwin::arg::arg32,Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall GetComputerNameW (Dlugosz::ratwin::arg::arg32,Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {

// GetComputerName notes:  On Win9x, fails if the input size is less than MAX_COMPUTERNAME_LENGTH + 1 ( =32 total )
// input size of buffer (including room for a \0 ?), output is actual size not including the \0.

inline bool GetComputerName (/* out */ char* buffer, /* in, out */ int* size)
 {
 return ::GetComputerNameA (reinterpret_cast<arg::arg32>(buffer), reinterpret_cast<arg::arg32>(size));
 }

inline bool GetComputerName (/* out */ wchar_t* buffer, /* in, out */ int* size)
 {
 return ::GetComputerNameW (reinterpret_cast<arg::arg32>(buffer), reinterpret_cast<arg::arg32>(size));
 }

} // end of ratwin
ENDWRAP


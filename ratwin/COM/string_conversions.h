// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\string_conversions.h
// Revision: post-public build 6

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\COM\string_conversions.h contains globals.
#endif


#include "ratwin\COM\HRESULT.h"
#include "ratwin\COM\GUID.h"

extern "C" {
__declspec(dllimport) int __stdcall StringFromCLSID (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

inline HRESULT StringFromCLSID (const CLSID& clsid, wchar_t** result)
 {
 return reinterpret_cast<HRESULT>(::StringFromCLSID (reinterpret_cast<arg::carg32>(&clsid), reinterpret_cast<arg::arg32>(result)));
 }

}
ENDWRAP



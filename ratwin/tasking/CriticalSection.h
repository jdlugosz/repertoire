// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\CriticalSection.h
// Revision: 


#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\CriticalSection.h contains globals.  Include CriticalSection=struct.h instead.
#endif

#include "ratwin\tasking\CriticalSection=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) void __stdcall InitializeCriticalSection (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall EnterCriticalSection (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall LeaveCriticalSection (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall DeleteCriticalSection (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall TryEnterCriticalSection (Dlugosz::ratwin::arg::arg32);
}  //end of "C"


STARTWRAP
namespace ratwin {

namespace tasking {


inline 
void InitializeCriticalSection (CRITICAL_SECTION& x)
  { ::InitializeCriticalSection (reinterpret_cast<arg::arg32>(&x)); }

inline 
void EnterCriticalSection (CRITICAL_SECTION& x)
  { ::EnterCriticalSection (reinterpret_cast<arg::arg32>(&x)); }
  
inline 
void LeaveCriticalSection (CRITICAL_SECTION& x)
  { ::LeaveCriticalSection (reinterpret_cast<arg::arg32>(&x)); }

inline 
void DeleteCriticalSection (CRITICAL_SECTION& x)
  { ::DeleteCriticalSection (reinterpret_cast<arg::arg32>(&x)); }


inline 
bool TryEnterCriticalSection (CRITICAL_SECTION& x)
  { return ::TryEnterCriticalSection (reinterpret_cast<arg::arg32>(&x)); }

}  //end tasking

}
ENDWRAP


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\Mutex.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_Tasking_KernalObjects_INCLUDED
#define RATWIN_Tasking_KernalObjects_INCLUDED

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateMutexA (Dlugosz::ratwin::arg::arg32 security, int owned, const char* name);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateMutexW (Dlugosz::ratwin::arg::arg32 security, int owned, const wchar_t* name);
__declspec(dllimport) int __stdcall ReleaseMutex (Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {
namespace tasking {

inline
types::HANDLE CreateMutex (bool initially_owned= false, const char* name= 0)
 {
 return reinterpret_cast<types::HANDLE>( ::CreateMutexA (0, initially_owned, name) );
 }

inline
types::HANDLE CreateMutex (bool initially_owned= false, const wchar_t* name= 0)
 {
 return reinterpret_cast<types::HANDLE>( ::CreateMutexW (0, initially_owned, name) );
 }

inline
bool ReleaseMutex (types::HANDLE h)
 {
 return ::ReleaseMutex (reinterpret_cast<arg::arg32>(h));
 }
 

}}
ENDWRAP

#endif





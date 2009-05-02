// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\Mutex.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#if defined RATWIN_NoGlobals
   #error ratwin\Mutex.h contains globals.
#endif

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateMutexA (Dlugosz::ratwin::arg::carg32 security, int owned, const char* name);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateMutexW (Dlugosz::ratwin::arg::carg32 security, int owned, const wchar_t* name);
__declspec(dllimport) int __stdcall ReleaseMutex (Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {
namespace tasking {

inline
types::Kernel_HANDLE CreateMutex (bool initially_owned= false, const char* name= 0)
 {
 return reinterpret_cast<types::Kernel_HANDLE>( ::CreateMutexA (0, initially_owned, name) );
 }

inline
types::Kernel_HANDLE CreateMutex (bool initially_owned, const char* name, const types::SECURITY_ATTRIBUTES& sa)
 {
 return reinterpret_cast<types::Kernel_HANDLE>( ::CreateMutexA (reinterpret_cast<arg::carg32>(&sa), initially_owned, name) );
 }

inline
types::Kernel_HANDLE CreateMutex (bool initially_owned= false, const wchar_t* name= 0)
 {
 return reinterpret_cast<types::Kernel_HANDLE>( ::CreateMutexW (0, initially_owned, name) );
 }

inline
types::Kernel_HANDLE CreateMutex (bool initially_owned, const wchar_t* name, const types::SECURITY_ATTRIBUTES& sa)
 {
 return reinterpret_cast<types::Kernel_HANDLE>( ::CreateMutexW (reinterpret_cast<arg::carg32>(&sa), initially_owned, name) );
 }

inline
bool ReleaseMutex (types::Kernel_HANDLE h)
 {
 return ::ReleaseMutex (reinterpret_cast<arg::arg32>(h));
 }
 

}}
ENDWRAP



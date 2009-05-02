// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\event.h
// Revision: public build 9, shipped on 18-Oct-2006

// SEE ALSO classics\event_flag.h for easy-to-use class wrapper.

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\tasking\event.h contains globals.
#endif

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall SetEvent (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall ResetEvent (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall PulseEvent (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateEventA (Dlugosz::ratwin::arg::carg32, int, int, const char*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateEventW (Dlugosz::ratwin::arg::carg32, int, int, const wchar_t*);
}

STARTWRAP
namespace ratwin {

namespace tasking {

inline
types::Kernel_HANDLE CreateEvent (bool manual_reset, bool initial_state=false, const char* name= 0)
 { return reinterpret_cast<types::Kernel_HANDLE> (::CreateEventA (0, manual_reset, initial_state, name)); }

inline
types::Kernel_HANDLE CreateEvent (bool manual_reset, bool initial_state, const wchar_t* name)
 { return reinterpret_cast<types::Kernel_HANDLE> (::CreateEventW (0, manual_reset, initial_state, name)); }

inline
types::Kernel_HANDLE CreateEvent (bool manual_reset, bool initial_state, const char* name, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::Kernel_HANDLE> (::CreateEventA (reinterpret_cast<arg::carg32>(&sa), manual_reset, initial_state, name)); }

inline
types::Kernel_HANDLE CreateEvent (bool manual_reset, bool initial_state, const wchar_t* name, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::Kernel_HANDLE> (::CreateEventW (reinterpret_cast<arg::carg32>(&sa), manual_reset, initial_state, name)); }

inline
bool SetEvent (types::Kernel_HANDLE event)
 { return ::SetEvent (reinterpret_cast<arg::arg32>(event)); }

inline
bool ResetEvent (types::Kernel_HANDLE event)
 { return ::ResetEvent (reinterpret_cast<arg::arg32>(event)); }

inline
bool PulseEvent (types::Kernel_HANDLE event)
 { return ::PulseEvent (reinterpret_cast<arg::arg32>(event)); }

} //end tasking

}
ENDWRAP



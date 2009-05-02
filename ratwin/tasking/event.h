// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\event.h
// Revision: updated

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
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateEventA (Dlugosz::ratwin::arg::arg32, int, int, const char*);
}

STARTWRAP
namespace ratwin {

namespace tasking {

inline
types::Kernel_HANDLE CreateEvent (bool manual_reset, bool initial_state=false, const char* name= 0)
 { return reinterpret_cast<types::Kernel_HANDLE> (::CreateEventA (0, manual_reset, initial_state, name)); }

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



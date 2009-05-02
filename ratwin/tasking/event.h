// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\event.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_TASKING_EVENT_INCLUDED
#define RATWIN_TASKING_EVENT_INCLUDED

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
types::HANDLE CreateEvent (bool manual_reset, bool initial_state=false, const char* name= 0)
 { return reinterpret_cast<types::HANDLE> (::CreateEventA (0, manual_reset, initial_state, name)); }

inline
bool SetEvent (types::HANDLE event)
 { return ::SetEvent (reinterpret_cast<arg::arg32>(event)); }

inline
bool ResetEvent (types::HANDLE event)
 { return ::ResetEvent (reinterpret_cast<arg::arg32>(event)); }

inline
bool PulseEvent (types::HANDLE event)
 { return ::PulseEvent (reinterpret_cast<arg::arg32>(event)); }

} //end tasking

}
ENDWRAP
#endif



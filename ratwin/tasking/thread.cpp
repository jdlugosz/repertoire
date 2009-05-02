// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\thread.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define RATWIN_EXPORT __declspec(dllexport)

#include "ratwin\tasking\thread.h"

STARTWRAP
namespace ratwin {
namespace tasking {

types::Thread_HANDLE CreateThread (ulong& id, THREAD_START_ROUTINE start, void* argument)
 {
 return reinterpret_cast<types::Thread_HANDLE>(::CreateThread (0, 0, reinterpret_cast<arg::arg32>(start), reinterpret_cast<arg::arg32>(argument), 0, &id));
 }

}}
ENDWRAP


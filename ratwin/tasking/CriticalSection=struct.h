// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\CriticalSection=struct.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace tasking {

struct CRITICAL_SECTION {
   void* DebugInfo;  //used internally
   long LockCount;
   long RecursionCount;
   types::HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
   types::HANDLE LockSemaphore;
   ulong Reserved;
   };

}  //end tasking

}
ENDWRAP


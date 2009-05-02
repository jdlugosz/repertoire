// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\thread.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\thread.h contains globals.
#endif

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateThread (
    Dlugosz::ratwin::arg::arg32 lpThreadAttributes,
    unsigned long dwStackSize,
    Dlugosz::ratwin::arg::arg32 lpStartAddress,
    Dlugosz::ratwin::arg::arg32 lpParameter,
    unsigned long dwCreationFlags,
    unsigned long* lpThreadId
    );
__declspec(dllimport) int __stdcall TerminateThread (Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllimport) unsigned long __stdcall QueueUserAPC (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall GetThreadTimes (Dlugosz::ratwin::arg::arg32, __int64*, __int64*, __int64*, __int64*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetCurrentThread();  //obtain the pseudohandle constant.
__declspec(dllimport) void __stdcall ExitThread (Dlugosz::ratwin::arg::arg32);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace tasking {

typedef ulong (__stdcall *THREAD_START_ROUTINE)(void*);

inline
types::Thread_HANDLE CreateThread (
    ulong stack_size,
    THREAD_START_ROUTINE start_address,
    void* param,
    ulong flags,
    ulong& id
    )
 { return reinterpret_cast<types::Thread_HANDLE>(::CreateThread (0, stack_size, reinterpret_cast<arg::arg32>(start_address), reinterpret_cast<arg::arg32>(param), flags, &id)); }

RATWIN_EXPORT
types::Thread_HANDLE CreateThread (ulong& id, THREAD_START_ROUTINE, void* argument);

inline
bool TerminateThread (types::hsoft<types::Thread_HANDLE> thd, ulong exitcode)
 { return ::TerminateThread (thd.value, exitcode); }

inline
bool QueueUserAPC (void (__stdcall *func)(void*),types::hsoft<types::Thread_HANDLE> thr, void* data)
 {  return ::QueueUserAPC (reinterpret_cast<arg::arg32>(func), thr.value, data); }

inline
bool GetThreadTimes (types::hsoft<types::Thread_HANDLE> thd, __int64& creation_time, __int64& exit_time, __int64& kernel_time, __int64& user_time)
 {  return ::GetThreadTimes (thd.value, &creation_time, &exit_time, &kernel_time, &user_time); }

inline
types::Thread_HANDLE GetCurrentThread()
 {  return reinterpret_cast<types::Thread_HANDLE>( ::GetCurrentThread() ); }

inline
void ExitThread (int exitcode)
 {  ::ExitThread (reinterpret_cast<arg::arg32>(exitcode));  }
 
} //end tasking
}
ENDWRAP


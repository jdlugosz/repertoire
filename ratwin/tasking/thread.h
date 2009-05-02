// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\thread.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined I_4d2ad6e8_4511_11d3_aadb_0020af6bccd6
#define I_4d2ad6e8_4511_11d3_aadb_0020af6bccd6

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
types::HANDLE CreateThread (
    ulong stack_size,
    THREAD_START_ROUTINE start_address,
    void* param,
    ulong flags,
    ulong& id
    )
 { return reinterpret_cast<types::HANDLE>(::CreateThread (0, stack_size, reinterpret_cast<arg::arg32>(start_address), reinterpret_cast<arg::arg32>(param), flags, &id)); }

RATWIN_EXPORT
types::HANDLE CreateThread (ulong& id, THREAD_START_ROUTINE, void* argument);

inline
bool TerminateThread (types::HANDLE thd, ulong exitcode)
 { return ::TerminateThread (reinterpret_cast<arg::arg32>(thd), exitcode); }

inline
bool QueueUserAPC (void (__stdcall *func)(void*), types::HANDLE thr, void* data)
 {  return ::QueueUserAPC (reinterpret_cast<arg::arg32>(func), reinterpret_cast<arg::arg32>(thr), data); }

inline
bool GetThreadTimes (types::HANDLE thd, __int64& creation_time, __int64& exit_time, __int64& kernel_time, __int64& user_time)
 {  return ::GetThreadTimes (reinterpret_cast<arg::arg32>(thd), &creation_time, &exit_time, &kernel_time, &user_time); }

inline
types::HANDLE GetCurrentThread()
 {  return reinterpret_cast<types::HANDLE>( ::GetCurrentThread() ); }

inline
void ExitThread (int exitcode)
 {  ::ExitThread (reinterpret_cast<arg::arg32>(exitcode));  }
 
} //end tasking
}
ENDWRAP
#endif


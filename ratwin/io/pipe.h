// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\pipe.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_IO_PIPE_INCLUDED
#define RATWIN_IO_PIPE_INCLUDED

#include "ratwin\io\general.h"

extern "C" {
__declspec(dllimport) int __stdcall CreatePipe (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, const void*, unsigned long);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateNamedPipeA (
    const char* lpName,
    unsigned long dwOpenMode,
    unsigned long dwPipeMode,
    unsigned long nMaxInstances,
    unsigned long nOutBufferSize,
    unsigned long nInBufferSize,
    unsigned long nDefaultTimeOut,
    Dlugosz::ratwin::arg::arg32 security
    );

__declspec(dllimport) int __stdcall ConnectNamedPipe (Dlugosz::ratwin::arg::arg32, void*);
}

STARTWRAP
namespace ratwin {

namespace io {

inline
bool CreatePipe (types::HANDLE& read, types::HANDLE& write, ulong size)
 { return ::CreatePipe (reinterpret_cast<arg::arg32>(&read), reinterpret_cast<arg::arg32>(&write), 0, size); }

inline
bool CreatePipe (types::HANDLE& read, types::HANDLE& write, const types::SECURITY_ATTRIBUTES& sa, ulong size)
 { return ::CreatePipe (reinterpret_cast<arg::arg32>(&read), reinterpret_cast<arg::arg32>(&write), &sa, size); }

inline
ratwin::types::HANDLE CreateNamedPipe (
    const char* name,
    ulong open_mode,
    ulong pipe_mode,
    ulong max_instances,
    ulong out_buffer_size,
    ulong in_buffer_size,
    ulong default_time_out,
    void* SecurityAttributes
    )
 { return reinterpret_cast<ratwin::types::HANDLE>(::CreateNamedPipeA (name, open_mode, pipe_mode, max_instances, out_buffer_size, in_buffer_size, default_time_out, 0)); }

inline bool ConnectNamedPipe (types::HANDLE h, OVERLAPPED* ov)
 { return ::ConnectNamedPipe (reinterpret_cast<arg::arg32>(h), ov); }


} //end io

}
ENDWRAP
#endif


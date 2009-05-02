// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\general.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\io\general.h contains globals.  Include general=struct.h instead.
#endif

#include "ratwin\io\general=struct.h"

extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetStdHandle (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall ReadFile (Dlugosz::ratwin::arg::arg32, void*, unsigned long, unsigned long*, void*);
__declspec(dllimport) int __stdcall WriteFile (Dlugosz::ratwin::arg::arg32, const void*, unsigned long, unsigned long*, void*);
__declspec(dllimport) int __stdcall DuplicateHandle (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, void*, unsigned long, int, unsigned long);
__declspec(dllimport) int __stdcall ReadFileEx (Dlugosz::ratwin::arg::arg32, void*, unsigned long, void*, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall FlushFileBuffers (Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {
namespace io {


inline
types::IO_HANDLE GetStdHandle (StdHandle x)
 { return reinterpret_cast<types::IO_HANDLE> (::GetStdHandle (reinterpret_cast<arg::arg32>(x))); }

inline
bool ReadFile (types::IO_HANDLE h, void* dest, ulong size, ulong& sizeread)
 { return ::ReadFile (reinterpret_cast<arg::arg32>(h), dest, size, &sizeread, 0); }

inline
bool ReadFile (types::IO_HANDLE h, void* dest, ulong size, OVERLAPPED& ov, COMPLETION_ROUTINE proc)
 { return ::ReadFileEx (reinterpret_cast<arg::arg32>(h), dest, size, &ov, reinterpret_cast<arg::arg32>(proc)); }

inline
bool WriteFile (types::IO_HANDLE h, const void* src, ulong size, ulong& sizewritten)
 { return ::WriteFile (reinterpret_cast<arg::arg32>(h), src, size, &sizewritten, 0); }

// options for DuplicateHandle
const ulong DUPLICATE_CLOSE_SOURCE= 1;
const ulong DUPLICATE_SAME_ACCESS= 2;

template <typename T>
// T is derived from KernelHandle.  The template assures the result is the same type as the input, with no casting by the user.
inline
bool DuplicateHandle (types::HANDLE srcproc, T srch, types::HANDLE destproc, T& desth, ulong access, bool inherit, ulong options)
 {
 types::Kernel_HANDLE source= srch;  // check this contstraint at compile-time.  An error here means T is not compatible.
 return ::DuplicateHandle (reinterpret_cast<arg::arg32>(srcproc), reinterpret_cast<arg::arg32>(source), reinterpret_cast<arg::arg32>(destproc), &desth,
    access, inherit, options); }

inline
bool FlushFileBuffers (types::IO_HANDLE file)
 { return ::FlushFileBuffers (reinterpret_cast<arg::arg32>(file)); }

} //end io

}
ENDWRAP


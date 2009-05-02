// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\CompletionPort.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\CompletionPort.h contains globals.
#endif


#include "ratwin\io\general.h"

extern "C" {
__declspec(dllexport) ::Dlugosz::ratwin::arg::arg32 __stdcall CreateIoCompletionPort (::Dlugosz::ratwin::arg::arg32,::Dlugosz::ratwin::arg::arg32,unsigned long, unsigned long);
__declspec(dllexport) int __stdcall GetQueuedCompletionStatus (::Dlugosz::ratwin::arg::arg32, unsigned long*, unsigned long*, ::Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllexport) int  __stdcall PostQueuedCompletionStatus (::Dlugosz::ratwin::arg::arg32, unsigned long, unsigned long,::Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

namespace io {

inline
types::Kernel_HANDLE
CreateIoCompletionPort (types::IO_HANDLE FileHandle, types::Kernel_HANDLE ExistingCompletionPort, ulong CompletionKey, ulong NumberOfConcurrentThreads)
 {
 return reinterpret_cast<types::Kernel_HANDLE>( ::CreateIoCompletionPort(reinterpret_cast<arg::arg32>(FileHandle), reinterpret_cast<arg::arg32>(ExistingCompletionPort), CompletionKey, NumberOfConcurrentThreads) );
 }

inline
bool GetQueuedCompletionStatus (types::Kernel_HANDLE CompletionPort, ulong& NumberOfBytesTransferred, ulong& CompletionKey, OVERLAPPED** Overlapped, ulong Milliseconds)
 {
 return ::GetQueuedCompletionStatus (reinterpret_cast<arg::arg32>(CompletionPort), &NumberOfBytesTransferred, &CompletionKey, reinterpret_cast<arg::arg32>(Overlapped), Milliseconds);
 }

inline
bool PostQueuedCompletionStatus (types::Kernel_HANDLE CompletionPort, ulong NumberOfBytesTransferred, ulong CompletionKey, OVERLAPPED* Overlapped)
 {
 return ::PostQueuedCompletionStatus (reinterpret_cast<arg::arg32>(CompletionPort), NumberOfBytesTransferred, CompletionKey, reinterpret_cast<arg::arg32>(Overlapped));
 }
 
} //end io

}
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\heap.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\heap.h contains globals.  Include heap=struct.h instead.
#endif

#include "ratwin\heap=struct.h"
#include "ratwin\size_t.h"
#include "classics\flagword.h"

// DLL imports "cloaked" for overloading
extern "C" {
//   __declspec(dllimport) int __stdcall GetObjectA (Dlugosz::ratwin::arg::arg32, int, void*);
__declspec(dllimport) void* __stdcall GetProcessHeap();
__declspec(dllimport) int __stdcall GetProcessHeaps (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) void*__stdcall HeapAlloc (Dlugosz::ratwin::arg::arg32, unsigned long, size_t size);
// HeapCompact
__declspec(dllimport) void* __stdcall HeapCreate (Dlugosz::ratwin::arg::arg32, size_t, size_t);
// HeapDestroy
__declspec(dllimport) int __stdcall HeapFree (Dlugosz::ratwin::arg::arg32, unsigned long, void*);
// HeapLock
// HeapQueryInformation
// HeapReAlloc
// HeapSetInformation
// HeapSize
// HeapUnlock
__declspec(dllimport) int __stdcall HeapValidate (Dlugosz::ratwin::arg::arg32, unsigned long, void*);
// HeapWalk
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace heap {

inline
void* HeapAlloc (Heap hHeap, classics::flagword<alloc_flags_t> flags, size_t size)
 {
 return ::HeapAlloc (reinterpret_cast<arg::arg32>(hHeap), flags.validdata(), size);
 }

inline
void* HeapAlloc (Heap hHeap, size_t size)
 {
 return ::HeapAlloc (reinterpret_cast<arg::arg32>(hHeap), 0, size);
 }

inline
bool HeapFree (Heap hHeap, void* mem, bool no_serialize= false)
 {
 return ::HeapFree (reinterpret_cast<arg::arg32>(hHeap), no_serialize, mem);
 }

inline
Heap GetProcessHeap()
 {
 return static_cast<Heap>(::GetProcessHeap());
 }

inline
int GetProcessHeaps (int array_element_size, Heap array[])
 {
 return ::GetProcessHeaps (reinterpret_cast<arg::arg32>(array_element_size), array);
 }

inline
Heap HeapCreate (classics::flagword<alloc_flags_t> flags, size_t initial_commit_size=0, size_t max_size= 0)
 {
 return static_cast<Heap>(::HeapCreate (
    reinterpret_cast<arg::arg32>(flags.validdata()),
    initial_commit_size,
    max_size)
    );
 }

inline
Heap HeapCreate()
 {
 return static_cast<Heap>(::HeapCreate (reinterpret_cast<arg::arg32>(0), 0, 0));
 }

inline
bool HeapValidate (Heap hHeap,  bool no_serialize= false, void* mem= 0)
 {
 return ::HeapValidate (reinterpret_cast<arg::arg32>(hHeap), no_serialize, mem);
 }

}}
ENDWRAP


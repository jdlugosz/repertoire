// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\filemapping.h
// Revision: post-public build 6

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\io\filemapping.h contains globals.  Include filemapping=struct.h instead.
#endif

#include "ratwin\io\general.h"
#include "ratwin\io\filemapping=struct.h"

extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateFileMappingA (
   Dlugosz::ratwin::arg::arg32, void*, unsigned long, unsigned highsize, unsigned lowsize, const char*);
__declspec(dllimport) void* __stdcall MapViewOfFile (
   Dlugosz::ratwin::arg::arg32, unsigned long, unsigned highpos, unsigned lowpos, unsigned long);
__declspec(dllimport) int __stdcall UnmapViewOfFile (Dlugosz::ratwin::arg::arg32);


/*  not in here yet:
FlushViewOfFile 
MapViewOfFileEx 
OpenFileMapping 
*/



}
STARTWRAP
namespace ratwin {
namespace io {

inline
types::HANDLE CreateFileMapping (types::HANDLE file, page_protection protection, __int64 size, const char* name=0)
 {
 union {  __int64 whole; unsigned part[2]; };
 whole= size;
 return reinterpret_cast<types::HANDLE> (::CreateFileMappingA (reinterpret_cast<arg::arg32>(file), 0, protection, part[1], part[0], name) );
 }

// all access is 0x000F001F
inline
void* MapViewOfFile (types::HANDLE mapper, view_access_t access, __int64 pos, long len)
 {
 union {  __int64 whole; unsigned part[2]; };
 whole= pos;
 return ::MapViewOfFile (reinterpret_cast<arg::arg32>(mapper), access, part[1], part[0], len);
 }

inline
bool UnmapViewOfFile (void* p)
 {
 return ::UnmapViewOfFile (reinterpret_cast<arg::arg32>(p));
 }
 
} //end io
}
ENDWRAP


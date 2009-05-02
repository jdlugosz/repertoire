// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\filemapping.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_IO_FILEMAPPING_INCLUDED
#define RATWIN_IO_FILEMAPPING_INCLUDED

#include "ratwin\io\general.h"

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

enum page_protection { PAGE_READONLY= 2, PAGE_READWRITE=4 };
// VIEW_READONLY = SECTION_MAP_READ(4)
// VIEW_READWRITE = SECTION_MAP_WRITE(2) | SECTION_MAP_READ(4)
// VIEW_ALL_ACCESS = SECTION_QUERY(1) | SECTION_MAP_WRITE(2) | SECTION_MAP_READ(4) |
//                   SECTION_MAP_EXECUTE(8) | SECTION_MAP_EXTEND_SIZE(0x10) |
//                   DELETE(0x00010000) | READ_CONTROL(0x00020000) | WRITE_DAC(0x00040000) |
//                   WRITE_OWNER(0x00080000)
enum view_access_t { VIEW_READONLY=4, VIEW_READWRITE=6, VIEW_ALL_ACCESS=0x000F001F };

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
#endif



// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\filemapping=struct.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined Id493e490_4b7d_11d4_8e10_0006296222ef
#define Id493e490_4b7d_11d4_8e10_0006296222ef

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace io {

#if defined PAGE_READONLY || defined PAGE_READWRITE
#undef PAGE_READONLY
#undef PAGE_READWRITE
#endif

enum page_protection { PAGE_READONLY= 2, PAGE_READWRITE=4 };
// VIEW_READONLY = SECTION_MAP_READ(4)
// VIEW_READWRITE = SECTION_MAP_WRITE(2) | SECTION_MAP_READ(4)
// VIEW_ALL_ACCESS = SECTION_QUERY(1) | SECTION_MAP_WRITE(2) | SECTION_MAP_READ(4) |
//                   SECTION_MAP_EXECUTE(8) | SECTION_MAP_EXTEND_SIZE(0x10) |
//                   DELETE(0x00010000) | READ_CONTROL(0x00020000) | WRITE_DAC(0x00040000) |
//                   WRITE_OWNER(0x00080000)
enum view_access_t { VIEW_READONLY=4, VIEW_READWRITE=6, VIEW_ALL_ACCESS=0x000F001F };

 
} //end io
}
ENDWRAP
#endif



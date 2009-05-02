// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\crc32.h
// Revision: public build 8, shipped on 11-July-2006
#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif
namespace classics {

CLASSICS_EXPORT unsigned __int32 __stdcall crc32 (const void* buf, unsigned len, unsigned __int32 crc=0);
CLASSICS_EXPORT unsigned __int32 crc32_alternate (const void* buf, unsigned len, unsigned __int32 crc=0);

}


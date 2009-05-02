// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\LZexpand.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\LZexpand.h contains globals.
#endif


#include "ratwin\base.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) int __stdcall LZOpenFileA (Dlugosz::ratwin::arg::carg32, void*, unsigned);
__declspec(dllimport) int __stdcall LZOpenFileW (Dlugosz::ratwin::arg::carg32, void*, unsigned);
__declspec(dllimport) void __stdcall LZClose (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall LZCopy (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {

static const int OFS_MAXPATHNAME= 128;

struct OFSTRUCT {
   unsigned char cBytes;
   unsigned char fFixedDisk;
   unsigned nErrCode;
   unsigned Reserved1;
   unsigned Reserved2;
   char szPathName[OFS_MAXPATHNAME];
   OFSTRUCT() : cBytes('\x88') {}
   };

enum OF_flags {
   OF_READ= 0x00000000,
   OF_WRITE= 0x00000001,
   OF_READWRITE= 0x00000002,
   OF_SHARE_COMPAT= 0x00000000,
   OF_SHARE_EXCLUSIVE= 0x00000010,
   OF_SHARE_DENY_WRITE= 0x00000020,
   OF_SHARE_DENY_READ= 0x00000030,
   OF_SHARE_DENY_NONE= 0x00000040,
   OF_PARSE= 0x00000100,
   OF_DELETE= 0x00000200,
   OF_VERIFY= 0x00000400,
   OF_CANCEL= 0x00000800,
   OF_CREATE= 0x00001000,
   OF_PROMPT= 0x00002000,
   OF_EXIST= 0x00004000,
   OF_REOPEN= 0x00008000
   };

inline
int LZOpenFile (const char* name, OFSTRUCT& ofs, classics::flagword<OF_flags> flags)
 {
 return ::LZOpenFileA (reinterpret_cast<arg::carg32>(name), &ofs, flags.validdata());
 }

inline
int LZOpenFile (const wchar_t* name, OFSTRUCT& ofs, classics::flagword<OF_flags> flags)
 {
 return ::LZOpenFileW (reinterpret_cast<arg::carg32>(name), &ofs, flags.validdata());
 }

inline
void LZClose (int handle)
 {
 ::LZClose (reinterpret_cast<arg::arg32>(handle));
 }

inline
int LZCopy (int source, int dest)
 {
 return ::LZCopy (reinterpret_cast<arg::arg32>(source), reinterpret_cast<arg::arg32>(dest));
 }
 
} // end namespace ratwin
ENDWRAP


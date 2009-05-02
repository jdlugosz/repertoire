// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\INI_file.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\atom.h contains globals.
#endif

#include "ratwin\base.h"


extern "C" {
__declspec(dllimport) int __stdcall WritePrivateProfileStringW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall WritePrivateProfileStringA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall WriteProfileStringW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall WriteProfileStringA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
}

STARTWRAP
namespace ratwin {

inline
bool WritePrivateProfileString (const wchar_t* section, const wchar_t* key, const wchar_t* value, const wchar_t* file)
 {
 return ::WritePrivateProfileStringW (reinterpret_cast<arg::carg32>(section), reinterpret_cast<arg::carg32>(key), reinterpret_cast<arg::carg32>(value), reinterpret_cast<arg::carg32>(file));
 }

inline
bool WritePrivateProfileString (const char* section, const char* key, const char* value, const char* file)
 {
 return ::WritePrivateProfileStringA (reinterpret_cast<arg::carg32>(section), reinterpret_cast<arg::carg32>(key), reinterpret_cast<arg::carg32>(value), reinterpret_cast<arg::carg32>(file));
 }

inline
bool WriteProfileString (const wchar_t* section, const wchar_t* key, const wchar_t* value)
 {
 return ::WriteProfileStringW (reinterpret_cast<arg::carg32>(section), reinterpret_cast<arg::carg32>(key), reinterpret_cast<arg::carg32>(value));
 }

inline
bool WriteProfileString (const char* section, const char* key, const char* value)
 {
 return ::WriteProfileStringA (reinterpret_cast<arg::carg32>(section), reinterpret_cast<arg::carg32>(key), reinterpret_cast<arg::carg32>(value));
 }

} // end ratwin namespace
ENDWRAP


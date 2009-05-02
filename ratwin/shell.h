// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\shell.h
// Revision: post-public build 5

#pragma once
#if defined RATWIN_NoGlobals
   #error contains globals.
#endif

#include "ratwin\window=struct.h"

// DLL imports "cloaked" for overloading

extern "C" {
__declspec(dllimport) int __stdcall ShellExecuteA (Dlugosz::ratwin::arg::arg32, const char*, const char*, const char*, const char*, int);
__declspec(dllimport) int __stdcall ShellExecuteW (Dlugosz::ratwin::arg::arg32, const wchar_t*, const wchar_t*, const wchar_t*, const wchar_t*, int);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

inline
types::HINSTANCE ShellExecute (types::HANDLE parent_hwnd, const char* verb, const char* file, const char* parameters, const char* directory, window::SW_window showmode)
 {
 return reinterpret_cast<types::HINSTANCE>( ::ShellExecuteA(reinterpret_cast<arg::arg32>(parent_hwnd), verb, file, parameters, directory, showmode) );
 }


}
ENDWRAP


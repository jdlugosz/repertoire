// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\mouse.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_MOUSE_INCLUDED
#define RATWIN_MOUSE_INCLUDED

#include "ratwin\base.h"


// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetCapture();
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall SetCapture (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall ReleaseCapture();
__declspec(dllimport) int __stdcall GetCursorPos (Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

inline types::HWND GetCapture()
 {  return reinterpret_cast<types::HWND>(::GetCapture()); }

inline types::HWND SetCapture (types::HWND hwnd)
 {  return reinterpret_cast<types::HWND>(::SetCapture (reinterpret_cast<arg::arg32>(hwnd))); }

inline bool ReleaseCapture()
 {  return ::ReleaseCapture(); }

inline bool GetCursorPos (types::POINT& p)
 {
 return ::GetCursorPos (reinterpret_cast<arg::arg32>(&p));
 }

} // end of ratwin
ENDWRAP

#endif




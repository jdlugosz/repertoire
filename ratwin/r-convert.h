// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\r-convert.h
// Revision: post-public build 6

/* Usage:
  Include this file after everything else (both RatWin stuff and WINDOWS.H) and
  it will let you easily convert between equivilent types.

*/

#pragma once

inline ::HWND r (ratwin::types::HWND h) { return reinterpret_cast<::HWND>(h); }
inline ratwin::types::HWND r (::HWND h) { return reinterpret_cast<ratwin::types::HWND>(h); }
inline ::RECT* r (ratwin::types::RECT* p) { return reinterpret_cast<::RECT*>(p); }
inline ::RECT& r (ratwin::types::RECT& p) { return reinterpret_cast<::RECT&>(p); }
inline ratwin::types::RECT& r (::RECT& p) { return reinterpret_cast<ratwin::types::RECT&>(p); }
inline ratwin::types::HBRUSH r (::HBRUSH h) { return reinterpret_cast<ratwin::types::HBRUSH>(h); }
inline ::HBRUSH r (ratwin::types::HBRUSH h) { return reinterpret_cast<::HBRUSH>(h); }
inline ::POINT* r (ratwin::types::POINT* p) { return reinterpret_cast<::POINT*>(p); }
inline ::POINT& r (ratwin::types::POINT& p) { return reinterpret_cast<::POINT&>(p); }
inline ratwin::types::POINT& r (::POINT& p) { return reinterpret_cast<ratwin::types::POINT&>(p); }
inline ::HINSTANCE r (ratwin::types::HINSTANCE h) { return reinterpret_cast<::HINSTANCE>(h); }
inline ratwin::types::HINSTANCE r (::HINSTANCE h) { return reinterpret_cast<ratwin::types::HINSTANCE>(h); }


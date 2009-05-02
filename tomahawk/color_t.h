// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\color_t.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_COLOR_T_DEFINED
#define TOMAHAWK_COLOR_T_DEFINED

#include "tomahawk\base.h"
#include "ratwin\GDI.h"

STARTWRAP
namespace tomahawk {

class color_t {
   unsigned long Value;  //the actual binary representation of a COLORREF
public:
   color_t (byte red, byte green, byte blue)
      { Value= int(red) | (int(green)<<8) | (int(blue)<<16); }
   color_t (ratwin::gdi::system_color x)
      { Value= ratwin::gdi::GetSysColor (x); }
   color_t (unsigned long value) : Value(value) {}
   ulong value() const { return Value; }
   void value (ulong x)  { Value=x; }
   };

} //end tomahawk
ENDWRAP
#endif


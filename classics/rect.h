// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\rect.h
// Revision: post-public build 9

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\2D_point.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
struct generic_rect {
// This must match the layout of the Win32 RECT type!
   T left;
   T top;
   T right;
   T bottom;
   generic_rect (int left_, int top_, int right_, int bottom_)
      { left= left_; top= top_; right= right_; bottom= bottom_; }
   generic_rect()
      { left=top=right=bottom= 0; }
   bool hit (const generic_2D_point<T>& p) const
      { return p.x >= left && p.x < right && p.y >= top && p.y < bottom; }
   int width() const { return right-left; }
   int height() const { return bottom-top; }
   generic_2D_point<T> ul_corner() const  { return generic_2D_point<T> (left,top); }
   // will add more as I need them...
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\rect.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_RECT_INCLUDED
#define TOMAHAWK_RECT_INCLUDED

#include "tomahawk\base.h"
#include "ratwin\base.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class rect : public ratwin::types::RECT {
public:
   rect (int left_, int top_, int right_, int bottom_)
      { left= left_; top= top_; right= right_; bottom= bottom_; }
   rect()
      { left=top=right=bottom= 0; }
   bool hit (const point& p) const
      { return p.x >= left && p.x < right && p.y >= top && p.y < bottom; }
   int width() const { return right-left; }
   int height() const { return bottom-top; }
   point ul_corner() const  { return point(left,top); }
   // will add more as I need them...   
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP

#endif



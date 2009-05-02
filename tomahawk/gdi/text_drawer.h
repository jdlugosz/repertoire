// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\gdi\text_drawer.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_TEXT_DRAWER_INCLUDED
#define TOMAHAWK_TEXT_DRAWER_INCLUDED

#include "tomahawk\gdi\dc.h"

STARTWRAP
namespace tomahawk {

class text_drawer {
protected:
   rendering_dc& dc;
   point Pos;
   TOMAHAWK_EXPORT void output (const char*, int len=-1);
public:
   int lineheight;
   int leftedge;
   enum effect { endl };
   TOMAHAWK_EXPORT text_drawer (rendering_dc&);
   TOMAHAWK_EXPORT point pos();
   TOMAHAWK_EXPORT void pos (point);
   // formatted output
   text_drawer& operator<< (const char* s)  { output(s); return *this; }
   text_drawer& operator<< (char c)  { output (&c,1); return *this; }
   TOMAHAWK_EXPORT text_drawer& operator<< (const string&);
   TOMAHAWK_EXPORT text_drawer& operator<< (int);
   // manipulators
   TOMAHAWK_EXPORT void newline();
   TOMAHAWK_EXPORT text_drawer& operator<< (color_t);
   TOMAHAWK_EXPORT text_drawer& operator<< (effect);
   };

} // end of tomahawk
ENDWRAP
#endif



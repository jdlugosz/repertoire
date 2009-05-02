// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\mouse_capture.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_MOUSE_CAPTURE_INCLUDED
#define TOMAHAWK_MOUSE_CAPTURE_INCLUDED

#include "tomahawk\base.h"
#include "tomahawk\window.h"
#include "ratwin\mouse.h"

STARTWRAP
namespace tomahawk {

class mouse_capture {
public:
   mouse_capture (window* w)
      { ratwin::SetCapture (w->get_handle()); }
   ~mouse_capture()
      { ratwin::ReleaseCapture(); }
   };
   
} // end of tomahawk
ENDWRAP

#endif




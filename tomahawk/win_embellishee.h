// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\win_embellishee.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_WIN_EMBELLISHEE_INCLUDED
#define TOMAHAWK_WIN_EMBELLISHEE_INCLUDED

#include "tomahawk\window.h"
#include "tomahawk\embellishee.h"

STARTWRAP
namespace tomahawk {

class win_embellishee : public embellishee, public embellishment, virtual public window {
public:
   win_embellishee()
      { embellishee::add (classics::baro<embellishment>(this)); }
   void scrollpos_changed (point newpos)
      { scroll_contents (scrollpos()-newpos); }
   bool on_size (size_state, unsigned width, unsigned height)
      { embellishee::viewsize (point(width,height));  return true; }
   };


} // end of tomahawk
ENDWRAP

#endif



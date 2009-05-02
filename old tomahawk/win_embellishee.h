// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\win_embellishee.h
// Revision: public build 8, shipped on 11-July-2006

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



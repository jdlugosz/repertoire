// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\scroll.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined TOMAHAWK_SCROLL_INCLUDED
#define TOMAHAWK_SCROLL_INCLUDED

#include "ratwin\base.h"
#include "tomahawk\event_router\contributer.h"
#include "tomahawk\embellishment.h"

STARTWRAP
namespace tomahawk {

class embellishee;

class scroller : public embellishment, public event_router_n::contributer {
   embellishee* commlink;
   ratwin::types::HWND wnd;
   int pagesize;  //could figure out each time instead.
   int flags;
   int get_SB_type() const;
   int& halfpoint (point&) const;
   void setup (event_router_n::delegator&);
   void update_pos (event&, int oldpos, int position);
   void set_range ();
public:
   int pixelfactor;
   int linesize;
   enum direction { horizontal=0, vertical=1 };
   TOMAHAWK_EXPORT scroller (embellishee* commlink, event_router_n::delegator*, direction);
   TOMAHAWK_EXPORT bool delegated_event (event&, int id);
   bool process_event (event& x)  { return delegated_event(x,0); }
      // necessary for aggregation, pain for inheritance.
   // overrides for embellishment
   void scrollpos_changed (point newpos);
   void viewsize_changed (point newsize);
   };
   

}
ENDWRAP
#endif

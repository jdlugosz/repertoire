// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event_router\base.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_EventRouter_BASE_INCLUDED
#define TOMAHAWK_EventRouter_BASE_INCLUDED

#include "classics\pointers.h"
#include "tomahawk\base.h"

STARTWRAP
namespace tomahawk {

class event;     //in tomahawk\event.h

namespace event_router_n {


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class base : virtual public classics::can_handle {
public:
   enum size_state {SIZE_RESTORED, SIZE_MINIMIZED, SIZE_MAXIMIZED, SIZE_MAXSHOW, SIZE_MAXHIDE };
   virtual bool process_event (event&) =0;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of event_router_n
} // end of tomahawk
ENDWRAP

#endif

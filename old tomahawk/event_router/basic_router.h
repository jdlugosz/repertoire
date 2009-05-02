// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\event_router\basic_router.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EventRouter_BASIC_ROUTER_INCLUDED
#define TOMAHAWK_EventRouter_BASIC_ROUTER_INCLUDED

#include "tomahawk\event_router\elementary.h"
#include "tomahawk\event_router\delegator.h"

STARTWRAP
namespace tomahawk {
namespace event_router_n {

class basic_router : public delegator, public window_router, public bare_essentials {
public:
   basic_router() : window_router(this), bare_essentials(this) {}
   ~basic_router() {}
   };

}
} // end of tomahawk
ENDWRAP

#endif



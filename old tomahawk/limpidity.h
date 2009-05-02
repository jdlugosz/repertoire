// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\limpidity.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined TOMAHAWK_LIMPIDITY_INCLUDED
#define TOMAHAWK_LIMPIDITY_INCLUDED

#include "tomahawk\event_router\contributer.h"

STARTWRAP
namespace tomahawk {

class limpidity : public event_router_n::contributer {
protected:
   limpidity (event_router_n::delegator* d, const event_router_n::message_range& range)
      : contributer (d, range) {}
   bool delegated_event (event&, int id);
   virtual bool hittest (point p) =0;
   virtual bool relay_event (event&, int id) =0;
   virtual bool native_event (event&) =0;
public:
   TOMAHAWK_EXPORT void install_relay (event_router_n::delegator*);
   };

} // end of tomahawk
ENDWRAP

#endif




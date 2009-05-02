// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\event_router\bare_essentials.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EventRouter_BARE_ESSENTIALS_INCLUDED
#define TOMAHAWK_EventRouter_BARE_ESSENTIALS_INCLUDED

#include "ratwin\base.h"
#include "tomahawk\event_router\contributer.h"

STARTWRAP
namespace tomahawk {

namespace event_router_n {

class bare_essentials : public contributer {
   static message_range make_message_range();
   static message_range message_span;
   bool debug_click (event&);
public:
   TOMAHAWK_EXPORT bare_essentials (delegator* master);
   ~bare_essentials() {}
   TOMAHAWK_EXPORT bool delegated_event (event&, int id);
  // common message handlers
   enum wa_state { WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE };  //FIXED
   virtual bool on_activate (wa_state, bool minimize, ratwin::types::HWND other)  { return false; }
   virtual bool on_close()  { return false; }
   virtual bool on_command (int id, unsigned notification_code, ratwin::types::HWND)  { return false; }
   virtual bool on_destroy() { return false; }
   virtual bool on_enable (bool state)  { return false; }
   virtual bool on_keyboard (event&) { return false; }
   virtual bool on_mouse (event&) { return false; }    //change this...
   TOMAHAWK_EXPORT virtual bool on_move (point);
   virtual bool on_paint (event&)  { return false; }
   virtual bool on_size (size_state, unsigned width, unsigned height)  { return false; }
   };


}
} // end of tomahawk
ENDWRAP

#endif



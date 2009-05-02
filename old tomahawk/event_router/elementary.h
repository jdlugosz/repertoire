// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event_router\elementary.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined TOMAHAWK_EVENT_ROUTER_DEFINED
#define TOMAHAWK_EVENT_ROUTER_DEFINED

#include "ratwin\window.h"
#include "ratwin\message.h"
#include "tomahawk\event_router\bare_essentials.h"

STARTWRAP
namespace tomahawk {
namespace event_router_n {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class command {
public:
   virtual void execute() =0;
   void operator()() { execute(); }
   virtual ~command() {}
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class window_router : public contributer {
   static message_range make_message_range();
   static message_range message_span;
protected:
   ratwin::window::WNDPROC Old_proc;
   void call_old_proc (event& e) const;
public:
   ratwin::window::WNDPROC old_proc() const  { return Old_proc; }
   void old_proc (ratwin::window::WNDPROC x)  { Old_proc= x; }
   bool disable_subclass;
   TOMAHAWK_EXPORT window_router (delegator* master);
   ~window_router() {}
   TOMAHAWK_EXPORT static unsigned subclass_command_message;
   enum scm { scm_Ping, scm_Object, scm_TranslateKeyEvent, scm_Command };
   static bool translate_key_event (ratwin::types::HWND wnd, ratwin::message::MSG& msg)
      { return ratwin::window::SendMessage (wnd, subclass_command_message, scm_TranslateKeyEvent, &msg); }
   static int ping (ratwin::types::HWND wnd, int input)
      { return ratwin::window::SendMessage (wnd, subclass_command_message, scm_Ping, input); }
   static window_router* object (ratwin::types::HWND wnd)
      { return reinterpret_cast<window_router*>(ratwin::window::SendMessage (wnd, subclass_command_message, scm_Object)); }
   static void execute (ratwin::types::HWND wnd, command& instructions)
      { ratwin::window::SendMessage (wnd, subclass_command_message, scm_Command, &instructions); }
   virtual bool translate_key_event (ratwin::message::MSG&) { return false; }
   virtual void router_disengage_cleanup() {}
   // things you can override to customize the window
   TOMAHAWK_EXPORT bool delegated_event (event&, int id);
   virtual bool query_end()  { return true; }
   virtual bool query_maximize()  { return true; }
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


} // end of event_router_N

}
ENDWRAP

#endif


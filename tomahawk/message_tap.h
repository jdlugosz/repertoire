// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.h
// Revision: public build 5, shipped on 8-April-1999

/* A "message tap" is the mechanism for converting Windows messages
   into object member function calls.  This whole thing is encapsulated,
   so the actual mechanism can vary with each window if necessary.
*/   

#pragma once
#if !defined TOMAHAWK_MESSAGE_TAP_DEFINED
#define TOMAHAWK_MESSAGE_TAP_DEFINED

#include "tomahawk\base.h"
#include "ratwin\window.h"
#include "tomahawk\event_router\elementary.h"

STARTWRAP
namespace tomahawk {

class message_tap {
public:
   typedef event_router_n::window_router event_router;
   static long __stdcall message_tap::install_hook (ratwin::types::HWND wnd, unsigned mess, unsigned p1, ulong p2);
   void pre_create (event_router*, ratwin::window::WNDPROC);
   static void post_create (ratwin::types::HWND wnd);
   virtual void link (ratwin::types::HWND, event_router&) =0;     //install my object pointer
   virtual void unlink (ratwin::types::HWND, event_router&) =0;   //restore old window function
   TOMAHAWK_EXPORT ratwin::window::WNDPROC subclass (ratwin::types::HWND, ratwin::window::WNDPROC Old_proc);  //replaces windows procedure
   };

class message_tap_1 : public message_tap {
public:
   TOMAHAWK_EXPORT virtual void link (ratwin::types::HWND, event_router&);
   TOMAHAWK_EXPORT virtual void unlink (ratwin::types::HWND, event_router&);
   static message_tap_1 instance;
   };

class message_tap_2 : public message_tap {
public:
   TOMAHAWK_EXPORT virtual void link (ratwin::types::HWND, event_router&);
   TOMAHAWK_EXPORT virtual void unlink (ratwin::types::HWND, event_router&);
   static message_tap_2 instance;
   };
   
}
ENDWRAP
#endif


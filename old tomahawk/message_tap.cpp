// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\message_tap.h"
#include "tomahawk\event.h"
#include "tomahawk\event_router\elementary.h"

STARTWRAP
namespace tomahawk {

message_tap_1 message_tap_1::instance;
message_tap_2 message_tap_2::instance;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {
__declspec(thread) ratwin::window::WNDPROC old_proc;
// Borland 5.0 doesn't like the declarations.  Introducing the typedef is a work-around.
typedef message_tap* mytap_type;
__declspec(thread) mytap_type mytap= 0;
typedef event_router_n::window_router* object_type;
__declspec(thread) object_type object= 0;


// the internal helpers are all grouped together here, rather than declared
// with the stuff that uses it, because Borland 5.0 has troubles with
// multiple unnamed namespaces.
long __stdcall hook1 (ratwin::types::HWND wnd, unsigned mess, unsigned p1, ulong p2)
 {
 event_router_n::window_router* object= static_cast<event_router_n::window_router*>(ratwin::window::GetWindowLong (wnd, 0));
 event e (wnd, mess, p1, p2);
 object->process_event (e);
 return e.ret;
 }


long __stdcall hook2 (ratwin::types::HWND wnd, unsigned mess, unsigned p1, ulong p2)
 {
 using ratwin::window::GWL_USERDATA;
 event_router_n::window_router* object= static_cast<event_router_n::window_router*>(ratwin::window::GetWindowLong (wnd, GWL_USERDATA));
 event e (wnd, mess, p1, p2);
 object->process_event (e);
 return e.ret;
 }

}

void message_tap::pre_create (event_router_n::window_router* x, ratwin::window::WNDPROC proc)
 {
 if (mytap)  throw "hook failure!";
 mytap= this;
 object= x;
 old_proc= proc;
 }

void message_tap::post_create (ratwin::types::HWND wnd)
 {
 if (mytap) {
    mytap->link (wnd, *object);
    mytap= 0;
    }
 }

long __stdcall message_tap::install_hook (ratwin::types::HWND wnd, unsigned mess, unsigned p1, ulong p2)
 {
 // first message has been received.  Install the tap.
 if (mytap) {
    mytap->link (wnd, *object);
    object->old_proc (old_proc);
    mytap= 0;    //for error checking in prepare_to_hook, and
                 //watching for cached send's during window creation.
    }             
 event e (wnd, mess, p1, p2);
 object->process_event (e);
 return e.ret;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::window::WNDPROC message_tap::subclass (ratwin::types::HWND hwnd, ratwin::window::WNDPROC proc)
 {
 if (!hwnd)  throw "can't subclass without a window handle!";
 using namespace ratwin::window;
 return reinterpret_cast<WNDPROC>(SetWindowLong (hwnd, GWL_WNDPROC, proc));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap_1::link (ratwin::types::HWND hwnd, event_router_n::window_router& er)
 {
 if (!hwnd)  throw "can't link without a window handle!";
 using namespace ratwin::window;
 const int data_offset= 0;
 SetWindowLong (hwnd, data_offset, &er);
        // that's the stuff that might get altered.  Break it
        // into its own virtual function.
 er.old_proc (subclass(hwnd,&hook1));
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap_1::unlink (ratwin::types::HWND, event_router_n::window_router&)
// ... promote this to the base class, since restoring the old
// windows procedure is general behavior.  I don't need to
// do anything with the data pointer.
// ... but, WHEN is unlink performed?  Window shutdown needs
// to accomplish this, so I need to call this from the router.
// general idea: have router maintain a pointer back to the tap object?
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap_2::link (ratwin::types::HWND hwnd, event_router_n::window_router& er)
 {
 if (!hwnd)  throw "can't link without a window handle!";
 using namespace ratwin::window;
 const int data_offset= GWL_USERDATA;
 SetWindowLong (hwnd, data_offset, &er);
 er.old_proc (subclass(hwnd,&hook2));
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap_2::unlink (ratwin::types::HWND, event_router_n::window_router&)
 {
 }


}
ENDWRAP


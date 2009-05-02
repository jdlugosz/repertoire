// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event_router\elementary.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\event.h"
#include "tomahawk\event_router\elementary.h"
#include "ratwin\WM_constants.h"

STARTWRAP

namespace tomahawk {
namespace event_router_n {

using namespace ratwin::WM_constants;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

unsigned window_router::subclass_command_message= ratwin::message::RegisterWindowMessage ("Dlugosz::Tomahawk");

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window_router::call_old_proc (event& e) const
 {
 e.ret= ratwin::window::CallWindowProc (Old_proc, e.wnd, e.message, e.wp, e.lp);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range window_router::make_message_range()
 {
 using ratwin::message::MSG;
 message_range x;
#if 0
 x << subclass_command_message << WM_QUERYENDSESSION
   << WM_QUERYOPEN << WM_NCDESTROY  << 0 << 0xffff;
#else
 // since this also handles the old_proc case, need to trap *all* messages.
 x << 0 << ~0;
#endif
 return x;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range window_router::message_span= make_message_range();

window_router::window_router (delegator* master)
 : disable_subclass(false), Old_proc(0),
   contributer (master, message_span, classics::high(classics::Late))
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
bool window_router::delegated_event (event& e, int)
 {
 if (disable_subclass)  call_old_proc (e);
 else if (e.message == subclass_command_message) {
    using ratwin::message::MSG;
    switch (e.wp) {
       case scm_Ping:
          e.ret= -e.lp;
          break;
       case scm_TranslateKeyEvent:
          e.ret= translate_key_event (*static_cast<MSG*> (e.plp));
          break;
       case scm_Object:
          e.pret= reinterpret_cast<void*> (this);
          break;
       case scm_Command: {
          command* instructions= static_cast<command*>(e.plp);
          instructions->execute();
          }  break;
       }
    }
 else {
    switch (e.message) {
       case WM_QUERYENDSESSION:
          e.ret= query_end();
          break;
       case WM_QUERYOPEN:
          e.ret= query_maximize();
          break;
       case WM_NCDESTROY:
          //note the order
          call_old_proc (e);
          router_disengage_cleanup();  //done last.
          throw Cancel;  //don't do any more processing!
       default:
          // keep this here? Why not.
          call_old_proc (e);
          return true;

       }//end of switch
    }   
 return true;
 }


} // end of event_router_n
} // end of tomahawk
ENDWRAP


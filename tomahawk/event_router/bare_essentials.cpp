// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event_router\bare_essentials.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "ratwin\WM_constants.h"
#include "ratwin\keyboard.h"
#include "ratwin\utilities.h"
#include "tomahawk\event.h"
#include "tomahawk\event_router\bare_essentials.h"
#include <typeinfo.h>

STARTWRAP

namespace tomahawk {
namespace event_router_n {
using namespace ratwin::WM_constants;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range bare_essentials::make_message_range()
 {
 message_range x;
 x << WM_PAINT << WM_ACTIVATE << WM_ENABLE << WM_MOVE
   << WM_CLOSE << WM_DESTROY << WM_COMMAND << WM_SIZE;
 return x;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range bare_essentials::message_span= make_message_range();

bare_essentials::bare_essentials (delegator* master)
 : contributer (master, message_span)
 { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool bare_essentials::debug_click (event& e)
 {
 using ratwin::util::MessageBox;
 using ratwin::keyboard::GetKeyState;
 using ratwin::keyboard::VK_SCROLL;
 if (e.message == WM_RBUTTONDOWN && (GetKeyState(VK_SCROLL)&1)) {
    MessageBox (typeid(*this).name(), "C++ Class");
    return true;
    }
 return false;   
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool bare_essentials::delegated_event (event& e, int)
 {
 const unsigned message= e.message;
 /***** will move these to other contributers ***/
 if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
    on_keyboard (e);
 if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST) {
    if (!debug_click (e))  return on_mouse (e);   //change to unpack, later.
    }
 /***************************/
 switch (message) {
    case WM_PAINT: 
       return on_paint (e);
    case WM_ACTIVATE:
       return on_activate (wa_state(e.xwp.lo), e.xwp.hi, static_cast<ratwin::types::HWND>(e.plp));
    case WM_ENABLE:
       return on_enable (e.wp);
    case WM_MOVE:
       return on_move (point(e.xlp.lo, e.xlp.hi));
    case WM_CLOSE:
       return on_close();
    // what about WM_SYSCOMMAND ?   
    case WM_DESTROY:
       return on_destroy();
    case WM_COMMAND:
       return on_command (e.xwp.lo, e.xwp.hi, static_cast<ratwin::types::HWND>(e.plp));
    case WM_SIZE:
       return on_size (size_state(e.wp), e.xlp.lo, e.xlp.hi);
    }
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool bare_essentials::on_move (point)
 {
 return false;
 }


} // end of event_router_n
} // end of tomahawk
ENDWRAP


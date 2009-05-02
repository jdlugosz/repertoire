// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tab_contributer.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\tab_contributer.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\event.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

using event_router_n::message_range;

static message_range& make_message_range()
 {
 using namespace ratwin::WM_constants;
 message_range x;
 x << WM_NOTIFY;
 return x;
 }

static message_range message_span= make_message_range();

tab_contributer::tab_contributer (event_router_n::delegator* master)
 : contributer (master, message_span)
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static controls::tab::handle gh (ratwin::types::HWND h)
 {
 // this will be replaced with a centralized "query interface"-like function.
 using event_router_n::window_router;
 using controls::tab;
 window_router* p1= window_router::object (h);
 tab* p2= dynamic_cast<tab*>(p1);
 return tab::handle (p2);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool tab_contributer::delegated_event (event& e, int id)
 {
 if (e.message != ratwin::WM_constants::WM_NOTIFY)  return false;
 ratwin::WM_constants::NMHDR* data= static_cast<ratwin::WM_constants::NMHDR*>(e.plp);
 switch (data->code) {
    case data->TCN_SELCHANGE:
       selection_changed (gh(data->sender));
       break;
    case data->TCN_SELCHANGING:
       e.ret= selection_changing (gh(data->sender));
       break;
    default:
       return false;
    }
 return true;
 }
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool tab_contributer::selection_changing (controls::tab::handle control)
 {
 controls::tab::info* data= control->get_data();
 prev= control;  //just remember it
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tab_contributer::selection_changed (controls::tab::handle control)
 {
 controls::tab::info* data= control->get_data();
 if (prev)  data->change_from (prev);
 else data->activate();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
}
ENDWRAP


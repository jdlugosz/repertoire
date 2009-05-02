// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\multimatte=drag_slider.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\multimatte.h"
#include "tomahawk\event.h"
#include "tomahawk\window_factory.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\cursor.h"
#include "ratwin\utilities.h"  //will remove later.
#include "tomahawk\multimatte=drag_slider.h"

STARTWRAP
namespace tomahawk {
using tomahawk::event_router_n::message_range;


static message_range get_drag_range()
 {
 using namespace ratwin::WM_constants;
 message_range range;
 range << WM_LBUTTONUP << WM_MOUSEMOVE;
 return range;
 }

static message_range slide_range (get_drag_range());

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

multimatte::drag_slider::drag_slider (multimatte* p, multimatte::hitlist selection)
 : object(p), selection(selection), mcap(p)
 {
 delegator::delegate::baro me (this);
 me.own(true);
 classics::schedule_t schedule= classics::high(classics::Normal);
 delegator::delegate data (slide_range, me, schedule);
 object->add (data);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool dragger::delegated_event (event& e, int id)
 {
 using namespace ratwin::WM_constants;
 switch (e.message) {
    case WM_LBUTTONUP:
       return drag_done (e);
    case WM_MOUSEMOVE:
       return drag_to (point(e.xlp.lo, e.xlp.hi));
    default:
       return false;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::drag_slider::drag_to (point p)
 {
 object->drag (selection, p);
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::drag_slider::drag_done (event&)
 {
 object->refit();
 object->remove (this);
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

multimatte::drag_slider::~drag_slider()
 {
 static int count= 0;
 ++count;
 }



} // end of tomahawk
ENDWRAP



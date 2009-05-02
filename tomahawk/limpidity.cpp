// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\limpidity.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\limpidity.h"
#include "tomahawk\event.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\event_router\delegator.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool limpidity::delegated_event (tomahawk::event& e, int id)
 {
 using namespace ratwin::WM_constants;
 if (id == 1)  return relay_event (e,id);
 else switch (e.message) {
    case WM_NCHITTEST: {
       const int HTTRANSPARENT= -1;
       // will collect these into a hittest enum or something.
       point p (e.xlp.lo, e.xlp.hi);
       if (hittest(p))  return false;  //don't mess with it -- normal meaning.
       else {  //hit a transparent region.
          e.ret= HTTRANSPARENT;
          return true;  //handled it fully
          }
       } break;
    default: return  native_event (e);  //all other events
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void limpidity::install_relay (event_router_n::delegator* parent)
 {
 using namespace event_router_n;
 message_range range;
 range << ratwin::WM_constants::WM_SIZE;
 // this needs to be made more general for reuse.
 // or, why bother with this function, since that's all there is to it?
 event_router_n::delegator::delegate x (range, classics::baro<contributer>(this), classics::always (classics::Normal), 1);
 parent->add (x);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


} // end of tomahawk
ENDWRAP




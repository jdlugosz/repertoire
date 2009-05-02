// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\scroll.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "classics\exception.h"
#include "ratwin\WM_constants.h"
#include "ratwin\window.h"
#include "tomahawk\scroll.h"
#include "tomahawk\event.h"
#include "tomahawk\embellishee.h"
#include "tomahawk\event_router\delegator.h"  //may not need this line, later
#include "classics\string_ios.h"  //for formatting error messages

using std::endl;
using classics::wFmt;

STARTWRAP
namespace tomahawk {
using namespace event_router_n;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static message_range make_span()
 {
 using namespace ratwin::WM_constants;
 message_range x;
 x << WM_VSCROLL << WM_HSCROLL;
 return x;
 }
 
static message_range message_span= make_span();

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

scroller::scroller (embellishee* commlink, delegator* master, direction dir)
: contributer(master,message_span), commlink(commlink), pixelfactor(1), linesize(1), wnd(0)
 { 
 flags= dir;
 commlink->add (classics::baro<embellishment>(this));

 // temporary scaffolding -- need to deal with aggregated objects' lifetime.
// get_lifetime_object()->inc_owned_count();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int scroller::get_SB_type() const
 {
 // The last two bits of flags are:
 //  2: set for control, clear for standard control bar
 //  1: set for vertical, clear for horizontal
 // This function returns the right constant for communicating with the scroll bar
 // via SendMessage.
 enum { SB_HORZ=0, SB_VERT=1, SB_CTL=2 };
 switch (flags & 3) {
    case 0:  return SB_HORZ;  //standard horizontal scroll bar
    case 1:  return SB_VERT;  //standard vertical scroll bar
    default: /* 2 or 3 */  return SB_CTL;   //scroll control window
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int& scroller::halfpoint (point& p) const
// pick the correct half of the point structure that I want, based
// on the scrollbar's direction.
 {
 return (flags&1) ? p.y : p.x;  //as an l-value
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void scroller::set_range ()
 {
 using namespace ratwin::window;
 const int high= halfpoint(commlink->pagesize()) - 1;
    ratwin::types::RECT r;
    ratwin::window::GetClientRect (wnd, r);
    const int size= flags&1 ? r.bottom : r.right;
    pagesize= size / pixelfactor;
 SCROLLINFO info= {sizeof info, pagesize==-1?1:3, 0, high, pagesize };
 SetScrollInfo (wnd, get_SB_type(), info);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool scroller::delegated_event (event& e, int id)
 {
 using namespace ratwin::WM_constants;
 const unsigned message= e.message;
 int position= halfpoint (commlink->scrollpos());
 int oldposition= position;
 if (!wnd) {
    // "standard" scrollbar figures out the window here.
    wnd= e.wnd;
    set_range();
    }
 if (id == 0) {   // primary contributer call
    const int trigger= flags&1 ? WM_VSCROLL : WM_HSCROLL;
    if (message == trigger) {
       switch (e.xwp.lo) {
          case 0:  // SB_LINEUP
             position -= linesize;
             break;
          case 1:  // SB_LINEDOWN
             position += linesize;
             break;
          case 2:  // SB_PAGEDOWN
             position -= pagesize;
             break;
          case 3:  // SB_PAGEUP
             position += pagesize;
             break;
          case 4:  // SB_THUMBPOSITION
          case 5:  // SB_TRACKPOSITION
             position= e.xwp.hi;
             break;
          case 6:  // SB_TOP
          case 7:  // SB_BOTTOM
          case 8:  // SB_ENDSCROLL
   	      ;
          }
       const int high= halfpoint(commlink->pagesize())-1;
       const int max= high-pagesize+1;
       if (position < 0)  position= 0;
       else if (position > max)  position= max;
       if (position != oldposition)  update_pos (e, oldposition, position);
       return true;
       }
    return false;
    }
 else {
    classics::exception X ("Tomahawk", "Invalid Interface ID", __FILE__, __LINE__);
    wFmt(X) << L"ID is " << id << L"." << endl;
    throw X;
    }
 return false;  //stupid compiler
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void scroller::viewsize_changed (point newsize)
 {
 pagesize= halfpoint (newsize) / pixelfactor;
 using namespace ratwin::window;
 SCROLLINFO info= {sizeof info, 2, 0, 0, pagesize };
 SetScrollInfo (wnd, get_SB_type(), info);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void scroller::update_pos (event& e, int oldpos, int position)
 {
 point newpos= commlink->scrollpos();
 halfpoint (newpos)= position;
 commlink->scrollpos (newpos);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void scroller::scrollpos_changed (point newpos)
 {
 using namespace ratwin::window;
 SCROLLINFO info= {sizeof info, 4 };
 info.nPos= halfpoint (newpos);
 SetScrollInfo (wnd, get_SB_type(), info);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}  //end namespace
ENDWRAP



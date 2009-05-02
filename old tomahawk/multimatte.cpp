// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\multimatte.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\multimatte.h"
#include "tomahawk\event.h"
#include "tomahawk\window_factory.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\cursor.h"
#include "ratwin\utilities.h"  //will remove later.
#include "tomahawk\multimatte=drag_slider.h"
#include "tomahawk\global.h"


namespace tomahawk {
  
using tomahawk::event_router_n::message_range;
using classics::alias;

// these can't be static members because the ModuleHandle will be set in DLLMain,
// not looked up each time.  Also, make the stock cursors part of a cursors module.
// update: module_handle now set before any static construction.
cursor multimatte::h_slider (module_handle, "H_SPLITTER");
cursor multimatte::v_slider (module_handle, "V_SPLITTER");
cursor multimatte::hv_slider (module_handle, "HV_SPLITTER");


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static message_range get_range()
 {
 using namespace ratwin::WM_constants;
 message_range range;
 range << WM_NCHITTEST << WM_LBUTTONDOWN << WM_SETCURSOR;
 return range;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static message_range span (get_range());

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

multimatte::handle multimatte::createnew (window* wnd)
 {
 multimatte* p= new multimatte;
 handle h (p);
 p->create ("multimatte", wnd);
 p->install_relay (wnd);
 return h;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

multimatte::multimatte()
 : limpidity (this, span)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tomahawk::window_factory& multimatte::get_default_factory()
 {
 // factory concept still needs work.
 static tomahawk::window_factory_userdef wc ("hotspot class");
 if (!wc.registered()) {
    using namespace ratwin::window;
    wc.background (0);
    wc.window_factory::style = WS_CHILD | WS_VISIBLE;
    wc.window_factory::style2= WS_EX_TRANSPARENT;
    /////
    }
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::hittest (point p)
 {
 p= screen_to_client(p);
 int result= 0;
 for (classics::const_iterator<slider_t> it (Sliders); it; ++it) {
    if (it->hitarea.hit(p))  {
       result |= it->vertical ? HitVertical : HitHorizontal;
       if (result == HitBoth)  break;  //no need to continue checking.
	   }
    }
 last_hit= static_cast <hit_result> (result);
 return result;  //0 means nothing, compatible with "false".
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::relay_event (event& e, int id)
 {
 using namespace ratwin::WM_constants;
 if (e.message == WM_SIZE)
    move (point(0,0), e.xlp.lo, e.xlp.hi);
 return false;  //continue with processing.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::set_cursor (hit_result value) const
 {
 static cursor* list[3]= { &h_slider, &v_slider, &hv_slider };
 unsigned index= value-1;
 if (index > 2)  return;  //improper use; do nothing
 list[index]->make_active();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::native_event (event& e)
 {
 using namespace ratwin::WM_constants;
 switch (e.message) {
    case WM_LBUTTONDOWN:
       new drag_slider (this, make_hitlist(point(e.xlp.lo, e.xlp.hi)));
       return true;
    case WM_SETCURSOR:
       set_cursor (last_hit);
       return true;  //handled it fully
    }
 return false;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::do_matte() const
 {
 const int arraysize= Requests.elcount();
 for (int loop= 0;  loop < arraysize;  loop++) {
    const matte_request& p= Requests[loop];
    int left= ControlValues[p.left].value;
    int top= ControlValues[p.top].value;
    int width= ControlValues[p.right].value-left;
    int height= ControlValues[p.bottom].value-top;
    (p.wnd)-> move (point(left,top), width,height);
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::add_control_value_prop (int n, int p1, int p2, int num, int denom)
 {
 if (ControlValues.elcount() <= n)  ControlValues.resize (n+1);
 ControlValues[n].prop (p1, p2, num, denom);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::add_control_value_fixed (int n, int p1, int delta)
 {
 if (ControlValues.elcount() <= n)  ControlValues.resize (n+1);
 ControlValues[n].fixed (p1, delta);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::control_value_t::prop (int p1_, int p2, int num, int denom)
 {
 p1= p1_;
 p2_or_op= p2;
 k= (32*1024)*num/denom;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::control_value_t::fixed (int p1_, int k_)
 {
 p1= p1_;
 p2_or_op= 255;
 k= k_;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool multimatte::on_size (size_state, unsigned width, unsigned height)
 {
 const int max= ControlValues.elcount();
 if (max >= 4) {
    ControlValues[0].value= 0;
    ControlValues[1].value= 0;
    ControlValues[2].value= width;
    ControlValues[3].value= height;
    }
 for (int loop= 4;  loop < max;  loop++) {
    ControlValues[loop].compute (ControlValues);
    }
 do_matte();
 update_sliders();
 return false;  //continue with default processing
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::control_value_t::compute (const pointarray& cv)
 {
 int left= cv[p1].value;
 if (p2_or_op == 255) {
    //constant mode
    value= left + k;
    }
 else {
    //proportional mode
    int right= cv[p2_or_op].value;
    value= left + (right-left) * k / (32*1024);
    }
 }
 
void multimatte::control_value_t::refit (const pointarray& cv)
// This is the inverse function of compute().  Solve for 'k' given 'value'.
 {
 if (p2_or_op == 255) {
    return;  //no change to constant mode values.
    // need to decide what to do if the size is too small.
    }
 int left= cv[p1].value;
 int right= cv[p2_or_op].value;
 k= (32*1024*value-left)/(right-left);
 // need to come up with a way to do them in proper order.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::add_request (const window::handle& wnd, int left, int top, int right, int bottom)
 {
 matte_request x;
 x.wnd= wnd;
 x.left= left;
 x.top= top;
 x.right= right;
 x.bottom= bottom;
 Requests.append (x);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::add_slider (bool vertical, int cv, int edge1, int edge2)
 {
 slider_t x;
 x.vertical= vertical;
 x.cv= cv;
 x.edge1= edge1;
 x.edge2= edge2;
 Sliders.append (x);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::update_sliders()
 {
 for (classics::iterator<slider_t> it (Sliders, alias); it; ++it) {
    it->compute_hit_rectangle (ControlValues);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void multimatte::refit()
 {
 classics::iterator<control_value_t> it (ControlValues,alias);
 ++it; ++it; ++it; ++it;
 while (it) {
    it->refit (ControlValues);
    ++it;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::slider_t::compute_hit_rectangle (const pointarray& controls)
 {
 const int widen= 2;
 // move "north/south", slider's line is drawn "east/west".  Only last,
 // decide which is horizontal and which is vertical.
 int north= controls[cv].value - widen;  //left or top - direction of slide
 int south= north + 2*widen;
 int east= controls[edge1].value - widen;
 int west= controls[edge2].value + widen;
 hitarea= vertical ?
    rect (east, north, west, south) : rect (north, east, south, west);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

multimatte::hitlist multimatte::make_hitlist (point p)
 {
 hitlist result;
 int loop= 0;
 for (classics::const_iterator<slider_t> it (Sliders); it; ++it, ++loop) {
    if (it->hitarea.hit(p))  result.append(loop);
    }
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void multimatte::drag (const hitlist& selection, point p)
 {
 const int max= selection.elcount();
 for (int loop= 0;  loop < max;  loop++) {
    slider_t& slider= Sliders[selection[loop]];
    int val= slider.vertical ? p.y : p.x;
    ControlValues[slider.cv].value= val;
    }
 update_sliders();
 do_matte();
 }


}



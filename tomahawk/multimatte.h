// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\multimatte.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_MULTIMATTE_INCLUDED
#define TOMAHAWK_MULTIMATTE_INCLUDED

#include "tomahawk\window.h"
#include "tomahawk\win_embellishee.h"
#include "tomahawk\scroll.h"
#include "tomahawk\rect.h"
#include "tomahawk\limpidity.h"
#include "tomahawk\mouse_capture.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class cursor;

class multimatte : public tomahawk::created_window, public limpidity {
public:
    class control_value_t {
       byte p1;
       byte p2_or_op;
       short k;
    public:
       int value;
       void prop (int p1, int p2, int num, int denom);
       void fixed (int p1, int k);
       void compute (const classics::vararray_s <control_value_t>&);
       void refit (const classics::vararray_s <control_value_t>&);
       };
   typedef classics::vararray_s <control_value_t> pointarray;
   struct slider_t {
      byte cv;  //the point that I'm controling
      byte edge1, edge2;  //delimits the control
      byte vertical;
      rect hitarea;
      void compute_hit_rectangle (const pointarray&);
      };
   typedef classics::vararray_s <slider_t> slider_array_t;
   slider_array_t Sliders;
protected:
   enum hit_result { HitNothing=0, HitHorizontal=1, HitVertical=2, HitBoth=3 };
   bool hittest (point p);
   hit_result last_hit;
   pointarray ControlValues;
   struct matte_request {
      window::handle wnd;
      int left,top,right,bottom;
      };
   classics::vararray_g <matte_request> Requests;
   bool relay_event (event&, int id);
   bool native_event (event&);
   class drag_slider;
   void set_cursor (hit_result) const;
public:
   typedef classics::handle<multimatte> handle;
   tomahawk::window_factory& get_default_factory();
   TOMAHAWK_EXPORT multimatte();
   TOMAHAWK_EXPORT static handle createnew (window*);
   TOMAHAWK_EXPORT void add_control_value_prop (int n, int p1, int p2, int num, int denom);
   TOMAHAWK_EXPORT void add_control_value_fixed (int n, int p1, int delta);
   pointarray read_control_values() const { return ControlValues; }
   pointarray access_control_values() { return pointarray(ControlValues, classics::alias); }
   TOMAHAWK_EXPORT void do_matte () const;
   TOMAHAWK_EXPORT void add_request (const window::handle& wnd, int left, int top, int right, int bottom);
   TOMAHAWK_EXPORT void add_slider (bool vertical, int cv, int edge1, int edge2);
   TOMAHAWK_EXPORT virtual void update_sliders();
   void add_vertical_slider (int cv, int edge1, int edge2)
      { add_slider (true, cv, edge1, edge2); }
   void add_horizontal_slider (int cv, int edge1, int edge2)
      { add_slider (false, cv, edge1, edge2); }
   bool on_size (size_state, unsigned width, unsigned height);
   typedef classics::vararray_s<int> hitlist;
   hitlist make_hitlist (point);  //find out which sliders are affected
   void drag (const hitlist&, point);  //move sliders.
   void refit();  //update "request" rules based on current dragged position.
   TOMAHAWK_EXPORT static cursor h_slider;
   TOMAHAWK_EXPORT static cursor v_slider;
   TOMAHAWK_EXPORT static cursor hv_slider;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of namespace
ENDWRAP
#endif



// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\multimatte=drag_slider.h
// Revision: public build 6, shipped on 28-Nov-1999

// Only included in implementation file.

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// later, make dragger stand-alone and reusable.

class dragger : public event_router_n::contributer {
protected:
   bool delegated_event (event&, int id);
   virtual bool drag_to (point) =0;
   virtual bool drag_done (event&) =0;
public:
   TOMAHAWK_EXPORT void install_relay (event_router_n::delegator*);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class multimatte::drag_slider : public dragger {
   bool process_event (event&)  { return false; }
   multimatte* object;
   multimatte::hitlist selection;  //what I'm sliding.
   bool drag_done (event&);
   bool drag_to (point);
   ~drag_slider();
   mouse_capture mcap;
public:
   drag_slider (multimatte*, multimatte::hitlist);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP





// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\dialog_window.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined TOMAHAWK_DIALOG_WINDOW_INCLUDED
#define TOMAHAWK_DIALOG_WINDOW_INCLUDED

#include "tomahawk\window.h"

STARTWRAP
namespace tomahawk {

namespace controls {
   class control_base;
   }
   
class dialog_window : public window {
protected:
   void subclass_remaining_controls();
public:
   typedef derived_handle <dialog_window, window> handle;
   TOMAHAWK_EXPORT dialog_window();
   TOMAHAWK_EXPORT void run (int resource, ratwin::types::HWND parent=0);
   void run (int resource, window::handle parent)  { run (resource, parent->get_handle()); }
   // ideas: besides a modal version of running, have a threaded version as well.
   TOMAHAWK_EXPORT bool on_command (int id, unsigned notification_code, ratwin::types::HWND);
   TOMAHAWK_EXPORT virtual bool on_button_clicked (int id);
   TOMAHAWK_EXPORT bool translate_key_event (ratwin::message::MSG&);
   TOMAHAWK_EXPORT virtual bool on_OK_button();
   TOMAHAWK_EXPORT virtual bool on_CANCEL_button();
   TOMAHAWK_EXPORT void on_initialize();
   TOMAHAWK_EXPORT controls::control_base& get_control (int id);
   TOMAHAWK_EXPORT void field_to_control();  //update all controls from current values
   TOMAHAWK_EXPORT void control_to_field();  //update all values from control's contents
   TOMAHAWK_EXPORT void field_to_control (controls::control_base*);  //update a control from current value
   TOMAHAWK_EXPORT void control_to_field (controls::control_base*);  //update a values from control's content
   virtual void create_bindings() {}  //override this to supply your bindings.
   };


/***** Derivation Tips *****
 Override (extend) control_to_field() to use a mutex around saving the values, or to
    signal something else that the values have changed.  The singular form just wraps
    the underlying call -- it is here so it may be overridden especially to wrap field updates
    around other code.

****/
 

}
ENDWRAP
#endif


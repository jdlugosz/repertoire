// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\base.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_Controls_BASE_INCLUDED
#define RATWIN_Controls_BASE_INCLUDED

#include "tomahawk\window.h"
#include "classics\string.h"
STARTWRAP

namespace tomahawk {
namespace controls {

bool init_common_controls();
class binder_base;

class control_base : public window {
// A common minimal interface for all controls
public:
   void* binder_data;
   const binder_base* my_binder;
   control_base* next;
   control_base() : binder_data(0), my_binder(0) {}
   TOMAHAWK_EXPORT ~control_base();
   TOMAHAWK_EXPORT virtual void get_value (string&) const;
   TOMAHAWK_EXPORT virtual void set_value (const string&);
   TOMAHAWK_EXPORT void bind (const binder_base&, void* field);
   TOMAHAWK_EXPORT void field_to_control();
   TOMAHAWK_EXPORT void control_to_field() const;
   TOMAHAWK_EXPORT void create_control (window* parent, int childID, int placeholder);
   TOMAHAWK_EXPORT void create_control (window* parent, int childID, const rect& position);
   void create_control (window* parent, int childID)  { create ("", parent, childID); }
   };


class register_control {
protected:
   static register_control* head;
   register_control* next;
   string my_WC_name;
   void (*hook)(ratwin::types::HWND);
public:
   TOMAHAWK_EXPORT static void find_and_hook (ratwin::types::HWND);
   TOMAHAWK_EXPORT virtual bool try_hook (ratwin::types::HWND, const string& WC_name);
   TOMAHAWK_EXPORT register_control (const string& WC_name, void (*hook)(ratwin::types::HWND));
   };

}}
ENDWRAP

#endif


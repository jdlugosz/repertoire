// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\base.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "ratwin\controls\basic.h"
#include "tomahawk\controls\binder.h"
#include "tomahawk\controls\base.h"
#include "tomahawk\rect.h"

#pragma comment (lib, "comctl32.lib")

STARTWRAP
namespace tomahawk {
namespace controls {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool init_common_controls()
 {
 static bool already_done= false;
 if (!already_done) {
    InitCommonControls();
    already_done= true;
    return true;
    }
 else return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

register_control* register_control::head= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool register_control::try_hook (ratwin::types::HWND wnd, const string& WC_name)
 {
 // this matches the Windows Class name.  A derived type could extend the
 // checking done, using the HWND provided.  The purpose of this function 
 // is to discover a match and call hook().
 if (0 != WC_name.compare(my_WC_name, false /*not case-sensitive*/))  return false;   //no match.
 // it might be faster to make sure everything is lower-case ahead of time, rather than
 // using a case-insensitive compare.  I doubt it's significant, and this is simpler.
 hook (wnd);
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void register_control::find_and_hook (ratwin::types::HWND wnd)
 {
 string WC_name (ratwin::window::GetClassName(wnd));
 for (register_control* p= head;  p;  p=p->next) {
    if (p->try_hook (wnd, WC_name))
       return;    //success
    }   
 // falls out of the loop if no match found
 (new window)->attach_to_hwnd (wnd);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

register_control::register_control (const string& WC_name, void (*hook)(ratwin::types::HWND))
 : my_WC_name (WC_name), hook(hook)
 {
 // keep a linked list of all instances.  That's what this class is for.
 next= head;
 head= this;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

control_base::~control_base()
 {
 if(my_binder)  my_binder->disconnect (*this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::get_value (string&) const
 {
 throw "Can't get value as string for this kind of control";
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::set_value (const string&)
 {
 throw "Can't set value as string for this kind of control";
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::field_to_control()
// @ni:dep
 {
 if (my_binder)  my_binder->field_to_control (*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::control_to_field() const
// @ni:dep
 {
 if (my_binder)  my_binder->control_to_field (*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::create_control (window* parent, int childID, int placeholder)
 {
 rect FOO (11,23, 410,183);
 create_control (parent, childID, FOO);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void control_base::create_control (window* parent, int childID, const rect& position)
 {
 create ("", parent, childID);
 move (position);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
}}
ENDWRAP



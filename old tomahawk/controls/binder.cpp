// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\binder.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\binder.h"
#include "tomahawk\controls\base.h"

STARTWRAP
namespace tomahawk {
namespace controls {

const binder<string>& binder<string>::get_instance()
 {
 // Exporting a static member ran into problems under MSVC4.2, so I do this instead.
 static binder<string> instance;
 return instance;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void binder_base::connect (control_base& control, void* field) const
 {
 control.my_binder= this;
 control.binder_data= field;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void binder_base::disconnect (control_base& control) const
 {
 control.my_binder= 0;
 control.binder_data= 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void binder<string>::control_to_field (const control_base& control) const
 {
 string* field= static_cast<string*>(control.binder_data);
 control.get_value (*field);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void binder<string>::field_to_control (control_base& control) const
 {
 string* field= static_cast<string*>(control.binder_data);
 control.set_value (*field);
 }
    

}} //end namespaces
ENDWRAP


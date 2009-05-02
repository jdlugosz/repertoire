// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\controls\binder.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined RATWIN_Controls_BINDER_INCLUDED
#define RATWIN_Controls_BINDER_INCLUDED

#include "classics\string.h"

STARTWRAP
namespace tomahawk {
namespace controls {

class control_base;

class binder_base {
public:
   virtual void control_to_field (const control_base&) const =0;
   virtual void field_to_control (control_base&) const =0;
   TOMAHAWK_EXPORT virtual void connect (control_base&, void* field) const;
   TOMAHAWK_EXPORT virtual void disconnect (control_base&) const;
   };

template <class T>  class binder;

template<>
class binder<classics::/*string*/generic_string<char> > : public binder_base {
	// problem with Microsoft 5.0 parser on above line.
public:
   TOMAHAWK_EXPORT void control_to_field (const control_base&) const;
   TOMAHAWK_EXPORT void field_to_control (control_base&) const;
   TOMAHAWK_EXPORT static const binder<classics::string>& get_instance();
   };
   

template <class T>
inline
void bind (control_base& control, T& field)
 {
 binder<T>::get_instance().connect (control, &field);
 }


} // end of controls
}
ENDWRAP
#endif


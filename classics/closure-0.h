// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure-0.h
// Revision: public build 9, shipped on 18-Oct-2006
// This file generated from the master code in closure-=-MSonPC.h.
// The "ParamType" has been removed, to provide a zero-argument form.
// Redo that if the original changes.

#pragma once
#include "closure-=-MSonPC.h"

namespace classics {
template <typename Class, typename RetType>
class member_callback_thunk_0 : private  internal::thunk_impl_layer<Class, sizeof(RetType (Class::*)()) <= 8> {
public:
   typedef RetType (__stdcall *func)();
   typedef RetType (Class::*method)();
   typedef RetType (Class::*const_method)()const;
   typedef RetType (Class::*volatile_method)()volatile;
   typedef RetType (Class::*const_volatile_method)()const volatile;
   member_callback_thunk_0 (Class* object, method member) 
    { setup (object, &member, sizeof member); }
   member_callback_thunk_0 (const Class* object, const_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk_0 (volatile Class* object, volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk_0 (const volatile Class* object, const_volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   func callptr() const { return reinterpret_cast<func>(this); }
   };


}

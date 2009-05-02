// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure-3.h
// Revision: public build 9, shipped on 18-Oct-2006
// This file generated from the master code in closure-=-MSonPC.h.
// Don't edit this -- edit that instead and re-run ThunkN.perl.

#pragma once
#include "closure-=-MSonPC.h"

namespace classics {
template <typename Class, typename RetType, typename ParamType1, typename ParamType2, typename ParamType3>
class member_callback_thunk_3 : private  internal::thunk_impl_layer<Class, sizeof(RetType (Class::*)(ParamType1, ParamType2, ParamType3)) <= 8> {
public:
   typedef RetType (__stdcall *func)(ParamType1, ParamType2, ParamType3);
   typedef RetType (Class::*method)(ParamType1, ParamType2, ParamType3);
   typedef RetType (Class::*const_method)(ParamType1, ParamType2, ParamType3)const;
   typedef RetType (Class::*volatile_method)(ParamType1, ParamType2, ParamType3)volatile;
   typedef RetType (Class::*const_volatile_method)(ParamType1, ParamType2, ParamType3)const volatile;
   member_callback_thunk_3 (Class* object, method member) 
    { setup (object, &member, sizeof member); }
   member_callback_thunk_3 (const Class* object, const_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk_3 (volatile Class* object, volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk_3 (const volatile Class* object, const_volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   func callptr() const { return reinterpret_cast<func>(this); }
   };


}

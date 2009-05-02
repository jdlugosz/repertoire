// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

/*
   This is included by closure.h if the platform is Microsoft compiler on a PC
*/

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#if (_M_IX86 < 500) || (_MSC_VER != 1310)
  #error This file has only been tested on MSVC 7.1 (.NET 2003 release), and requires Pentium or higher X86 processor.
  // This tests for EQUAL on the compiler version, to make sure the unit test is run for the
  // specific version.  That's just in case code generated is incompatible.  Change the _MSC_VER
  // to allow the new version too, and verify that it works correctly, and send your results to
  // classics@dlugosz.com .
#endif

#include "classics\common.h"


namespace classics {

/////////////////////////////////////////////
////// These are the thunk structures
// Low level, primitive, no type checking.
// Used to implement the "specific useful thunks" below.

#pragma pack (push, 1)  // must use byte alignment!

class closure_stdcall_to_thiscall {
   const unsigned __int8 B9;  // MOV ECX, imm32
   void* object;
   const unsigned __int8 E9;  // JMP relative immediate
   __int32 displacement;  // target= next instruction + displacement
public:
   CLASSICS_EXPORT closure_stdcall_to_thiscall ();
   CLASSICS_EXPORT void set_function (void* function);
   void set_object (void* ob_) { object= ob_; }
   void* callptr() const  { (void*)this; }
   // copy operations need to calculate new value for displacement.
   // they are not implemented yet.
   closure_stdcall_to_thiscall (const closure_stdcall_to_thiscall&);
   closure_stdcall_to_thiscall& operator= (const closure_stdcall_to_thiscall&);
   };

#pragma pack (pop)  // as you were.




namespace internal {

template <typename Class, bool Easy>
class thunk_impl_layer;  // general case not defined.

CLASSICS_EXPORT void easy_setup (closure_stdcall_to_thiscall&, void* object, const void* memberptr, int membersize);

// Easy case: generates no code, as it is all common code for any type.
template <typename Class>
class thunk_impl_layer <Class, true> : public closure_stdcall_to_thiscall {
public:
   void setup (Class* object, void* memberptr, int membersize) {
      easy_setup (*this, object, memberptr, membersize); }
   };


CLASSICS_EXPORT void __fastcall create_probe (void* tryme, void* memberptr);
CLASSICS_EXPORT void __fastcall finish_setup (closure_stdcall_to_thiscall&, void* object, void* memberptr);

// Hard case: virtual inheritance.  Code varies with Class type!
template <typename Class>
class thunk_impl_layer <Class, false> : public closure_stdcall_to_thiscall {
public:
   void setup (Class* object, void* memberptr, int membersize)
    {
    // See what the compiler generates for this Class.
    typedef void* (Class::*tryme_t)();
    tryme_t tryme;
    create_probe (&tryme, memberptr);
    finish_setup (*this, (object->*tryme)(), memberptr);
    }
    
   };

} // end internal



///////////////////////
/* turn a regular function into a member function call, adding a 'this' object.

Does the same thing as writing the following glue function:

   Class* p;
   RetType __stdcall glue (ParamType x)
    {
    return p->method (x);
    }

Except it doesn't re-copy x or the return value.
*/


// The following structured comment brackets the code that is replicated by the script that
// generates templates for different number of arguments.

// ## ThunkN

template <typename Class, typename RetType, typename ParamType>
class member_callback_thunk : private  internal::thunk_impl_layer<Class, sizeof(RetType (Class::*)(ParamType)) <= 8> {
public:
   typedef RetType (__stdcall *func)(ParamType);
   typedef RetType (Class::*method)(ParamType);
   typedef RetType (Class::*const_method)(ParamType)const;
   typedef RetType (Class::*volatile_method)(ParamType)volatile;
   typedef RetType (Class::*const_volatile_method)(ParamType)const volatile;
   member_callback_thunk (Class* object, method member) 
    { setup (object, &member, sizeof member); }
   member_callback_thunk (const Class* object, const_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk (volatile Class* object, volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   member_callback_thunk (const volatile Class* object, const_volatile_method member) 
    { setup (const_cast<Class*>(object), &member, sizeof member); }
   func callptr() const { return reinterpret_cast<func>(this); }
   };

// ## end

}  //end of namespace classics


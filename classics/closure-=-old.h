// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure-=-old.h
// Revision: public build 9, shipped on 18-Oct-2006

/*
  This is the contents of an older version of closure.h.
  It is preserved here for backward compatibility.  The new stuff will not work on older compilers due to
  poor template support, and I'm not supporting the old compilers in new code.
*/


#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#if (_M_IX86 < 500) || (_MSC_VER != 1200 && _MSC_VER != 1300 && _MSC_VER != 1310)
  #error This file has only been tested on MSVC 6.0 and 7.0 (first .NET release), and requires Pentium or higher X86 processor.
  // This tests for EQUAL on the compiler version, to make sure the unit test is run for the
  // specific version.  That's just in case code generated is incompatible.  Change the _MSC_VER
  // to allow the new version too, and verify that it works correctly, and send your results to
  // classics@dlugosz.com .
#endif

#include "classics\common.h"


STARTWRAP
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
   CLASSICS_EXPORT closure_stdcall_to_thiscall (void* object, void* function);
   CLASSICS_EXPORT closure_stdcall_to_thiscall (const closure_stdcall_to_thiscall&);
   closure_stdcall_to_thiscall& operator= (const closure_stdcall_to_thiscall&);
   void* callptr() const  { (void*)this; }
   };

#pragma pack (pop)  // as you were.


////////////////////////////////////////////
/////// These are specific useful thunks.


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

template <typename Class, typename RetType, typename ParamType>
class member_callback_thunk : private closure_stdcall_to_thiscall {
public:
   typedef RetType (__stdcall *func)(ParamType);
   typedef RetType (Class::*method)(ParamType);
private:
   static void* helper2 (method, char (* const dummy)[4]);  // __single_inheritance
   // >> implement __multiple_inheritance case.
   // >> implement __virtual_inheritance case.
   static void* helper (method);
public:
   member_callback_thunk (Class* object, method member) : closure_stdcall_to_thiscall (object, helper(member)) {}
   func callptr() const { return reinterpret_cast<func>(this); }
   };


template <typename Class, typename RetType, typename ParamType>
void* member_callback_thunk<Class,RetType,ParamType>::helper2 (method member, char (*const)[4])
 {
 // When the method pointer is 4 bytes, it is simply a function pointer to either the
 // actual member function entry point, or a VCALL thunk that looks up the vtable.
 // Either way, that is simply the address I need.  This is the __single_inheritance
 // case of VC++ member pointer representation.
 union {
    method p;
    void* function;
    };
 p= member;
 return function;
 }

template <typename Class, typename RetType, typename ParamType>
void* member_callback_thunk<Class,RetType,ParamType>::helper (method member)
 {
 typedef char (*ss)[sizeof(method)];
 return helper2 (member, (ss)0);  // If you get an error here about parameter 2,
   // It means that the class is too complex for this thunk to handle (in this version).
   // Supports single-inheritance only (simplest representation of member pointers)
 }


/////////////////////
// Add a parameter to a __stdcall function
/*
Does the same thing as writing the following glue function:

   Class* p;
   RetType __stdcall glue (ParamType x)
    {
    return foo (p, x);  // foo is also __stdcall
    }

Except it doesn't re-copy x or the return value.

For cases where member_callback_thunk doesn't work, use this (with a little more work) instead.
E.g.  instead of member_callback_thunk<C,RetType,ParamType> (instance, &C::bar)
include a static member:

   RetType C::foo (C* self, ParamType x)
    {
    return self->bar (x);
    }

 And then use a global_callback_thunk<C,RetType,ParamType> (instance, &C::foo).
*/

//>> class global_callback_thunk

}  //end of namespace
ENDWRAP


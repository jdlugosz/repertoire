// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"


STARTWRAP
namespace classics {

#pragma pack (push, 1)  // must use byte alignment!

class closure_stdcall_to_thiscall {
   const unsigned __int8 B9;  // MOV ECX, imm32
   void* object;
   const unsigned __int8 E9;  // JMP relative immediate
   __int32 displacement;  // target= next instruction + displacement
public:
   CLASSICS_EXPORT closure_stdcall_to_thiscall (void* object, void* function);
   closure_stdcall_to_thiscall (const closure_stdcall_to_thiscall&);
   closure_stdcall_to_thiscall& operator= (const closure_stdcall_to_thiscall&);
   void* callptr() const  { (void*)this; }
   };

#pragma pack (pop)  // as you were.

}  //end of namespace
ENDWRAP


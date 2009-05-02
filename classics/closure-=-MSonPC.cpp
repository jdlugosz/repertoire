// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure-=-MSonPC.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\closure.h"

STARTWRAP
namespace classics {

closure_stdcall_to_thiscall::closure_stdcall_to_thiscall ()
 :B9 (0xb9), E9 (0xe9)
 {
 }

void closure_stdcall_to_thiscall::set_function (void* function)
 {
 // function= next instruction + displacement, so...
 displacement= reinterpret_cast<unsigned>(function) - (reinterpret_cast<unsigned>(&displacement)+4);
 }

namespace internal {

CLASSICS_EXPORT void easy_setup (closure_stdcall_to_thiscall& thunk, void* object, const void* memberptr, int membersize)
 {
 struct parser {
    void* function;
    int adjustment;
    };
 const parser* p= static_cast<const parser*>(memberptr);
 if (membersize == 8 && p->adjustment != 0)
    object= static_cast<char*>(object) + p->adjustment;
 thunk.set_object (object);
 thunk.set_function (p->function);
 }

__declspec(naked) void __stdcall probefunction ()
 {
 __asm {
    mov EAX, ECX;
    ret
    }
 }

CLASSICS_EXPORT void __fastcall create_probe (void* tryme, void* memberptr)
 {
 struct parser {
    void* function;
    int adjustment;
    int somethingelse;
    };
 parser* dest= static_cast<parser*>(tryme);
 const parser* src= static_cast<const parser*>(memberptr);
 dest->adjustment= src->adjustment;
 dest->somethingelse= src->somethingelse;
 dest->function= &probefunction;
 }

CLASSICS_EXPORT void __fastcall finish_setup (closure_stdcall_to_thiscall& self, void* object, void* memberptr)
 {
 struct parser {
    void* function;
    int adjustment;
    int somethingelse;
    };
 const parser* p= static_cast<const parser*>(memberptr);
 self.set_function (p->function);
 self.set_object (object);
 }

}  // end internal
}  // end classics


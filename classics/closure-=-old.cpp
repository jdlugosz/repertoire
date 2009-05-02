// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure-=-old.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\closure.h"

STARTWRAP
namespace classics {

closure_stdcall_to_thiscall::closure_stdcall_to_thiscall (void* object, void* function)
 :B9 (0xb9), E9 (0xe9), object (object)
 {
 // function= next instruction + displacement, so...
 displacement= reinterpret_cast<unsigned>(function) - (reinterpret_cast<unsigned>(&displacement)+4);
 }

}


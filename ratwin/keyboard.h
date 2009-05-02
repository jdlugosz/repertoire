// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\keyboard.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_KEYBOARD_INCLUDED
#define RATWIN_KEYBOARD_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) short __stdcall GetKeyState (Dlugosz::ratwin::arg::arg32);

}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace keyboard {

enum vkey {
   VK_SCROLL=  0x91,
   // add others as I need them
   };
   
inline
short GetKeyState (vkey k)
 { return ::GetKeyState (reinterpret_cast<arg::arg32>(k)); }


} //end of keyboard

}
ENDWRAP
#endif


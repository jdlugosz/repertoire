// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\message=struct.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace message {

struct MSG_base {
   types::HWND hwnd;
   unsigned message;
   inline types::HWND receiving_window() const { return hwnd; }
   };

struct sMSG : public MSG_base { // simple message
   unsigned wParam;
   ulong lParam;
   };


// WINDOWS.H calls this MSG, so I kept the same name.  But, the subset is
// also available as a type sMSG.
struct MSG : public sMSG {
   ulong time;
   types::POINT pt;
   };

template<typename T>
const T& MSG_cast (const ratwin::message::MSG_base& x)
 { return static_cast<const T&>(x); }
 

} //end of message
}
ENDWRAP




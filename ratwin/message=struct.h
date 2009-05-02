// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\message=struct.h
// Revision: updated

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace message {

struct MSG {
   types::HWND hwnd;
   unsigned message;
   unsigned wParam;
   ulong lParam;
   ulong time;
   types::POINT pt;
   };


} //end of message
}
ENDWRAP




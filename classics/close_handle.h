// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\close_handle.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error classics\close_handle.h (indirectly) contains globals.
#endif
#include "classics\common.h"
#include "ratwin\handle.h"  // contains globals

STARTWRAP
namespace classics {

class close_Kernel_HANDLE {
   ratwin::types::Kernel_HANDLE& h;
   close_Kernel_HANDLE (close_Kernel_HANDLE&);  // never defined
   void operator= (close_Kernel_HANDLE&);  // never defined
public:
   explicit close_Kernel_HANDLE (const ratwin::types::Kernel_HANDLE& h) 
    // The parameter is declared as 'const' so derived types will work here, too.
    : h(const_cast<ratwin::types::Kernel_HANDLE&>(h)) {}
   // Here's what I came for:
   ~close_Kernel_HANDLE() { ratwin::CloseHandle(h); }
   };

}
ENDWRAP



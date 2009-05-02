// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\bitmap.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\bitmap.h contains globals.  Include bitmap=struct.h instead.
#endif

#include "ratwin\bitmap=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall GetObjectA (Dlugosz::ratwin::arg::arg32, int, void*);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace bitmap {

inline int GetObject (types::HBITMAP bitmap, BITMAP& data)
 { return ::GetObjectA (reinterpret_cast<arg::arg32>(bitmap), sizeof(BITMAP), &data); }
// other forms of GetObject elsewhere.


//////////////
// See Also:  GDI.h for BitBlt


} //end of bitmap

}
ENDWRAP


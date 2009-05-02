// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ToolBar.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error contains globals (use "ratwin\controls\ToolBar=struct.h" instead)
#endif

/* Notes

Don't use CreateToolbarEx.  The bitmaps must be 16-color, and the algorithm for making them transparent
is totally bizzare and undocumented.  Use an image list!

The default height of a toolbar has nothing to do with the button size you gave it.  It's too short, prob. designed
for 16-pixel-tall images. 

Interestingly, any MoveWindow sent to resize will compute the correct size and ignore the parameters you
gave it.  (this might vary with the style flags; not probed exhaustivly)

*/

#include "ratwin\controls\ToolBar=struct.h"

extern "C" {

__declspec(dllimport) void* __stdcall CreateToolbarEx (Dlugosz::ratwin::arg::arg32 hwnd, unsigned ws, unsigned wID, int nBitmaps,
 void* hBMInst, unsigned wBMID, const void* lpButtons, int iNumButtons, int dxButton, int dyButton, int dxBitmap, int dyBitmap, unsigned uStructSize);

}


STARTWRAP
namespace ratwin {
namespace controls {

inline
types::HWND CreateToolbarEx (
      types::HWND parent, 
      unsigned styles, 
      unsigned child_ID, 
      int nBitmaps, 
      types::HINSTANCE hBMInst, unsigned wBMID,   // resource number (reportedly not string!), or 0 and bitmap handle.
      const TBBUTTON* Buttons, int NumButtons, 
      types::POINT button_size,
      types::POINT bitmap_size  )
 {
 return reinterpret_cast<types::HWND>( ::CreateToolbarEx (reinterpret_cast<arg::arg32>(parent), styles, child_ID, nBitmaps, hBMInst, wBMID, Buttons, NumButtons,
    button_size.x, button_size.y, bitmap_size.x, bitmap_size.y, sizeof (TBBUTTON) ) );
 }
 
} // end of controls
}
ENDWRAP




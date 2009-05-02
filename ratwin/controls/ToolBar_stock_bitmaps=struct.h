// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ToolBar_stock_bitmaps=struct.h
// Revision: new

#pragma once
#include "ratwin\controls\basic.h"

STARTWRAP
namespace ratwin {
namespace controls {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::controls)
HINST_COMMCTRL IDB_STD_SMALL_COLOR IDB_STD_LARGE_COLOR IDB_VIEW_SMALL_COLOR IDB_VIEW_LARGE_COLOR
IDB_HIST_SMALL_COLOR IDB_HIST_LARGE_COLOR





*/


 const types::HINSTANCE HINST_COMMCTRL= reinterpret_cast<types::HINSTANCE>(-1);

enum IDB_identifiers {
// used with TB_ADDBITMAP and TB_LOADIMAGES
   IDB_STD_SMALL_COLOR=     0,
   IDB_STD_LARGE_COLOR=     1,
   IDB_VIEW_SMALL_COLOR=    4,
   IDB_VIEW_LARGE_COLOR=    5,
   IDB_HIST_SMALL_COLOR=    8,
   IDB_HIST_LARGE_COLOR=    9
   };


   
} // end of controls
}
ENDWRAP

// ## Macro_Cloak_After


// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ImageList=struct.h
// Revision: new

#pragma once
#include "ratwin\controls\basic.h"

STARTWRAP
namespace ratwin {

namespace types {
namespace internal {
   struct HIMAGELIST_struct : public HANDLE_struct {/*empty*/};
}}

namespace controls {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::controls)
   ILC_COLOR ILC_COLORDDB ILC_COLOR4 ILC_COLOR8 ILC_COLOR16 ILC_COLOR24 ILC_COLOR32    
   IMAGE_BITMAP IMAGE_ICON IMAGE_CURSOR IMAGE_ENHMETAFILE




*/

typedef types::internal::HIMAGELIST_struct* HIMAGELIST;

// #define ILC_MASK                0x0001
// ICL_MASK not used.  Made into separate bool parameter in ImageList_Create
enum ICL_color {  // parameter for ImageList_Create
   ILC_COLOR=      0x0000,  // a moving default.  Don't use that.
   ILC_COLORDDB=   0x00FE,  // only (possibly) used on very old video drivers.
   ILC_COLOR4=     0x0004,
   ILC_COLOR8=     0x0008,
   ILC_COLOR16=    0x0010,
   ILC_COLOR24=    0x0018,
   ILC_COLOR32=    0x0020,
   };

enum LoadImage_type {  // parameter for ImageList_LoadImage
   IMAGE_BITMAP  =0, IMAGE_ICON, IMAGE_CURSOR  , IMAGE_ENHMETAFILE
   };


} // end of controls
}
ENDWRAP

// ## Macro_Cloak_After


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ImageList=struct.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\controls\basic=struct.h"

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
// ## BEGIN MacroCloak Generated Code
#if defined (ILC_COLOR)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef ILC_COLOR
#undef ILC_COLORDDB
#undef ILC_COLOR4
#undef ILC_COLOR8
#undef ILC_COLOR16
#undef ILC_COLOR24
#undef ILC_COLOR32
#undef IMAGE_BITMAP
#undef IMAGE_ICON
#undef IMAGE_CURSOR
#undef IMAGE_ENHMETAFILE
#endif
// ## END Generated Code

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
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::controls::ILC_COLOR;
using ratwin::controls::ILC_COLORDDB;
using ratwin::controls::ILC_COLOR4;
using ratwin::controls::ILC_COLOR8;
using ratwin::controls::ILC_COLOR16;
using ratwin::controls::ILC_COLOR24;
using ratwin::controls::ILC_COLOR32;
using ratwin::controls::IMAGE_BITMAP;
using ratwin::controls::IMAGE_ICON;
using ratwin::controls::IMAGE_CURSOR;
using ratwin::controls::IMAGE_ENHMETAFILE;
#endif
// ## END Generated Code


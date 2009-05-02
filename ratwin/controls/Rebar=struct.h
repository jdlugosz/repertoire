// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\Rebar=struct.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#include "ratwin\controls\basic=struct.h"
#include "ratwin\color=struct.h"

STARTWRAP
namespace ratwin {
namespace controls {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::controls)
   RBS_TOOLTIPS RBS_VARHEIGHT RBS_BANDBORDERS RBS_FIXEDORDER RBS_REGISTERDROP
   RBS_AUTOSIZE RBS_VERTICALGRIPPER RBS_DBLCLKTOGGLE
   RBBIM_STYLE RBBIM_COLORS RBBIM_TEXT RBBIM_IMAGE RBBIM_CHILD RBBIM_CHILDSIZE
   RBBIM_SIZE RBBIM_BACKGROUND RBBIM_ID RBBIM_IDEALSIZE RBBIM_LPARAM RBBIM_HEADERSIZE
   RBBS_BREAK RBBS_FIXEDSIZE RBBS_CHILDEDGE RBBS_HIDDEN RBBS_NOVERT RBBS_FIXEDBMP
   RBBS_VARIABLEHEIGHT RBBS_GRIPPERALWAYS RBBS_NOGRIPPER      
   RB_INSERTBANDA RB_DELETEBAND RB_GETBARINFO RB_SETBARINFO RB_GETBANDINFO RB_SETBANDINFOA
   RB_SETPARENT RB_HITTEST RB_GETRECT RB_INSERTBANDW RB_SETBANDINFOW RB_GETBANDCOUNT
   RB_GETROWCOUNT RB_GETROWHEIGHT RB_IDTOINDEX RB_GETTOOLTIPS RB_SETTOOLTIPS RB_SETBKCOLOR
   RB_GETBKCOLOR RB_SETTEXTCOLOR RB_GETTEXTCOLOR RB_SIZETORECT
   RBBS_USECHEVRON RBBS_HIDETITLE
*/
// ## BEGIN MacroCloak Generated Code
#if defined (RBS_TOOLTIPS)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef RBS_TOOLTIPS
#undef RBS_VARHEIGHT
#undef RBS_BANDBORDERS
#undef RBS_FIXEDORDER
#undef RBS_REGISTERDROP
#undef RBS_AUTOSIZE
#undef RBS_VERTICALGRIPPER
#undef RBS_DBLCLKTOGGLE
#undef RBBIM_STYLE
#undef RBBIM_COLORS
#undef RBBIM_TEXT
#undef RBBIM_IMAGE
#undef RBBIM_CHILD
#undef RBBIM_CHILDSIZE
#undef RBBIM_SIZE
#undef RBBIM_BACKGROUND
#undef RBBIM_ID
#undef RBBIM_IDEALSIZE
#undef RBBIM_LPARAM
#undef RBBIM_HEADERSIZE
#undef RBBS_BREAK
#undef RBBS_FIXEDSIZE
#undef RBBS_CHILDEDGE
#undef RBBS_HIDDEN
#undef RBBS_NOVERT
#undef RBBS_FIXEDBMP
#undef RBBS_VARIABLEHEIGHT
#undef RBBS_GRIPPERALWAYS
#undef RBBS_NOGRIPPER
#endif
// ## END Generated Code

#if 0
   #define REBARCLASSNAMEW         L"ReBarWindow32"
   #define REBARCLASSNAMEA         "ReBarWindow32"
   // these are not being defined because it takes a ustring to make it autoswitch A/W, and that's a higher level
   // than allowed in this component.  It's just as easy to use the well-known string name.  A "classics" class
   // will take care of this for you.
#endif

enum RBS_style {  // window style flags
   RBS_TOOLTIPS=          0x0100,
   RBS_VARHEIGHT=         0x0200,
   RBS_BANDBORDERS=       0x0400,
   RBS_FIXEDORDER=        0x0800,
   RBS_REGISTERDROP=      0x1000,
   RBS_AUTOSIZE=          0x2000,
   RBS_VERTICALGRIPPER=   0x4000,
   RBS_DBLCLKTOGGLE=      0x8000
   };


 enum RBBIM_bits {
 // used for fMask member of REBARBANDINFO
    RBBIM_STYLE=         0x00000001,
    RBBIM_COLORS=        0x00000002,
    RBBIM_TEXT=          0x00000004,
    RBBIM_IMAGE=         0x00000008,
    RBBIM_CHILD=         0x00000010,
    RBBIM_CHILDSIZE=     0x00000020,
    RBBIM_SIZE=          0x00000040,
    RBBIM_BACKGROUND=    0x00000080,
    RBBIM_ID=            0x00000100,
    RBBIM_IDEALSIZE=     0x00000200,
    RBBIM_LPARAM=        0x00000400,
    RBBIM_HEADERSIZE=    0x00000800  // control the size of the header
    };

enum RBBS_style {
// used for fStyle member of REBARBANDINFO
   RBBS_BREAK=             0x00000001,  // break to new line
   RBBS_FIXEDSIZE=         0x00000002,  // band can't be sized
   RBBS_CHILDEDGE=         0x00000004,  // edge around top & bottom of child window
   RBBS_HIDDEN=            0x00000008,  // don't show
   RBBS_NOVERT=            0x00000010,  // don't show when vertical
   RBBS_FIXEDBMP=          0x00000020,  // bitmap doesn't move during band resize
   RBBS_VARIABLEHEIGHT=    0x00000040,  // allow autosizing of this child vertically
   RBBS_GRIPPERALWAYS=     0x00000080,  // always show the gripper
   RBBS_NOGRIPPER=         0x00000100,   // never show the gripper
   RBBS_USECHEVRON=        0x00000200,  // display drop-down button for this band if it's sized smaller than ideal width
   RBBS_HIDETITLE=         0x00000400  // keep band title hidden
   };


template <typename Char_T>
struct REBARBANDINFO_v3 {
   unsigned cbSize;
   unsigned fMask;   // use RBBM_bits flags here.
   unsigned fStyle;  // use RBBS_style flags here.
   color::COLORREF clrFore;
   color::COLORREF clrBack;
   Char_T* lpText;
   unsigned cch;
   int iImage;
   types::HWND hwndChild;
   unsigned cxMinChild;
   unsigned cyMinChild;
   unsigned cx;
   types::HBITMAP hbmBack;
   unsigned wID;
   };

template <typename Char_T>
struct REBARBANDINFO : public REBARBANDINFO_v3<Char_T> {
    unsigned cyChild;
    unsigned cyMaxChild;
    unsigned cyIntegral;
    unsigned cxIdeal;
    unsigned lParam;
    unsigned cxHeader;
    };

 enum Rebar_Messages {
 // used with msg parameter of SendMessage to Rebar windows
    RB_INSERTBANDA= 0x0401,  // WM_USER+1
    RB_DELETEBAND,
    RB_GETBARINFO,
    RB_SETBARINFO,
    RB_GETBANDINFO,
    RB_SETBANDINFOA,
    RB_SETPARENT,
    RB_HITTEST,
    RB_GETRECT,
    RB_INSERTBANDW,
    RB_SETBANDINFOW,
    RB_GETBANDCOUNT,
    RB_GETROWCOUNT  ,
    RB_GETROWHEIGHT,
    // no WM_USER+15
    RB_IDTOINDEX= 0x0410, // wParam == id
    RB_GETTOOLTIPS,
    RB_SETTOOLTIPS,
    RB_SETBKCOLOR,  // sets the default BK color
    RB_GETBKCOLOR, // defaults to CLR_NONE
    RB_SETTEXTCOLOR,
    RB_GETTEXTCOLOR, // defaults to 0x00000000
    RB_SIZETORECT  // resize the rebar/break bands and such to this rect (lparam)
    };
/* notes:
  want RB_SETCOLORSCHEME ? use  CCM_SETCOLORSCHEME  
  want RB_GETCOLORSCHEME ? use  CCM_GETCOLORSCHEME  
  want RB_INSERTBAND ? use RB_INSERTBANDW or -A, or better yet use the InsertBand function instead of an explicit call to SendMessage.
  want RB_SETBANDINFO ? use RB_SETBANDINFOW or -A, or better yet use the SetBandInfo function.
*/

   
} // end of controls
}
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::controls::RBS_TOOLTIPS;
using ratwin::controls::RBS_VARHEIGHT;
using ratwin::controls::RBS_BANDBORDERS;
using ratwin::controls::RBS_FIXEDORDER;
using ratwin::controls::RBS_REGISTERDROP;
using ratwin::controls::RBS_AUTOSIZE;
using ratwin::controls::RBS_VERTICALGRIPPER;
using ratwin::controls::RBS_DBLCLKTOGGLE;
using ratwin::controls::RBBIM_STYLE;
using ratwin::controls::RBBIM_COLORS;
using ratwin::controls::RBBIM_TEXT;
using ratwin::controls::RBBIM_IMAGE;
using ratwin::controls::RBBIM_CHILD;
using ratwin::controls::RBBIM_CHILDSIZE;
using ratwin::controls::RBBIM_SIZE;
using ratwin::controls::RBBIM_BACKGROUND;
using ratwin::controls::RBBIM_ID;
using ratwin::controls::RBBIM_IDEALSIZE;
using ratwin::controls::RBBIM_LPARAM;
using ratwin::controls::RBBIM_HEADERSIZE;
using ratwin::controls::RBBS_BREAK;
using ratwin::controls::RBBS_FIXEDSIZE;
using ratwin::controls::RBBS_CHILDEDGE;
using ratwin::controls::RBBS_HIDDEN;
using ratwin::controls::RBBS_NOVERT;
using ratwin::controls::RBBS_FIXEDBMP;
using ratwin::controls::RBBS_VARIABLEHEIGHT;
using ratwin::controls::RBBS_GRIPPERALWAYS;
using ratwin::controls::RBBS_NOGRIPPER;
#endif
// ## END Generated Code


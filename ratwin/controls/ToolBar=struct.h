// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\ToolBar=struct.h
// Revision: new

// See also ratwin\controls\ToolBar_stock_bitmaps=struct.h

#pragma once
#include "ratwin\controls\basic.h"
#include "ratwin\WM_constants.h"  // need NMHDR.  Should move that.

STARTWRAP
namespace ratwin {
namespace controls {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::controls)
   TBSTYLE_TOOLTIPS TBSTYLE_WRAPABLE TBSTYLE_ALTDRAG TBSTYLE_FLAT
   TBSTYLE_LIST TBSTYLE_CUSTOMERASE TBSTYLE_REGISTERDROP TBSTYLE_TRANSPARENT
   TBSTATE_CHECKED  TBSTATE_PRESSED TBSTATE_ENABLED TBSTATE_HIDDEN TBSTATE_INDETERMINATE
   TBSTATE_WRAP TBSTATE_ELLIPSES TBSTATE_MARKED
   TB_ENABLEBUTTON TB_CHECKBUTTON TB_PRESSBUTTON TB_HIDEBUTTON TB_INDETERMINATE
   TB_MARKBUTTON TB_ISBUTTONENABLED TB_ISBUTTONCHECKED TB_ISBUTTONPRESSED
   TB_ISBUTTONHIDDEN TB_ISBUTTONINDETERMINATE TB_ISBUTTONHIGHLIGHTED TB_SETSTATE
   TB_GETSTATE TB_ADDBITMAP TB_ADDBUTTONS TB_INSERTBUTTON TB_DELETEBUTTON TB_GETBUTTON
   TB_BUTTONCOUNT TB_COMMANDTOINDEX TB_SAVERESTOREA TB_SAVERESTOREW TB_CUSTOMIZE
   TB_ADDSTRINGA TB_ADDSTRINGW TB_GETITEMRECT TB_BUTTONSTRUCTSIZE TB_SETBUTTONSIZE
   TB_SETBITMAPSIZE TB_AUTOSIZE TB_GETTOOLTIPS TB_SETTOOLTIPS TB_SETPARENT TB_SETROWS              
   TB_GETROWS TB_SETCMDID TB_CHANGEBITMAP TB_GETBITMAP TB_GETBUTTONTEXTA TB_GETBUTTONTEXTW
   TB_REPLACEBITMAP TB_SETINDENT TB_SETIMAGELIST TB_GETIMAGELIST TB_LOADIMAGES TB_GETRECT
   TB_SETHOTIMAGELIST TB_GETHOTIMAGELIST TB_SETDISABLEDIMAGELIST TB_GETDISABLEDIMAGELIST
   TB_SETSTYLE TB_GETSTYLE TB_GETBUTTONSIZE TB_SETBUTTONWIDTH TB_SETMAXTEXTROWS TB_GETTEXTROWS
   TB_GETOBJECT TB_GETHOTITEM TB_SETHOTITEM TB_SETANCHORHIGHLIGHT TB_GETANCHORHIGHLIGHT
   TB_MAPACCELERATORA TB_GETINSERTMARK TB_SETINSERTMARK TB_INSERTMARKHITTEST TB_MOVEBUTTON
   TB_GETMAXSIZE TB_SETEXTENDEDSTYLE TB_GETEXTENDEDSTYLE TB_GETPADDING TB_SETPADDING
   TB_SETINSERTMARKCOLOR TB_GETINSERTMARKCOLOR TB_MAPACCELERATORW TB_GETBITMAPFLAGS
   TB_GETBUTTONINFOW TB_SETBUTTONINFOW TB_GETBUTTONINFOA TB_SETBUTTONINFOA     
   TB_INSERTBUTTONW TB_ADDBUTTONSW TB_HITTEST TB_SETDRAWTEXTFLAGS
   TBIF_IMAGE TBIF_TEXT TBIF_STATE TBIF_STYLE TBIF_LPARAM TBIF_COMMAND TBIF_SIZE
   BTNS_BUTTON BTNS_SEP BTNS_CHECK BTNS_GROUP BTNS_CHECKGROUP BTNS_DROPDOWN
   BTNS_AUTOSIZE BTNS_NOPREFIX BTNS_SHOWTEXT BTNS_WHOLEDROPDOWN
   TBSTYLE_EX_DRAWDDARROWS TBSTYLE_EX_MIXEDBUTTONS TBSTYLE_EX_HIDECLIPPEDBUTTONS





   
   */
// ## BEGIN MacroCloak Generated Code
#if defined (TBSTYLE_BUTTON)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef TBSTYLE_BUTTON
#undef TBSTYLE_SEP
#undef TBSTYLE_CHECK
#undef TBSTYLE_GROUP
#undef TBSTYLE_CHECKGROUP
#undef TBSTYLE_DROPDOWN
#undef TBSTYLE_AUTOSIZE
#undef TBSTYLE_NOPREFIX
#undef TBSTYLE_TOOLTIPS
#undef TBSTYLE_WRAPABLE
#undef TBSTYLE_ALTDRAG
#undef TBSTYLE_FLAT
#undef TBSTYLE_LIST
#undef TBSTYLE_CUSTOMERASE
#undef TBSTYLE_REGISTERDROP
#undef TBSTYLE_TRANSPARENT
#undef TBSTATE_CHECKED
#undef TBSTATE_PRESSED
#undef TBSTATE_ENABLED
#undef TBSTATE_HIDDEN
#undef TBSTATE_INDETERMINATE
#undef TBSTATE_WRAP
#undef TBSTATE_ELLIPSES
#undef TBSTATE_MARKED
#undef TB_ENABLEBUTTON
#undef TB_CHECKBUTTON
#undef TB_PRESSBUTTON
#undef TB_HIDEBUTTON
#undef TB_INDETERMINATE
#undef TB_MARKBUTTON
#undef TB_ISBUTTONENABLED
#undef TB_ISBUTTONCHECKED
#undef TB_ISBUTTONPRESSED
#undef TB_ISBUTTONHIDDEN
#undef TB_ISBUTTONINDETERMINATE
#undef TB_ISBUTTONHIGHLIGHTED
#undef TB_SETSTATE
#undef TB_GETSTATE
#undef TB_ADDBITMAP
#undef TB_ADDBUTTONS
#undef TB_INSERTBUTTON
#undef TB_DELETEBUTTON
#undef TB_GETBUTTON
#undef TB_BUTTONCOUNT
#undef TB_COMMANDTOINDEX
#undef TB_SAVERESTOREA
#undef TB_SAVERESTOREW
#undef TB_CUSTOMIZE
#undef TB_ADDSTRINGA
#undef TB_ADDSTRINGW
#undef TB_GETITEMRECT
#undef TB_BUTTONSTRUCTSIZE
#undef TB_SETBUTTONSIZE
#undef TB_SETBITMAPSIZE
#undef TB_AUTOSIZE
#undef TB_GETTOOLTIPS
#undef TB_SETTOOLTIPS
#undef TB_SETPARENT
#undef TB_SETROWS
#undef TB_GETROWS
#undef TB_SETCMDID
#undef TB_CHANGEBITMAP
#undef TB_GETBITMAP
#undef TB_GETBUTTONTEXTA
#undef TB_GETBUTTONTEXTW
#undef TB_REPLACEBITMAP
#undef TB_SETINDENT
#undef TB_SETIMAGELIST
#undef TB_GETIMAGELIST
#undef TB_LOADIMAGES
#undef TB_GETRECT
#undef TB_SETHOTIMAGELIST
#undef TB_GETHOTIMAGELIST
#undef TB_SETDISABLEDIMAGELIST
#undef TB_GETDISABLEDIMAGELIST
#undef TB_SETSTYLE
#undef TB_GETSTYLE
#undef TB_GETBUTTONSIZE
#undef TB_SETBUTTONWIDTH
#undef TB_SETMAXTEXTROWS
#undef TB_GETTEXTROWS
#undef TB_GETOBJECT
#undef TB_GETHOTITEM
#undef TB_SETHOTITEM
#undef TB_SETANCHORHIGHLIGHT
#undef TB_GETANCHORHIGHLIGHT
#undef TB_MAPACCELERATORA
#undef TB_GETINSERTMARK
#undef TB_SETINSERTMARK
#undef TB_INSERTMARKHITTEST
#undef TB_MOVEBUTTON
#undef TB_GETMAXSIZE
#undef TB_SETEXTENDEDSTYLE
#undef TB_GETEXTENDEDSTYLE
#undef TB_GETPADDING
#undef TB_SETPADDING
#undef TB_SETINSERTMARKCOLOR
#undef TB_GETINSERTMARKCOLOR
#undef TB_MAPACCELERATORW
#undef TB_GETBITMAPFLAGS
#undef TB_GETBUTTONINFOW
#undef TB_SETBUTTONINFOW
#undef TB_GETBUTTONINFOA
#undef TB_SETBUTTONINFOA
#undef TB_INSERTBUTTONW
#undef TB_ADDBUTTONSW
#undef TB_HITTEST
#undef TB_SETDRAWTEXTFLAGS
#endif
// ## END Generated Code

#if 0
#define TOOLBARCLASSNAMEW       L"ToolbarWindow32"
#define TOOLBARCLASSNAMEA       "ToolbarWindow32"
   // these are not being defined because it takes a ustring to make it autoswitch A/W, and that's a higher level
   // than allowed in this component.  It's just as easy to use the well-known string name.  A "classics" class
   // will take care of this for you.
#endif

enum BTNS_fsStyle {
// this is used in the TBBUTTON structure.
   BTNS_BUTTON=             0x0000,
   BTNS_SEP=                0x0001,
   BTNS_CHECK=              0x0002,
   BTNS_GROUP=              0x0004,
   BTNS_CHECKGROUP=         (BTNS_GROUP | BTNS_CHECK),
   BTNS_DROPDOWN=           0x0008,
   BTNS_AUTOSIZE=           0x0010, // automatically calculate the cx of the button
   BTNS_NOPREFIX=           0x0020, // if this button should not have accel prefix
   BTNS_SHOWTEXT=           0x0040, // used with TBSTYLE_EX_MIXEDBUTTONS only.
   BTNS_WHOLEDROPDOWN= 0x0080      // dropdown arrow without the split.
   };

enum TB_style {
// these are combined with the other window styles when creating a toolbar window.
   TBSTYLE_TOOLTIPS=        0x0100,
   TBSTYLE_WRAPABLE=        0x0200,
   TBSTYLE_ALTDRAG=         0x0400,
   TBSTYLE_FLAT=            0x0800,
   TBSTYLE_LIST=            0x1000,
   TBSTYLE_CUSTOMERASE=     0x2000,
   TBSTYLE_REGISTERDROP=    0x4000,
   TBSTYLE_TRANSPARENT=     0x8000
   };

enum TB_EX_style {
// these are used with TB_GET(SET)EXTENDEDSTYLE messages!  NOT extended window style bits.
   TBSTYLE_EX_DRAWDDARROWS=         0x00000001,  // draw dropdown arrows.  Otherwise specifying them doesn't do any good.
   TBSTYLE_EX_MIXEDBUTTONS=         0x00000008,  // show text in LIST style, or only show text of buttons marked SHOWTEXT.
   TBSTYLE_EX_HIDECLIPPEDBUTTONS=   0x00000010  // don't show partially obscured buttons
   };

// #define TBSTYLE_EX_DRAWDDARROWS 0x00000001

enum TB_state {  // use third element in TBBUTTON struct.
   TBSTATE_CHECKED=          0x01,
   TBSTATE_PRESSED=          0x02,
   TBSTATE_ENABLED=          0x04,
   TBSTATE_HIDDEN=           0x08,
   TBSTATE_INDETERMINATE=    0x10,
   TBSTATE_WRAP=             0x20,
   TBSTATE_ELLIPSES=         0x40,
   TBSTATE_MARKED=           0x80
   };


struct TBBUTTON {
   int iBitmap;
   int idCommand;
   unsigned char fsState;
   unsigned char fsStyle;
//   unsigned char bReserved[2];  // for alignment, we suppose.
//   the two-byte array shown in WINDOWS.H does not work correctly with the code
//   in MS's examples!!!
   unsigned short reserved;  // for alignment, we suppose.
   unsigned long dwData;
   int iString;
   };


enum TBIF_flags {  // used in TBBUTTONINFO structure.
   TBIF_IMAGE=      0x00000001,
   TBIF_TEXT=       0x00000002,
   TBIF_STATE=      0x00000004,
   TBIF_STYLE=      0x00000008,
   TBIF_LPARAM=     0x00000010,
   TBIF_COMMAND=    0x00000020,
   TBIF_SIZE=       0x00000040
   };


template <typename CharT>
struct TBBUTTONINFO {
   unsigned cbSize;
   unsigned dwMask;  // use TBIF_flags above.
   int idCommand;
   int iImage;
   unsigned char fsState;
   unsigned char fsStyle;
   unsigned short cx;
   unsigned lParam;
   CharT* pszText;
   int cchText;
   };

template <typename CharT>
struct NMTOOLBAR : public WM_constants::NMHDR {
   int iItem;
   TBBUTTON tbButton;     // Only populated with TBN_QUERYINSERT / TBN_QUERYDELETE notifications.
   int cchText;
   CharT* pszText;
   types::RECT rcButton;
   };


 enum Toolbar_Messages {
 // used with msg parameter of SendMessage to Toolbar windows
    TB_ENABLEBUTTON=    0x0401,  // (WM_USER+1
    TB_CHECKBUTTON  ,
    TB_PRESSBUTTON,
    TB_HIDEBUTTON,
    TB_INDETERMINATE,
    TB_MARKBUTTON,
    // no 7 or 8
    TB_ISBUTTONENABLED= 0x0409,
    TB_ISBUTTONCHECKED,
    TB_ISBUTTONPRESSED,
    TB_ISBUTTONHIDDEN,
    TB_ISBUTTONINDETERMINATE,
    TB_ISBUTTONHIGHLIGHTED,
    // no 15 or 16
    TB_SETSTATE=  0x0411,
    TB_GETSTATE,
    TB_ADDBITMAP,
    TB_ADDBUTTONS,
    TB_INSERTBUTTON,
    TB_DELETEBUTTON,
    TB_GETBUTTON,
    TB_BUTTONCOUNT,
    TB_COMMANDTOINDEX,  // 25
    TB_SAVERESTOREA,
    TB_CUSTOMIZE,
    TB_ADDSTRINGA,
    TB_GETITEMRECT,
    TB_BUTTONSTRUCTSIZE,
    TB_SETBUTTONSIZE,
    TB_SETBITMAPSIZE,
    TB_AUTOSIZE,
    // no 34
    TB_GETTOOLTIPS= 0x0400+35,
    TB_SETTOOLTIPS,
    TB_SETPARENT,
    // no 38
    TB_SETROWS= 0x0400+39,
    TB_GETROWS,
    TB_GETBITMAPFLAGS,
    TB_SETCMDID,
    TB_CHANGEBITMAP,
    TB_GETBITMAP,
    TB_GETBUTTONTEXTA,
    TB_REPLACEBITMAP,
    TB_SETINDENT,
    TB_SETIMAGELIST,
    TB_GETIMAGELIST,
    TB_LOADIMAGES,
    TB_GETRECT,  // wParam is the Cmd instead of index
    TB_SETHOTIMAGELIST,
    TB_GETHOTIMAGELIST,
    TB_SETDISABLEDIMAGELIST,
    TB_GETDISABLEDIMAGELIST,
    TB_SETSTYLE,
    TB_GETSTYLE,
    TB_GETBUTTONSIZE,
    TB_SETBUTTONWIDTH,
    TB_SETMAXTEXTROWS,
    TB_GETTEXTROWS,   //61
    TB_GETOBJECT,  // wParam == IID, lParam void **ppv
    TB_GETBUTTONINFOW,
    TB_SETBUTTONINFOW,
    TB_GETBUTTONINFOA,
    TB_SETBUTTONINFOA, //66
    TB_INSERTBUTTONW,
    TB_ADDBUTTONSW,
    TB_HITTEST,
    TB_SETDRAWTEXTFLAGS,    // wParam == mask lParam == bit values
    TB_GETHOTITEM,
    TB_SETHOTITEM,  // wParam == iHotItem
    TB_SETANCHORHIGHLIGHT,    // wParam == TRUE/FALSE
    TB_GETANCHORHIGHLIGHT,
    TB_GETBUTTONTEXTW,
    TB_SAVERESTOREW   ,
    TB_ADDSTRINGW,
    TB_MAPACCELERATORA,    // wParam == ch, lParam int * pidBtn
    TB_GETINSERTMARK,   // lParam == LPTBINSERTMARK
    TB_SETINSERTMARK,   // lParam == LPTBINSERTMARK
    TB_INSERTMARKHITTEST,   // wParam == LPPOINT lParam == LPTBINSERTMARK
    TB_MOVEBUTTON,
    TB_GETMAXSIZE,  // lParam == LPSIZE
    TB_SETEXTENDEDSTYLE,  // For TBSTYLE_EX_*
    TB_GETEXTENDEDSTYLE,  // For TBSTYLE_EX_*
    TB_GETPADDING,
    TB_SETPADDING,
    TB_SETINSERTMARKCOLOR   ,
    TB_GETINSERTMARKCOLOR   ,
    TB_MAPACCELERATORW,    //(90) wParam == ch, lParam int * pidBtn

    };

enum Toolbar_Notifications {
   TBN_FIRST=       0xfffffd44,  // which is actually the largest Unsigned.  Strange MicroSoft.
   TBN_DROPDOWN=    0xfffffd3a
   };


} // end of controls
}
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::controls::TBSTYLE_BUTTON;
using ratwin::controls::TBSTYLE_SEP;
using ratwin::controls::TBSTYLE_CHECK;
using ratwin::controls::TBSTYLE_GROUP;
using ratwin::controls::TBSTYLE_CHECKGROUP;
using ratwin::controls::TBSTYLE_DROPDOWN;
using ratwin::controls::TBSTYLE_AUTOSIZE;
using ratwin::controls::TBSTYLE_NOPREFIX;
using ratwin::controls::TBSTYLE_TOOLTIPS;
using ratwin::controls::TBSTYLE_WRAPABLE;
using ratwin::controls::TBSTYLE_ALTDRAG;
using ratwin::controls::TBSTYLE_FLAT;
using ratwin::controls::TBSTYLE_LIST;
using ratwin::controls::TBSTYLE_CUSTOMERASE;
using ratwin::controls::TBSTYLE_REGISTERDROP;
using ratwin::controls::TBSTYLE_TRANSPARENT;
using ratwin::controls::TBSTATE_CHECKED;
using ratwin::controls::TBSTATE_PRESSED;
using ratwin::controls::TBSTATE_ENABLED;
using ratwin::controls::TBSTATE_HIDDEN;
using ratwin::controls::TBSTATE_INDETERMINATE;
using ratwin::controls::TBSTATE_WRAP;
using ratwin::controls::TBSTATE_ELLIPSES;
using ratwin::controls::TBSTATE_MARKED;
using ratwin::controls::TB_ENABLEBUTTON;
using ratwin::controls::TB_CHECKBUTTON;
using ratwin::controls::TB_PRESSBUTTON;
using ratwin::controls::TB_HIDEBUTTON;
using ratwin::controls::TB_INDETERMINATE;
using ratwin::controls::TB_MARKBUTTON;
using ratwin::controls::TB_ISBUTTONENABLED;
using ratwin::controls::TB_ISBUTTONCHECKED;
using ratwin::controls::TB_ISBUTTONPRESSED;
using ratwin::controls::TB_ISBUTTONHIDDEN;
using ratwin::controls::TB_ISBUTTONINDETERMINATE;
using ratwin::controls::TB_ISBUTTONHIGHLIGHTED;
using ratwin::controls::TB_SETSTATE;
using ratwin::controls::TB_GETSTATE;
using ratwin::controls::TB_ADDBITMAP;
using ratwin::controls::TB_ADDBUTTONS;
using ratwin::controls::TB_INSERTBUTTON;
using ratwin::controls::TB_DELETEBUTTON;
using ratwin::controls::TB_GETBUTTON;
using ratwin::controls::TB_BUTTONCOUNT;
using ratwin::controls::TB_COMMANDTOINDEX;
using ratwin::controls::TB_SAVERESTOREA;
using ratwin::controls::TB_SAVERESTOREW;
using ratwin::controls::TB_CUSTOMIZE;
using ratwin::controls::TB_ADDSTRINGA;
using ratwin::controls::TB_ADDSTRINGW;
using ratwin::controls::TB_GETITEMRECT;
using ratwin::controls::TB_BUTTONSTRUCTSIZE;
using ratwin::controls::TB_SETBUTTONSIZE;
using ratwin::controls::TB_SETBITMAPSIZE;
using ratwin::controls::TB_AUTOSIZE;
using ratwin::controls::TB_GETTOOLTIPS;
using ratwin::controls::TB_SETTOOLTIPS;
using ratwin::controls::TB_SETPARENT;
using ratwin::controls::TB_SETROWS;
using ratwin::controls::TB_GETROWS;
using ratwin::controls::TB_SETCMDID;
using ratwin::controls::TB_CHANGEBITMAP;
using ratwin::controls::TB_GETBITMAP;
using ratwin::controls::TB_GETBUTTONTEXTA;
using ratwin::controls::TB_GETBUTTONTEXTW;
using ratwin::controls::TB_REPLACEBITMAP;
using ratwin::controls::TB_SETINDENT;
using ratwin::controls::TB_SETIMAGELIST;
using ratwin::controls::TB_GETIMAGELIST;
using ratwin::controls::TB_LOADIMAGES;
using ratwin::controls::TB_GETRECT;
using ratwin::controls::TB_SETHOTIMAGELIST;
using ratwin::controls::TB_GETHOTIMAGELIST;
using ratwin::controls::TB_SETDISABLEDIMAGELIST;
using ratwin::controls::TB_GETDISABLEDIMAGELIST;
using ratwin::controls::TB_SETSTYLE;
using ratwin::controls::TB_GETSTYLE;
using ratwin::controls::TB_GETBUTTONSIZE;
using ratwin::controls::TB_SETBUTTONWIDTH;
using ratwin::controls::TB_SETMAXTEXTROWS;
using ratwin::controls::TB_GETTEXTROWS;
using ratwin::controls::TB_GETOBJECT;
using ratwin::controls::TB_GETHOTITEM;
using ratwin::controls::TB_SETHOTITEM;
using ratwin::controls::TB_SETANCHORHIGHLIGHT;
using ratwin::controls::TB_GETANCHORHIGHLIGHT;
using ratwin::controls::TB_MAPACCELERATORA;
using ratwin::controls::TB_GETINSERTMARK;
using ratwin::controls::TB_SETINSERTMARK;
using ratwin::controls::TB_INSERTMARKHITTEST;
using ratwin::controls::TB_MOVEBUTTON;
using ratwin::controls::TB_GETMAXSIZE;
using ratwin::controls::TB_SETEXTENDEDSTYLE;
using ratwin::controls::TB_GETEXTENDEDSTYLE;
using ratwin::controls::TB_GETPADDING;
using ratwin::controls::TB_SETPADDING;
using ratwin::controls::TB_SETINSERTMARKCOLOR;
using ratwin::controls::TB_GETINSERTMARKCOLOR;
using ratwin::controls::TB_MAPACCELERATORW;
using ratwin::controls::TB_GETBITMAPFLAGS;
using ratwin::controls::TB_GETBUTTONINFOW;
using ratwin::controls::TB_SETBUTTONINFOW;
using ratwin::controls::TB_GETBUTTONINFOA;
using ratwin::controls::TB_SETBUTTONINFOA;
using ratwin::controls::TB_INSERTBUTTONW;
using ratwin::controls::TB_ADDBUTTONSW;
using ratwin::controls::TB_HITTEST;
using ratwin::controls::TB_SETDRAWTEXTFLAGS;
#endif
// ## END Generated Code


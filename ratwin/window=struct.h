// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: Dependant_Libs\Repertoire\ratwin\window=struct.h
// Revision: post-public build 6

#pragma once
#include "ratwin\message=struct.h"

STARTWRAP
namespace ratwin {
namespace window {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::window)
   SW_HIDE SW_SHOWNORMAL SW_NORMAL SW_SHOWMINIMIZED SW_SHOWMAXIMIZED SW_MAXIMIZE SW_SHOWNOACTIVATE
   SW_SHOW SW_MINIMIZE SW_SHOWMINNOACTIVE SW_SHOWNA SW_RESTORE SW_SHOWDEFAULT SW_MAX
   CS_VREDRAW   CS_HREDRAW   CS_DBLCLKS  CS_OWNDC CS_CLASSDC    CS_PARENTDC CS_NOCLOSE   CS_SAVEBITS CS_BYTEALIGNCLIENT
   CS_BYTEALIGNWINDOW   CS_GLOBALCLASS  CS_IME
   WS_OVERLAPPED  WS_POPUP  WS_CHILD WS_MINIMIZE WS_VISIBLE WS_DISABLED   WS_CLIPSIBLINGS WS_CLIPCHILDREN  WS_MAXIMIZE
   WS_CAPTION WS_BORDER   WS_DLGFRAME  WS_VSCROLL  WS_HSCROLL  WS_SYSMENU  WS_THICKFRAME  WS_GROUP  WS_TABSTOP         
   WS_MINIMIZEBOX  WS_MAXIMIZEBOX WS_TILED WS_ICONIC   WS_SIZEBOX WS_OVERLAPPEDWINDOW WS_TILEDWINDOW  
   WS_POPUPWINDOW WS_CHILDWINDOW
   WS_EX_DLGMODALFRAME   WS_EX_NOPARENTNOTIFY WS_EX_TOPMOST    WS_EX_ACCEPTFILES WS_EX_TRANSPARENT   WS_EX_MDICHILD          
   WS_EX_TOOLWINDOW    WS_EX_WINDOWEDGE    WS_EX_CLIENTEDGE  WS_EX_CONTEXTHELP  WS_EX_RIGHT  WS_EX_LEFT WS_EX_RTLREADING        
   WS_EX_LTRREADING  WS_EX_LEFTSCROLLBAR  WS_EX_RIGHTSCROLLBAR   WS_EX_CONTROLPARENT   WS_EX_STATICEDGE   WS_EX_APPWINDOW         
   WS_EX_OVERLAPPEDWINDOW WS_EX_PALETTEWINDOW
   SBS_HORZ SBS_VERT SBS_TOPALIGN SBS_LEFTALIGN SBS_BOTTOMALIGN SBS_RIGHTALIGN SBS_SIZEBOXTOPLEFTALIGN
   SBS_SIZEBOXBOTTOMRIGHTALIGN SBS_SIZEBOX SBS_SIZEGRIP   
   CW_USEDEFAULT
   GWL_WNDPROC GWL_HINSTANCE GWL_HWNDPARENT GWL_STYLE GWL_EXSTYLE GWL_USERDATA GWL_ID              
   GW_HWNDFIRST GW_HWNDLAST GW_HWNDNEXT GW_HWNDPREV GW_OWNER GW_CHILD          GW_MAX
   SIZE_RESTORED SIZE_MINIMIZED SIZE_MAXIMIZED SIZE_MAXSHOW SIZE_MAXHIDE     
*/
// ## BEGIN MacroCloak Generated Code
#if defined (SW_HIDE)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef SW_HIDE
#undef SW_SHOWNORMAL
#undef SW_NORMAL
#undef SW_SHOWMINIMIZED
#undef SW_SHOWMAXIMIZED
#undef SW_MAXIMIZE
#undef SW_SHOWNOACTIVATE
#undef SW_SHOW
#undef SW_MINIMIZE
#undef SW_SHOWMINNOACTIVE
#undef SW_SHOWNA
#undef SW_RESTORE
#undef SW_SHOWDEFAULT
#undef SW_MAX
#undef CS_VREDRAW
#undef CS_HREDRAW
#undef CS_DBLCLKS
#undef CS_OWNDC
#undef CS_CLASSDC
#undef CS_PARENTDC
#undef CS_NOCLOSE
#undef CS_SAVEBITS
#undef CS_BYTEALIGNCLIENT
#undef CS_BYTEALIGNWINDOW
#undef CS_GLOBALCLASS
#undef CS_IME
#undef WS_OVERLAPPED
#undef WS_POPUP
#undef WS_CHILD
#undef WS_MINIMIZE
#undef WS_VISIBLE
#undef WS_DISABLED
#undef WS_CLIPSIBLINGS
#undef WS_CLIPCHILDREN
#undef WS_MAXIMIZE
#undef WS_CAPTION
#undef WS_BORDER
#undef WS_DLGFRAME
#undef WS_VSCROLL
#undef WS_HSCROLL
#undef WS_SYSMENU
#undef WS_THICKFRAME
#undef WS_GROUP
#undef WS_TABSTOP
#undef WS_MINIMIZEBOX
#undef WS_MAXIMIZEBOX
#undef WS_TILED
#undef WS_ICONIC
#undef WS_SIZEBOX
#undef WS_OVERLAPPEDWINDOW
#undef WS_TILEDWINDOW
#undef WS_POPUPWINDOW
#undef WS_CHILDWINDOW
#undef WS_EX_DLGMODALFRAME
#undef WS_EX_NOPARENTNOTIFY
#undef WS_EX_TOPMOST
#undef WS_EX_ACCEPTFILES
#undef WS_EX_TRANSPARENT
#undef WS_EX_MDICHILD
#undef WS_EX_TOOLWINDOW
#undef WS_EX_WINDOWEDGE
#undef WS_EX_CLIENTEDGE
#undef WS_EX_CONTEXTHELP
#undef WS_EX_RIGHT
#undef WS_EX_LEFT
#undef WS_EX_RTLREADING
#undef WS_EX_LTRREADING
#undef WS_EX_LEFTSCROLLBAR
#undef WS_EX_RIGHTSCROLLBAR
#undef WS_EX_CONTROLPARENT
#undef WS_EX_STATICEDGE
#undef WS_EX_APPWINDOW
#undef WS_EX_OVERLAPPEDWINDOW
#undef WS_EX_PALETTEWINDOW
#undef SBS_HORZ
#undef SBS_VERT
#undef SBS_TOPALIGN
#undef SBS_LEFTALIGN
#undef SBS_BOTTOMALIGN
#undef SBS_RIGHTALIGN
#undef SBS_SIZEBOXTOPLEFTALIGN
#undef SBS_SIZEBOXBOTTOMRIGHTALIGN
#undef SBS_SIZEBOX
#undef SBS_SIZEGRIP
#undef CW_USEDEFAULT
#undef GWL_WNDPROC
#undef GWL_HINSTANCE
#undef GWL_HWNDPARENT
#undef GWL_STYLE
#undef GWL_EXSTYLE
#undef GWL_USERDATA
#undef GWL_ID
#undef GW_HWNDFIRST
#undef GW_HWNDLAST
#undef GW_HWNDNEXT
#undef GW_HWNDPREV
#undef GW_OWNER
#undef GW_CHILD
#undef GW_MAX
#undef SIZE_RESTORED
#undef SIZE_MINIMIZED
#undef SIZE_MAXIMIZED
#undef SIZE_MAXSHOW
#undef SIZE_MAXHIDE
#endif
// ## END Generated Code

enum SW_window {
   SW_HIDE= 0,
   SW_SHOWNORMAL= 1,
   SW_NORMAL= 1,
   SW_SHOWMINIMIZED= 2,
   SW_SHOWMAXIMIZED= 3,
   SW_MAXIMIZE= 3,
   SW_SHOWNOACTIVATE= 4,
   SW_SHOW= 5,
   SW_MINIMIZE= 6,
   SW_SHOWMINNOACTIVE= 7,
   SW_SHOWNA= 8,
   SW_RESTORE= 9,
   SW_SHOWDEFAULT= 10,
   SW_MAX= 10
   };

enum SIZE_window {
   SIZE_RESTORED,
   SIZE_MINIMIZED,
   SIZE_MAXIMIZED,
   SIZE_MAXSHOW  ,
   SIZE_MAXHIDE
   };

typedef long (__stdcall* WNDPROC)(types::HWND, unsigned, unsigned, ulong);
typedef long (__stdcall* WNDPROC_2)(message::sMSG);  // same stack image, but treated as a single structure instead of individual items

template <typename CharT>
struct WNDCLASS {
   unsigned style;
   union {
      WNDPROC lpfnWndProc;
      WNDPROC_2 WndProc2;
      };
   int cbClsExtra;
   int cbWndExtra;
   types::HINSTANCE hInstance;
   types::HICON hIcon;
   types::HCURSOR hCursor;
   union {
      types::HBRUSH hbrBackground;         //handle
      int /*1 + color::sys_color_index*/ colorBackground;  //pre-defined background
      };
   const CharT* lpszMenuName;
   union {
      const CharT* lpszClassName;  // yucky name
      const CharT* className;  // clean name for same variable
      };
   };

template <typename CharT>
class window_class : public WNDCLASS<CharT> {
public:
   RATWIN_EXPORT window_class (const CharT* classname = 0);
   };

enum WC_style {  //first member of Window Class
   CS_VREDRAW=          0x0001,
   CS_HREDRAW=          0x0002,
   CS_KEYCVTWINDOW=     0x0004,
   CS_DBLCLKS=          0x0008,
   CS_OWNDC=            0x0020,
   CS_CLASSDC=          0x0040,
   CS_PARENTDC=         0x0080,
   CS_NOKEYCVT=         0x0100,
   CS_NOCLOSE=          0x0200,
   CS_SAVEBITS=         0x0800,
   CS_BYTEALIGNCLIENT=  0x1000,
   CS_BYTEALIGNWINDOW=  0x2000,
   CS_GLOBALCLASS=      0x4000,
   CS_IME=              0x00010000
   };


enum style {  //style param to CreateWindow
   WS_OVERLAPPED=       0x00000000L,
   WS_POPUP=            0x80000000L,
   WS_CHILD=            0x40000000L,
   WS_MINIMIZE=         0x20000000L,
   WS_VISIBLE=          0x10000000L,
   WS_DISABLED=         0x08000000L,
   WS_CLIPSIBLINGS=     0x04000000L,
   WS_CLIPCHILDREN=     0x02000000L,
   WS_MAXIMIZE=         0x01000000L,
   WS_CAPTION=          0x00C00000L,
   WS_BORDER=           0x00800000L,
   WS_DLGFRAME=         0x00400000L,
   WS_VSCROLL=          0x00200000L,
   WS_HSCROLL=          0x00100000L,
   WS_SYSMENU=          0x00080000L,
   WS_THICKFRAME=       0x00040000L,
   WS_GROUP=            0x00020000L,
   WS_TABSTOP=          0x00010000L,
   WS_MINIMIZEBOX=      0x00020000L,
   WS_MAXIMIZEBOX=      0x00010000L,
   WS_TILED=            WS_OVERLAPPED,
   WS_ICONIC=           WS_MINIMIZE,
   WS_SIZEBOX=          WS_THICKFRAME,
   WS_OVERLAPPEDWINDOW= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
   WS_TILEDWINDOW=      WS_OVERLAPPEDWINDOW,
   WS_POPUPWINDOW=      WS_POPUP | WS_BORDER | WS_SYSMENU,
   WS_CHILDWINDOW=      WS_CHILD
   };

enum extended_style {  //first parameter to CreateWindowEx
   WS_EX_DLGMODALFRAME=     0x00000001L,
   WS_EX_NOPARENTNOTIFY=    0x00000004L,
   WS_EX_TOPMOST=           0x00000008L,
   WS_EX_ACCEPTFILES=       0x00000010L,
   WS_EX_TRANSPARENT=       0x00000020L,
   WS_EX_MDICHILD=          0x00000040L,
   WS_EX_TOOLWINDOW=        0x00000080L,
   WS_EX_WINDOWEDGE=        0x00000100L,
   WS_EX_CLIENTEDGE=        0x00000200L,
   WS_EX_CONTEXTHELP=       0x00000400L,
   WS_EX_RIGHT=             0x00001000L,
   WS_EX_LEFT=              0x00000000L,
   WS_EX_RTLREADING=        0x00002000L,
   WS_EX_LTRREADING=        0x00000000L,
   WS_EX_LEFTSCROLLBAR=     0x00004000L,
   WS_EX_RIGHTSCROLLBAR=    0x00000000L,
   WS_EX_CONTROLPARENT=     0x00010000L,
   WS_EX_STATICEDGE=        0x00020000L,
   WS_EX_APPWINDOW=         0x00040000L,
   WS_EX_OVERLAPPEDWINDOW=  WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE,
   WS_EX_PALETTEWINDOW=     WS_EX_WINDOWEDGE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST
   };



enum scroll_style {
   SBS_HORZ=                    0x0000L,
   SBS_VERT=                    0x0001L,
   SBS_TOPALIGN=                0x0002L,
   SBS_LEFTALIGN=               0x0002L,
   SBS_BOTTOMALIGN=             0x0004L,
   SBS_RIGHTALIGN=              0x0004L,
   SBS_SIZEBOXTOPLEFTALIGN=     0x0002L,
   SBS_SIZEBOXBOTTOMRIGHTALIGN= 0x0004L,
   SBS_SIZEBOX=                 0x0008L,
   SBS_SIZEGRIP=                0x0010L,
   };
   
const int CW_USEDEFAULT=   0x80000000;

enum window_long_offset {
   GWL_WNDPROC= -4,
   GWL_HINSTANCE= -6,
   GWL_HWNDPARENT= -8,
   GWL_STYLE= -16,
   GWL_EXSTYLE= -20,
   GWL_USERDATA= -21,
   GWL_ID= -12
   };

struct CREATESTRUCT {
   void* lpCreateParams;
   types::HINSTANCE hInstance;
   types::HMENU hMenu;
   types::HWND hwndParent;
   int cy;
   int cx;
   int y;
   int x;
   long style;
   char* lpszName;
   char* lpszClass;
   ulong dwExStyle;
   };

enum GW {  // used with GetWindow
   GW_HWNDFIRST=0,
   GW_HWNDLAST,
   GW_HWNDNEXT,
   GW_HWNDPREV,
   GW_OWNER,
   GW_CHILD,
   GW_MAX=GW_CHILD
   };


struct SCROLLINFO {  // used with Get/SetScrollInfo
    unsigned    cbSize;
    unsigned    fMask;
    int     nMin;
    int     nMax;
    unsigned    nPage;
    int     nPos;
    int     nTrackPos;
    };



} } //ratwin
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::window::SW_HIDE;
using ratwin::window::SW_SHOWNORMAL;
using ratwin::window::SW_NORMAL;
using ratwin::window::SW_SHOWMINIMIZED;
using ratwin::window::SW_SHOWMAXIMIZED;
using ratwin::window::SW_MAXIMIZE;
using ratwin::window::SW_SHOWNOACTIVATE;
using ratwin::window::SW_SHOW;
using ratwin::window::SW_MINIMIZE;
using ratwin::window::SW_SHOWMINNOACTIVE;
using ratwin::window::SW_SHOWNA;
using ratwin::window::SW_RESTORE;
using ratwin::window::SW_SHOWDEFAULT;
using ratwin::window::SW_MAX;
using ratwin::window::CS_VREDRAW;
using ratwin::window::CS_HREDRAW;
using ratwin::window::CS_DBLCLKS;
using ratwin::window::CS_OWNDC;
using ratwin::window::CS_CLASSDC;
using ratwin::window::CS_PARENTDC;
using ratwin::window::CS_NOCLOSE;
using ratwin::window::CS_SAVEBITS;
using ratwin::window::CS_BYTEALIGNCLIENT;
using ratwin::window::CS_BYTEALIGNWINDOW;
using ratwin::window::CS_GLOBALCLASS;
using ratwin::window::CS_IME;
using ratwin::window::WS_OVERLAPPED;
using ratwin::window::WS_POPUP;
using ratwin::window::WS_CHILD;
using ratwin::window::WS_MINIMIZE;
using ratwin::window::WS_VISIBLE;
using ratwin::window::WS_DISABLED;
using ratwin::window::WS_CLIPSIBLINGS;
using ratwin::window::WS_CLIPCHILDREN;
using ratwin::window::WS_MAXIMIZE;
using ratwin::window::WS_CAPTION;
using ratwin::window::WS_BORDER;
using ratwin::window::WS_DLGFRAME;
using ratwin::window::WS_VSCROLL;
using ratwin::window::WS_HSCROLL;
using ratwin::window::WS_SYSMENU;
using ratwin::window::WS_THICKFRAME;
using ratwin::window::WS_GROUP;
using ratwin::window::WS_TABSTOP;
using ratwin::window::WS_MINIMIZEBOX;
using ratwin::window::WS_MAXIMIZEBOX;
using ratwin::window::WS_TILED;
using ratwin::window::WS_ICONIC;
using ratwin::window::WS_SIZEBOX;
using ratwin::window::WS_OVERLAPPEDWINDOW;
using ratwin::window::WS_TILEDWINDOW;
using ratwin::window::WS_POPUPWINDOW;
using ratwin::window::WS_CHILDWINDOW;
using ratwin::window::WS_EX_DLGMODALFRAME;
using ratwin::window::WS_EX_NOPARENTNOTIFY;
using ratwin::window::WS_EX_TOPMOST;
using ratwin::window::WS_EX_ACCEPTFILES;
using ratwin::window::WS_EX_TRANSPARENT;
using ratwin::window::WS_EX_MDICHILD;
using ratwin::window::WS_EX_TOOLWINDOW;
using ratwin::window::WS_EX_WINDOWEDGE;
using ratwin::window::WS_EX_CLIENTEDGE;
using ratwin::window::WS_EX_CONTEXTHELP;
using ratwin::window::WS_EX_RIGHT;
using ratwin::window::WS_EX_LEFT;
using ratwin::window::WS_EX_RTLREADING;
using ratwin::window::WS_EX_LTRREADING;
using ratwin::window::WS_EX_LEFTSCROLLBAR;
using ratwin::window::WS_EX_RIGHTSCROLLBAR;
using ratwin::window::WS_EX_CONTROLPARENT;
using ratwin::window::WS_EX_STATICEDGE;
using ratwin::window::WS_EX_APPWINDOW;
using ratwin::window::WS_EX_OVERLAPPEDWINDOW;
using ratwin::window::WS_EX_PALETTEWINDOW;
using ratwin::window::SBS_HORZ;
using ratwin::window::SBS_VERT;
using ratwin::window::SBS_TOPALIGN;
using ratwin::window::SBS_LEFTALIGN;
using ratwin::window::SBS_BOTTOMALIGN;
using ratwin::window::SBS_RIGHTALIGN;
using ratwin::window::SBS_SIZEBOXTOPLEFTALIGN;
using ratwin::window::SBS_SIZEBOXBOTTOMRIGHTALIGN;
using ratwin::window::SBS_SIZEBOX;
using ratwin::window::SBS_SIZEGRIP;
using ratwin::window::CW_USEDEFAULT;
using ratwin::window::GWL_WNDPROC;
using ratwin::window::GWL_HINSTANCE;
using ratwin::window::GWL_HWNDPARENT;
using ratwin::window::GWL_STYLE;
using ratwin::window::GWL_EXSTYLE;
using ratwin::window::GWL_USERDATA;
using ratwin::window::GWL_ID;
using ratwin::window::GW_HWNDFIRST;
using ratwin::window::GW_HWNDLAST;
using ratwin::window::GW_HWNDNEXT;
using ratwin::window::GW_HWNDPREV;
using ratwin::window::GW_OWNER;
using ratwin::window::GW_CHILD;
using ratwin::window::GW_MAX;
using ratwin::window::SIZE_RESTORED;
using ratwin::window::SIZE_MINIMIZED;
using ratwin::window::SIZE_MAXIMIZED;
using ratwin::window::SIZE_MAXSHOW;
using ratwin::window::SIZE_MAXHIDE;
#endif
// ## END Generated Code



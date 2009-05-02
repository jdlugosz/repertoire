// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\window.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_WINDOW_INCLUDED
#define RATWIN_WINDOW_INCLUDED

#include "ratwin\base.h"
#include "classics\string.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  CreateWindowExA (
    unsigned long dwExStyle,
    const char* lpClassName,
    const char* lpWindowName,
    unsigned long dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    Dlugosz::ratwin::arg::arg32 hWndParent ,
    Dlugosz::ratwin::arg::arg32 hMenu,
    Dlugosz::ratwin::arg::arg32 hInstance,
    void* lpParam);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  CreateWindowExW (
    unsigned long dwExStyle,
    const wchar_t* lpClassName,
    const wchar_t* lpWindowName,
    unsigned long dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    Dlugosz::ratwin::arg::arg32 hWndParent ,
    Dlugosz::ratwin::arg::arg32 hMenu,
    Dlugosz::ratwin::arg::arg32 hInstance,
    void* lpParam);

__declspec(dllimport) int __stdcall ShowWindow (Dlugosz::ratwin::arg::arg32 hWnd, int nCmdShow);
__declspec(dllimport) int __stdcall UpdateWindow (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall SendMessageA (Dlugosz::ratwin::arg::arg32 hWnd, unsigned Msg, unsigned wParam, long lParam);
__declspec(dllimport) void __stdcall PostQuitMessage (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall DefWindowProcA (Dlugosz::ratwin::arg::arg32, unsigned Msg, unsigned wParam, unsigned long lParam);
__declspec(dllimport) unsigned short __stdcall RegisterClassA (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void* __stdcall GetWindowLongA (Dlugosz::ratwin::arg::arg32,int);
__declspec(dllimport) void* __stdcall SetWindowLongA (Dlugosz::ratwin::arg::arg32,int,void*);
__declspec(dllimport) int __stdcall SetPropA (Dlugosz::ratwin::arg::arg32, const char*, void*);
__declspec(dllimport) void* __stdcall GetPropA (Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) int __stdcall MoveWindow (Dlugosz::ratwin::arg::arg32, int X, int Y, int nWidth, int nHeight, int bRepaint);
__declspec(dllimport) unsigned long __stdcall CallWindowProcA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, unsigned, unsigned, unsigned long);
__declspec(dllimport) int __stdcall SetWindowTextA (Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) int __stdcall EnableWindow (Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) int __stdcall GetClientRect (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall GetWindowRect (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall ClientToScreen (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall ScreenToClient (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall DestroyWindow (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetWindow (Dlugosz::ratwin::arg::arg32, unsigned);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetParent (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall GetClassNameA (Dlugosz::ratwin::arg::arg32, char*, int);
__declspec(dllimport) int __stdcall SetScrollInfo (Dlugosz::ratwin::arg::arg32, int, void*, int);
__declspec(dllimport) int __stdcall GetScrollInfo (Dlugosz::ratwin::arg::arg32, int, void*);
__declspec(dllimport) int __stdcall InvalidateRect (Dlugosz::ratwin::arg::arg32, const void*, int);
__declspec(dllimport) int __stdcall ScrollWindowEx (Dlugosz::ratwin::arg::arg32, int, int, const void*, const void*, Dlugosz::ratwin::arg::arg32, void*, unsigned);
__declspec(dllimport) int __stdcall UnregisterClassA (const char*, Dlugosz::ratwin::arg::arg32);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace window {

typedef long (__stdcall* WNDPROC)(types::HWND, unsigned, unsigned, ulong);

struct WNDCLASS {
   unsigned style;
   WNDPROC lpfnWndProc;
   int cbClsExtra;
   int cbWndExtra;
   types::HINSTANCE hInstance;
   types::HICON hIcon;
   types::HCURSOR hCursor;
   union {
      types::HBRUSH hbrBackground;         //handle
      int /*1 + color::sys_color_index*/ colorBackground;  //pre-defined background
      };
   const char* lpszMenuName;
   union {
      const char* lpszClassName;
      const char* className;
      };
   };

class window_class : public WNDCLASS {
public:
   RATWIN_EXPORT window_class (const char* classname = 0);
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
   WS_OVERLAPPEDWINDOW= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |                              WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
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

    
inline
types::HWND CreateWindowEx (
    ulong dwExStyle,
    const char* lpClassName,
    const char* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    types::HMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ 
	using types::HWND;
	using types::HMENU;
	using types::HINSTANCE;
	return reinterpret_cast<HWND>(::CreateWindowExA(
   dwExStyle, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   reinterpret_cast<arg::arg32>(hMenu), 
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }

inline
types::HWND CreateWindowEx (
    ulong dwExStyle,
    const wchar_t* lpClassName,
    const wchar_t* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    types::HMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExW(
   dwExStyle, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent),
   reinterpret_cast<arg::arg32>(hMenu), 
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }

inline
types::HWND CreateWindowEx (
    ulong dwExStyle,
    const char* lpClassName,
    const char* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    int child_id,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExA(
   dwExStyle, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent),
   reinterpret_cast<arg::arg32>(child_id), 
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }
   
inline
types::HWND CreateWindowEx (
    ulong dwExStyle,
    types::ATOM window_class,
    const char* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    types::HMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
 { return CreateWindowEx (dwExStyle, reinterpret_cast<const char*>(window_class),
          lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam); }
    
inline
types::HWND CreateWindow (
    const char* lpClassName,
    const char* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    types::HMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExA(
   0, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   reinterpret_cast<arg::arg32>(hMenu), 
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }

inline
types::HWND CreateWindow (
    const wchar_t* lpClassName,
    const wchar_t* lpWindowName,
    ulong dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    types::HWND hWndParent,
    types::HMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExW(
   0, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   reinterpret_cast<arg::arg32>(hMenu), 
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }

RATWIN_EXPORT
types::HWND CreateWindow (const char* lpClassName, const char* lpWindowName, ulong dwStyle);

RATWIN_EXPORT
types::HWND CreateWindowEx (ulong, const char*, const char*, ulong dwStyle);

inline
bool ShowWindow (types::HWND hWnd, int nCmdShow)
{ return ::ShowWindow (reinterpret_cast<arg::arg32>(hWnd), nCmdShow); }

inline
bool UpdateWindow (types::HWND hWnd)
{ return ::UpdateWindow (reinterpret_cast<arg::arg32>(hWnd)); }

inline
long SendMessage (types::HWND hWnd, unsigned Msg, unsigned wParam=0, ulong lParam=0)
{ return ::SendMessageA (reinterpret_cast<arg::arg32>(hWnd), Msg,wParam, lParam); }

inline
long SendMessage (types::HWND hWnd, unsigned Msg, unsigned wParam, const void* lParam)
{ return ::SendMessageA (reinterpret_cast<arg::arg32>(hWnd), Msg,wParam, reinterpret_cast<ulong>(lParam)); }

inline void PostQuitMessage (int ExitCode)
 { ::PostQuitMessage (reinterpret_cast<arg::arg32>(ExitCode)); }
 
inline long DefWindowProc (types::HWND hWnd, unsigned Msg, unsigned wParam, ulong lParam)
 { return ::DefWindowProcA (reinterpret_cast<arg::arg32>(hWnd), Msg, wParam, lParam); }

inline types::ATOM RegisterClass (const WNDCLASS& lpWndClass)
 { return ::RegisterClassA (reinterpret_cast<arg::arg32>(const_cast<WNDCLASS*>(&lpWndClass))); }

inline void* GetWindowLong (types::HWND hWnd, int index)
 { return ::GetWindowLongA (reinterpret_cast<arg::arg32>(hWnd), index); }

inline void* SetWindowLong (types::HWND hWnd, int index, void* newval)
 { return ::SetWindowLongA (reinterpret_cast<arg::arg32>(hWnd), index, newval); }

inline void* SetWindowLong (types::HWND hWnd, int index, ulong newval)
 { return ::SetWindowLongA (reinterpret_cast<arg::arg32>(hWnd), index, (void*)newval); }

inline bool SetProp (types::HWND hWnd, const char* lpString, void* p)
 { return ::SetPropA (reinterpret_cast<arg::arg32>(hWnd), lpString, p); }

inline void* GetProp (types::HWND hWnd, const char* lpString)
 { return ::GetPropA (reinterpret_cast<arg::arg32>(hWnd), lpString); }

inline
bool MoveWindow (types::HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint= true)
 { return ::MoveWindow (reinterpret_cast<arg::arg32>(hWnd), X, Y, nWidth, nHeight, bRepaint); }

inline
ulong CallWindowProc (WNDPROC proc, types::HWND w, unsigned msg, unsigned p1, ulong p2)
  { return ::CallWindowProcA (reinterpret_cast<arg::arg32>(proc), reinterpret_cast<arg::arg32>(w), msg, p1, p2); }

inline
bool SetWindowText (types::HWND wnd, const char* text)
  { return ::SetWindowTextA (reinterpret_cast<arg::arg32>(wnd), text); }


inline
int EnableWindow (types::HWND wnd, bool enable)
 { return ::EnableWindow (reinterpret_cast<arg::arg32>(wnd), enable); }


inline
bool GetClientRect (types::HWND hWnd, types::RECT& rect)
 { return ::GetClientRect (reinterpret_cast<arg::arg32>(hWnd), &rect); }

inline
bool GetWindowRect (types::HWND hWnd, types::RECT& rect)
 { return ::GetWindowRect (reinterpret_cast<arg::arg32>(hWnd), &rect); }

inline
bool ClientToScreen (types::HWND hWnd, types::POINT& pt)
 { return ::ClientToScreen (reinterpret_cast<arg::arg32>(hWnd), &pt); }

inline
bool ScreenToClient (types::HWND hWnd, types::POINT& pt)
 { return ::ScreenToClient (reinterpret_cast<arg::arg32>(hWnd), &pt); }

inline
bool DestroyWindow (types::HWND window)
 { return ::DestroyWindow (reinterpret_cast<arg::arg32>(window)); }


enum GW {
   GW_HWNDFIRST=0,
   GW_HWNDLAST,
   GW_HWNDNEXT,
   GW_HWNDPREV,
   GW_OWNER,
   GW_CHILD,
   GW_MAX=GW_CHILD
   };

inline
types::HWND GetWindow (types::HWND wnd, GW cmd)
 { return reinterpret_cast<types::HWND>(::GetWindow (reinterpret_cast<arg::arg32>(wnd), cmd)); }

inline
types::HWND GetParent (types::HWND wnd)
 { return reinterpret_cast<types::HWND>(::GetParent (reinterpret_cast<arg::arg32>(wnd))); }

inline
int GetClassName (types::HWND wnd, char* buf, int buflen)
 { return ::GetClassNameA (reinterpret_cast<arg::arg32>(wnd), buf, buflen); }

RATWIN_EXPORT classics::string GetClassName (types::HWND hwnd);

struct SCROLLINFO {
    unsigned    cbSize;
    unsigned    fMask;
    int     nMin;
    int     nMax;
    unsigned    nPage;
    int     nPos;
    int     nTrackPos;
    };

inline int SetScrollInfo (types::HWND w, int flags, SCROLLINFO& info, bool redraw=true)
 { return ::SetScrollInfo (reinterpret_cast<arg::arg32>(w), flags, &info, redraw); }

inline int GetScrollInfo (types::HWND w, int flags, SCROLLINFO& info)
 { return ::GetScrollInfo (reinterpret_cast<arg::arg32>(w), flags, &info); }

inline int InvalidateRect (types::HWND w, const types::RECT& r, bool erase=true)
 { return ::InvalidateRect (reinterpret_cast<arg::arg32>(w), &r, erase); }

inline int InvalidateRect (types::HWND w, bool erase=true)
 { return ::InvalidateRect (reinterpret_cast<arg::arg32>(w), 0, erase); }

inline int ScrollWindow (
   types::HWND w, int dx, int dy,
   const types::RECT* scroll, const types::RECT* clip,
   /*HRGN*/ void* hrgnUpdate,
   types::RECT* prcUpdate,
   unsigned flags=7)
 { return ::ScrollWindowEx (reinterpret_cast<arg::arg32>(w),dx,dy,scroll,clip,reinterpret_cast<arg::arg32>(hrgnUpdate),prcUpdate,flags); }

inline int ScrollWindow (
   types::HWND w, int dx, int dy,
   unsigned flags=7)
 { return ScrollWindow (w,dx,dy,0,0,0,0,flags); }

inline int UnregisterClass (const char* szClass, types::HINSTANCE hInstance)
{ return ::UnregisterClassA(szClass, reinterpret_cast<arg::arg32>(hInstance)); }

} //end of window
   
}
ENDWRAP

#endif



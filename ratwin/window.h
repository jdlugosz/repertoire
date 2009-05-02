// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\window.h
// Revision: post-public build 5

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\window.h contains globals.  Use ratwin\window=struct.h instead.
#endif

#include "ratwin\window=struct.h"
#include "ratwin\ChildidOrHMENU.h"

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
__declspec(dllimport) int __stdcall SetWindowTextW (Dlugosz::ratwin::arg::arg32, const wchar_t*);
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
__declspec(dllimport) int __stdcall MapWindowPoints (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, void*, int);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace window {

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
    ChildidOrHMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ 
   using types::HWND;
//using types::HMENU;
//using types::HINSTANCE;
return reinterpret_cast<HWND>(::CreateWindowExA(
   dwExStyle, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   hMenu,
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
    ChildidOrHMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExW(
   dwExStyle, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent),
   hMenu,
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
    ChildidOrHMENU hMenu,
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
    ChildidOrHMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExA(
   0, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   hMenu,
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
    ChildidOrHMENU hMenu,
    types::HINSTANCE hInstance,
    void* lpParam)
{ return reinterpret_cast<types::HWND>(::CreateWindowExW(
   0, lpClassName, lpWindowName, dwStyle,
   X, Y, nWidth, nHeight, 
   reinterpret_cast<arg::arg32>(hWndParent), 
   hMenu,
   reinterpret_cast<arg::arg32>(hInstance), lpParam)); }

RATWIN_EXPORT
types::HWND CreateWindow (const char* lpClassName, const char* lpWindowName, ulong dwStyle);

RATWIN_EXPORT
types::HWND CreateWindowEx (ulong, const char*, const char*, ulong dwStyle);


inline
bool ShowWindow (types::HWND hWnd, SW_window nCmdShow)
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
bool SetWindowText (types::HWND wnd, const wchar_t* text)
  { return ::SetWindowTextW (reinterpret_cast<arg::arg32>(wnd), text); }

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
unsigned long // strange return value, rarely used so don't worry about RATing it
MapWindowPoints (types::HWND from, types::HWND to, types::POINT* p, int count)
 {
 return ::MapWindowPoints (reinterpret_cast<arg::arg32>(from), reinterpret_cast<arg::arg32>(to), p, count);
 }

inline
unsigned long // strange return value, rarely used so don't worry about RATing it
MapWindowPoints (types::HWND from, types::HWND to, types::RECT* p, int count)
 {
 return ::MapWindowPoints (reinterpret_cast<arg::arg32>(from), reinterpret_cast<arg::arg32>(to), p, 2*count);
 }

inline
bool DestroyWindow (types::HWND window)
 { return ::DestroyWindow (reinterpret_cast<arg::arg32>(window)); }

inline
types::HWND GetWindow (types::HWND wnd, GW cmd)
 { return reinterpret_cast<types::HWND>(::GetWindow (reinterpret_cast<arg::arg32>(wnd), cmd)); }

inline
types::HWND GetParent (types::HWND wnd)
 { return reinterpret_cast<types::HWND>(::GetParent (reinterpret_cast<arg::arg32>(wnd))); }

inline
int GetClassName (types::HWND wnd, char* buf, int buflen)
 { return ::GetClassNameA (reinterpret_cast<arg::arg32>(wnd), buf, buflen); }

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




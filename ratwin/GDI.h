// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\GDI.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_GDI_INCLUDED
#define RATWIN_GDI_INCLUDED

// This has the potential to be very large.  I need
// to find a logical way to further break it up.

#include "ratwin\bitmap.h"

// cloaked globals
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateCompatibleDC (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall SelectObject (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall DeleteDC (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall BeginPaint (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall EndPaint (Dlugosz::ratwin::arg::arg32, const void*);
__declspec(dllimport) int __stdcall SetBkMode (Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateSolidBrush (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetStockObject (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall GetSysColor (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall SetBkColor (Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllimport) int __stdcall ReleaseDC (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetDC (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetDCEx (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, unsigned long flags);
__declspec(dllimport) int __stdcall DeleteObject (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall RoundRect (Dlugosz::ratwin::arg::arg32, int, int, int, int, int, int);
__declspec(dllimport) int __stdcall SetDIBitsToDevice (Dlugosz::ratwin::arg::arg32, int, int, unsigned long, unsigned long, int, int, unsigned, unsigned, const void*, const /*BITMAPINFO*/ void*, unsigned int);
}


STARTWRAP
namespace ratwin {

namespace gdi {

struct PAINTSTRUCT {
   types::HDC hdc;
   bool fErase;
   types::RECT rcPaint;
   bool fRestore;
   bool fIncUpdate;
   byte rgbReserved[32];
   };

enum background_mode { TRANSPARENT= 1, OPAQUE= 2, BKMODE_LAST= 2 };


inline
types::HDC CreateCompatibleDC (types::HDC h)
 { return reinterpret_cast<types::HDC>(::CreateCompatibleDC(reinterpret_cast<arg::arg32>(h))); }

inline
types::HGDIOBJ SelectObject (types::HDC dc, types::HGDIOBJ object)
 { return reinterpret_cast<types::HGDIOBJ>(::SelectObject(reinterpret_cast<arg::arg32>(dc), reinterpret_cast<arg::arg32>(object))); }
inline
types::HBITMAP SelectObject (types::HDC dc, types::HBITMAP bitmap)
{ return static_cast<types::HBITMAP>(SelectObject(dc,static_cast<types::HGDIOBJ>(bitmap))); }
// add other SelectObject forms here... 
inline
bool DeleteDC (types::HDC dc)
 { return ::DeleteDC (reinterpret_cast<arg::arg32>(dc)); }
 
inline
types::HDC BeginPaint (types::HWND hWnd, PAINTSTRUCT* lpPaint)
 { return reinterpret_cast<types::HDC>(::BeginPaint(reinterpret_cast<arg::arg32>(hWnd), reinterpret_cast<arg::arg32>(lpPaint))); }

inline
bool EndPaint (types::HWND hWnd, const PAINTSTRUCT *lpPaint)
 { return ::EndPaint (reinterpret_cast<arg::arg32>(hWnd), lpPaint); }

inline int SetBkMode (types::HDC dc, background_mode x)
 { return ::SetBkMode (reinterpret_cast<arg::arg32>(dc), x); }

inline types::HBRUSH CreateSolidBrush (/*COLORREF*/ulong color)
 { return reinterpret_cast<types::HBRUSH>(::CreateSolidBrush(reinterpret_cast<arg::arg32>(color)));}

inline types::HDC GetDC (types::HWND h)
 { return reinterpret_cast<types::HDC>(::GetDC(reinterpret_cast<arg::arg32>(h))); }

inline types::HDC GetDC (types::HWND h, ulong flags)
 { return reinterpret_cast<types::HDC>(::GetDCEx(reinterpret_cast<arg::arg32>(h),reinterpret_cast<arg::arg32>(0),flags)); }

enum stock_object {
   WHITE_BRUSH=         0,
   LTGRAY_BRUSH=        1,
   GRAY_BRUSH=          2,
   DKGRAY_BRUSH=        3,
   BLACK_BRUSH=         4,
   NULL_BRUSH=          5,
   WHITE_PEN=           6,
   BLACK_PEN=           7,
   NULL_PEN=            8,
   OEM_FIXED_FONT=      10,
   ANSI_FIXED_FONT=     11,
   ANSI_VAR_FONT=       12,
   SYSTEM_FONT=         13,
   DEVICE_DEFAULT_FONT= 14,
   DEFAULT_PALETTE=     15,
   SYSTEM_FIXED_FONT=   16,
   DEFAULT_GUI_FONT=    17,
   };

inline types::HGDIOBJ GetStockObject (stock_object x)
 { return reinterpret_cast<types::HGDIOBJ>(::GetStockObject(reinterpret_cast<arg::arg32>(x))); }


enum system_color {
   COLOR_SCROLLBAR=         0,
   COLOR_BACKGROUND=        1,
   COLOR_ACTIVECAPTION=     2,
   COLOR_INACTIVECAPTION=   3,
   COLOR_MENU=              4,
   COLOR_WINDOW=            5,
   COLOR_WINDOWFRAME=       6,
   COLOR_MENUTEXT=          7,
   COLOR_WINDOWTEXT=        8,
   COLOR_CAPTIONTEXT=       9,
   COLOR_ACTIVEBORDER=      10,
   COLOR_INACTIVEBORDER=    11,
   COLOR_APPWORKSPACE=      12,
   COLOR_HIGHLIGHT=         13,
   COLOR_HIGHLIGHTTEXT=     14,
   COLOR_BTNFACE=           15,
   COLOR_BTNSHADOW=         16,
   COLOR_GRAYTEXT=          17,
   COLOR_BTNTEXT=           18,
   COLOR_INACTIVECAPTIONTEXT= 19,
   COLOR_BTNHIGHLIGHT=      20,
   COLOR_3DDKSHADOW=        21,
   COLOR_3DLIGHT=           22,
   COLOR_INFOTEXT=          23,
   COLOR_INFOBK=            24
   };

inline unsigned long GetSysColor (system_color color)
 { return ::GetSysColor (reinterpret_cast<arg::arg32>(color)); }

inline unsigned long SetBkColor (types::HDC dc, unsigned long color)
 { return ::SetBkColor (reinterpret_cast<arg::arg32>(dc), color); }

inline bool ReleaseDC (types::HWND wnd, types::HDC dc)
 { return ::ReleaseDC (reinterpret_cast<arg::arg32>(wnd), reinterpret_cast<arg::arg32>(dc)); }

inline bool DeleteObject (types::HGDIOBJ x)
 { return ::DeleteObject (reinterpret_cast<arg::arg32>(x)); }

inline bool RoundRect (types::HDC dc, int left, int top, int right, int bottom, int rwid, int rheight)
 { return ::RoundRect (reinterpret_cast<arg::arg32>(dc), left, top, right, bottom, rwid, rheight); }


enum colormode { DIB_RGB_COLORS, DIB_PAL_COLORS };
inline int SetDIBitsToDevice (types::HDC dc, int destx, int desty, int width, int height, int srcx, int srcy, unsigned first_scan, unsigned scan_count, const void* data, const ratwin::bitmap::BITMAPINFOHEADER* info, colormode mode)
 { return ::SetDIBitsToDevice (reinterpret_cast<arg::arg32>(dc), destx, desty, width, height, srcx, srcy, first_scan, scan_count, data, info, mode); }

} //end gdi

}
ENDWRAP

#endif


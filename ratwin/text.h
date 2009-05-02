// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\text.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\text.h contains globals.
#endif

#include "ratwin\color=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall TextOutA (Dlugosz::ratwin::arg::arg32, int, int, const char*, int);
__declspec(dllimport) int __stdcall TextOutW (Dlugosz::ratwin::arg::arg32, int, int, const wchar_t*, int);
__declspec(dllimport) int __stdcall DrawTextA (Dlugosz::ratwin::arg::arg32, const char*, int, Dlugosz::ratwin::arg::carg32, unsigned);
__declspec(dllimport) int __stdcall GetTextMetricsW (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall GetTextExtentPoint32A (Dlugosz::ratwin::arg::arg32, const char*, int, void*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall SetTextColor (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetTextColor (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall GetDialogBaseUnits();  // can't "cloak"
}


STARTWRAP
namespace ratwin {
namespace text {

inline bool TextOut (types::HDC dc, int x, int y, const char* s, int len)
 { return ::TextOutA (reinterpret_cast<arg::arg32>(dc), x,y,s,len); }

inline bool TextOut (types::HDC dc, int x, int y, const wchar_t* s, int len)
 { return ::TextOutW (reinterpret_cast<arg::arg32>(dc), x,y,s,len); }

enum TextOut_options {
   DT_TOP=              0x00000000,
   DT_LEFT=             0x00000000,
   DT_CENTER=           0x00000001,
   DT_RIGHT=            0x00000002,
   DT_VCENTER=          0x00000004,
   DT_BOTTOM=           0x00000008,
   DT_WORDBREAK=        0x00000010,
   DT_SINGLELINE=       0x00000020,
   DT_EXPANDTABS=       0x00000040,
   DT_TABSTOP=          0x00000080,
   DT_NOCLIP=           0x00000100,
   DT_EXTERNALLEADING=  0x00000200,
   DT_CALCRECT=         0x00000400,
   DT_NOPREFIX=         0x00000800,
   DT_INTERNAL=         0x00001000,
   DT_EDITCONTROL=      0x00002000,
   DT_PATH_ELLIPSIS=    0x00004000,
   DT_END_ELLIPSIS=     0x00008000,
   DT_MODIFYSTRING=     0x00010000,
   DT_RTLREADING=       0x00020000,
   DT_WORD_ELLIPSIS=    0x00040000,
   };

inline bool DrawText (types::HDC dc, const char* s, int len, const types::RECT& r, unsigned options)
 { return ::DrawTextA (reinterpret_cast<arg::arg32>(dc), s, len, reinterpret_cast<arg::carg32>(&r), options); }

struct TEXTMETRIC {
    long Height;
    long Ascent;
    long Descent;
    long InternalLeading;
    long ExternalLeading;
    long AveCharWidth;
    long MaxCharWidth;
    long Weight;
    long Overhang;
    types::POINT DigitizedAspect;
    wchar_t FirstChar;
    wchar_t LastChar;
    wchar_t DefaultChar;
    wchar_t BreakChar;
    byte Italic;
    byte Underlined;
    byte StruckOut;
    byte PitchAndFamily;
    byte CharSet;
    };

inline bool GetTextMetrics (types::HDC dc, TEXTMETRIC& dest)
 { return ::GetTextMetricsW (reinterpret_cast<arg::arg32>(dc), &dest); }


inline bool GetTextExtent (types::HDC dc, const char* s, int strlen, types::POINT& result)
 {
 return ::GetTextExtentPoint32A (reinterpret_cast<arg::arg32>(dc), s, strlen, &result);
 }

inline ulong SetTextColor (types::HDC dc, color::COLORREF newcolor)
 {
 return reinterpret_cast<ulong>(::SetTextColor (reinterpret_cast<arg::arg32>(dc), reinterpret_cast<arg::arg32>(newcolor)));
 }
 
inline ulong GetTextColor (types::HDC dc)
 {
 return reinterpret_cast<ulong>(::GetTextColor (reinterpret_cast<arg::arg32>(dc)));
 }

inline
types::POINT GetDialogBaseUnits()
// returns average character size in the system font.
 {
 unsigned long x= ::GetDialogBaseUnits();
 return types::POINT (x&0xffff, x>>16);
 }

}  //end text

}
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\MessageBox.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\MessageBox.h contains globals.
#endif


#include "ratwin\base.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) int __stdcall MessageBoxExA (Dlugosz::ratwin::arg::arg32 hWnd, const char* lpText, const char* lpCaption, unsigned uType, unsigned short langID);
__declspec(dllimport) int __stdcall MessageBoxExW (Dlugosz::ratwin::arg::arg32 hWnd, const wchar_t* lpText, const wchar_t* lpCaption, unsigned uType, unsigned short langID);
}


STARTWRAP
namespace ratwin {
namespace MessageBox {

enum options {
   MB_TYPEMASK= 0x0000000FL,
   MB_OK= 0,
   MB_OKCANCEL= 0x00000001L,
   MB_ABORTRETRYIGNORE= 0x00000002L,
   MB_YESNOCANCEL= 0x00000003L,
   MB_YESNO= 0x00000004L,
   MB_RETRYCANCEL= 0x00000005L,

   MB_ICONMASK= 0x000000F0L,
   MB_ICONHAND= 0x00000010L,
   MB_ICONQUESTION= 0x00000020L,
   MB_ICONEXCLAMATION= 0x00000030L,
   MB_ICONASTERISK= 0x00000040L,
   MB_USERICON= 0x00000080L,
   MB_ICONWARNING= MB_ICONEXCLAMATION,
   MB_ICONERROR= MB_ICONHAND,
   MB_ICONINFORMATION= MB_ICONASTERISK,
   MB_ICONSTOP= MB_ICONHAND,

   MB_DEFMASK= 0x00000F00L,
   MB_DEFBUTTON1= 0x00000000L,
   MB_DEFBUTTON2= 0x00000100L,
   MB_DEFBUTTON3= 0x00000200L,
   MB_DEFBUTTON4= 0x00000300L,

   MB_MODEMASK= 0x00003000L,
   MB_APPLMODAL= 0,
   MB_SYSTEMMODAL= 0x00001000L,
   MB_TASKMODAL= 0x00002000L,

   MB_MISCMASK= 0x0000C000L,
   MB_HELP= 0x00004000L, // Help Button
   MB_NOFOCUS= 0x00008000L,
   
   MB_SETFOREGROUND= 0x00010000L,
   MB_DEFAULT_DESKTOP_ONLY= 0x00020000L,
   MB_TOPMOST= 0x00040000L,
   MB_RIGHT= 0x00080000L,
   MB_RTLREADING= 0x00100000L,
   MB_SERVICE_NOTIFICATION= 0x00200000L,
   };

enum result {
   IDOK= 1, IDCANCEL, IDABORT, IDRETRY, IDIGNORE, IDYES, IDNO, IDCLOSE, IDHELP
   };
   
inline
result MessageBox (types::HWND parent, const char* text, const char* caption, classics::flagword<options> options=MB_OK, unsigned short LangID=0)
 { return static_cast<result>(::MessageBoxExA (reinterpret_cast<arg::arg32>(parent), text, caption, options.validdata(), LangID)); }
 
inline
result MessageBox (const char* text, const char* caption, classics::flagword<options> options=MB_OK, unsigned short LangID=0)
 { return static_cast<result>(::MessageBoxExA (0, text, caption, options.validdata(), LangID)); }

inline
result MessageBox (types::HWND parent, const wchar_t* text, const wchar_t* caption, classics::flagword<options> options=MB_OK, unsigned short LangID=0)
 { return static_cast<result>(::MessageBoxExW (reinterpret_cast<arg::arg32>(parent), text, caption, options.validdata(), LangID)); }
 
inline
result MessageBox (const wchar_t* text, const wchar_t* caption, classics::flagword<options> options=MB_OK, unsigned short LangID=0)
 { return static_cast<result>(::MessageBoxExW (0, text, caption, options.validdata(), LangID)); }

}}


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\message.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_MESSAGE_INCLUDED
#define RATWIN_MESSAGE_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall TranslateMessage (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) long __stdcall DispatchMessageA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall GetMessageA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, unsigned, unsigned);
__declspec(dllimport) int __stdcall PostMessageA (Dlugosz::ratwin::arg::arg32, unsigned, unsigned, unsigned long);
__declspec(dllimport) int __stdcall PostThreadMessageA (Dlugosz::ratwin::arg::arg32, unsigned, unsigned, unsigned long);
__declspec(dllimport) int __stdcall IsDialogMessageA (Dlugosz::ratwin::arg::arg32, const void*);
__declspec(dllimport) unsigned __stdcall SetTimer (Dlugosz::ratwin::arg::arg32, unsigned, unsigned, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall KillTimer (Dlugosz::ratwin::arg::arg32, unsigned);
__declspec(dllimport) unsigned __stdcall RegisterWindowMessageA (Dlugosz::ratwin::arg::carg32);
}

////////////////////////

STARTWRAP
namespace ratwin {

namespace message {

struct MSG {
   types::HWND hwnd;
   unsigned message;
   unsigned wParam;
   ulong lParam;
   ulong time;
   types::POINT pt;
   };

inline bool TranslateMessage (const MSG& msg)
 { return ::TranslateMessage (reinterpret_cast<arg::carg32>(&msg)); }


inline long DispatchMessage (const MSG& msg)
 { return ::DispatchMessageA (reinterpret_cast<arg::carg32>(&msg)); }

inline int GetMessage (MSG& msg, types::HWND h= 0, unsigned min=0, unsigned max=0)
 { return ::GetMessageA (reinterpret_cast<arg::arg32>(&msg), reinterpret_cast<arg::arg32>(h), min, max); }

inline
bool PostMessage (types::HWND wnd, unsigned msg, unsigned p1, ulong p2)
 { return ::PostMessageA (reinterpret_cast<arg::arg32>(wnd), msg, p1, p2); }

inline
bool PostThreadMessage (ulong id, unsigned msg, unsigned p1, ulong p2)
 { return ::PostThreadMessageA (reinterpret_cast<arg::arg32>(id), msg, p1, p2); }

inline
bool IsDialogMessage (types::HWND wnd, const MSG& msg)
 { return ::IsDialogMessageA (reinterpret_cast<arg::arg32>(wnd), &msg); }
 
inline
unsigned SetTimer (types::HWND hWnd, unsigned IDEvent, unsigned Elapse)
 { return ::SetTimer (reinterpret_cast<arg::arg32>(hWnd), IDEvent, Elapse, 0); }

inline
bool KillTimer (types::HWND hWnd, unsigned IDEvent)
 { return ::KillTimer (reinterpret_cast<arg::arg32>(hWnd), IDEvent); }

inline
unsigned RegisterWindowMessage (const char* s)
 { return ::RegisterWindowMessageA (reinterpret_cast<arg::carg32>(s)); }
 
} //end of message
}
ENDWRAP

#endif


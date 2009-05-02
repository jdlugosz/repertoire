// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\menu.h
// Revision: updated

#pragma once

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) unsigned long __stdcall CheckMenuItem (Dlugosz::ratwin::arg::arg32, unsigned, unsigned);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetMenu (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall TrackPopupMenuEx (Dlugosz::ratwin::arg::arg32, unsigned, int, int, Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetSystemMenu (Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall LoadMenuA (Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetSubMenu (Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) int __stdcall DestroyMenu (Dlugosz::ratwin::arg::arg32);
}

////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace menu {

enum flags {
   MF_CHECKED= 0x00000008L,
   MF_UNCHECKED= 0x00000000L,
   MF_BYCOMMAND= 0x00000000L,
   // get more of these later... don't feel up to it now <g>
   };

inline
ulong CheckMenuItem (types::HMENU hMenu, unsigned uIDCheckItem, unsigned uCheck)
 { return ::CheckMenuItem (reinterpret_cast<arg::arg32>(hMenu), uIDCheckItem, uCheck); }

inline types::HMENU GetMenu (types::HWND hWnd)
 { return reinterpret_cast<types::HMENU>(::GetMenu(reinterpret_cast<arg::arg32>(hWnd))); }


enum {
   TPM_LEFTBUTTON= 0x0000,
   TPM_RIGHTBUTTON= 0x0002,
   TPM_LEFTALIGN= 0x0000,
   TPM_CENTERALIGN= 0x0004,
   TPM_RIGHTALIGN= 0x0008,
   TPM_TOPALIGN= 0x0000,
   TPM_VCENTERALIGN= 0x0010,
   TPM_BOTTOMALIGN= 0x0020,
   TPM_HORIZONTAL= 0x0000,
   TPM_VERTICAL= 0x0040,
   TPM_NONOTIFY= 0x0080,
   TPM_RETURNCMD= 0x0100,
   };


inline bool TrackPopupMenu (types::HMENU m, unsigned flags, types::POINT location, types::HWND w)
 {
 return ::TrackPopupMenuEx (reinterpret_cast<arg::arg32>(m), flags, location.x, location.y, reinterpret_cast<arg::arg32>(w), 0);
 }

inline bool TrackPopupMenu (types::HMENU m, unsigned flags, types::POINT location, types::HWND w, const types::RECT& r)
 {
 struct {
    unsigned structsize;
    types::RECT exclusion;
    } param; //= { (sizeof param), r };
 param.structsize= sizeof param;
 param.exclusion= r;
 return ::TrackPopupMenuEx (reinterpret_cast<arg::arg32>(m), flags, location.x, location.y, reinterpret_cast<arg::arg32>(w), &param);
 }

inline types::HMENU GetSystemMenu (types::HWND w, bool revert= false)
 {
 return reinterpret_cast<types::HMENU>( ::GetSystemMenu(reinterpret_cast<arg::arg32>(w), revert) );
 }

inline types::HMENU LoadMenu (types::HINSTANCE module, const char* name)
 {
 return reinterpret_cast<types::HMENU>( ::LoadMenuA (reinterpret_cast<arg::arg32>(module), name) );
 }

inline types::HMENU GetSubMenu (types::HMENU m, int index)
 {
 return reinterpret_cast<types::HMENU>( ::GetSubMenu (reinterpret_cast<arg::arg32>(m), index) );
 }

inline bool DestroyMenu (types::HMENU m)
 {
 return ::DestroyMenu (reinterpret_cast<arg::arg32>(m));
 }
  
}  //end menu

}
ENDWRAP


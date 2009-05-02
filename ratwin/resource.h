// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\resource.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_RESOURCE_INCLUDED
#define RATWIN_RESOURCE_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  LoadBitmapA (Dlugosz::ratwin::arg::arg32 hInstance, const char* lpBitmapName);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  LoadIconA (Dlugosz::ratwin::arg::arg32 hInstance, const char* name);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  LoadCursorA (Dlugosz::ratwin::arg::arg32 hInstance, const char* name);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  LoadResource (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall
  FindResourceA (Dlugosz::ratwin::arg::arg32, const char*, const char*);
__declspec(dllimport) int __stdcall DestroyCursor (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall SetCursor (Dlugosz::ratwin::arg::arg32);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace resource {

enum cursor_id {
   IDC_ARROW=       32512,
   IDC_IBEAM=       32513,
   IDC_WAIT=        32514,
   IDC_CROSS=       32515,
   IDC_UPARROW=     32516,
   IDC_SIZENWSE=    32642,
   IDC_SIZENESW=    32643,
   IDC_SIZEWE=      32644,
   IDC_SIZENS=      32645,
   IDC_SIZEALL=     32646,
   IDC_NO=          32648,
   IDC_APPSTARTING= 32650,
   IDC_HELP=        32651,
   };
//   IDC_SIZE            MAKEINTRESOURCE(32640)  /* OBSOLETE: use IDC_SIZEALL */
//   IDC_ICON            MAKEINTRESOURCE(32641)  /* OBSOLETE: use IDC_ARROW */

   
inline types::HBITMAP LoadBitmap (types::HINSTANCE hInstance, const char* lpBitmapName)
{return reinterpret_cast<types::HBITMAP>(::LoadBitmapA (reinterpret_cast<arg::arg32>(hInstance), lpBitmapName)); }

inline types::HICON LoadIcon (types::HINSTANCE hInstance, const char* name)
{return reinterpret_cast<types::HICON>(::LoadIconA (reinterpret_cast<arg::arg32>(hInstance), name)); }

inline types::HICON LoadIcon (types::HINSTANCE hInstance, int intresource)
{return reinterpret_cast<types::HICON>(::LoadIconA (reinterpret_cast<arg::arg32>(hInstance), reinterpret_cast<const char*>(intresource))); }

inline types::HCURSOR LoadCursor (types::HINSTANCE hInstance, const char* name)
{return reinterpret_cast<types::HCURSOR>(::LoadCursorA (reinterpret_cast<arg::arg32>(hInstance), name)); }

inline bool DestroyCursor (types::HCURSOR x)
{return ::DestroyCursor (reinterpret_cast<arg::arg32>(x));}

inline types::HCURSOR LoadCursor (types::HINSTANCE hInstance, int intresource)
{return reinterpret_cast<types::HCURSOR>(::LoadCursorA (reinterpret_cast<arg::arg32>(hInstance), reinterpret_cast<const char*>(intresource))); }

inline types::HCURSOR SetCursor (types::HCURSOR x)
{return reinterpret_cast<types::HCURSOR>(::SetCursor (reinterpret_cast<arg::arg32>(x))); }

inline const void* LoadResource (types::HINSTANCE hInstance, types::HRSRC resource_handle)
{return ::LoadResource (reinterpret_cast<arg::arg32>(hInstance), reinterpret_cast<arg::arg32>(resource_handle)); }

inline types::HRSRC FindResource (types::HINSTANCE hInstance, const char* name, int type)
{return reinterpret_cast<types::HRSRC>(::FindResourceA(reinterpret_cast<arg::arg32>(hInstance), name, reinterpret_cast<const char*>(type))); }

}  //end resource

}
ENDWRAP
#endif


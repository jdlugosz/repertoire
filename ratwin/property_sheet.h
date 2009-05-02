// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\property_sheet=struct.h
// Revision: 


#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\property_sheet.h contains globals.  Use property_sheet=struct.h instead.
#endif
#include "ratwin\property_sheet=struct.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) void* __stdcall CreatePropertySheetPageA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) void* __stdcall CreatePropertySheetPageW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall DestroyPropertySheetPage (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall PropertySheetA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall PropertySheetW (Dlugosz::ratwin::arg::carg32);
}

STARTWRAP
namespace ratwin {
namespace property_sheet {

inline
types::HPROPSHEETPAGE CreatePropertySheetPage (const PROPSHEETPAGE<char>& pagedef)
 { return reinterpret_cast<types::HPROPSHEETPAGE>( ::CreatePropertySheetPageA (reinterpret_cast<arg::carg32>(&pagedef)) ); }

inline
types::HPROPSHEETPAGE CreatePropertySheetPage (const PROPSHEETPAGE<wchar_t>& pagedef)
 { return reinterpret_cast<types::HPROPSHEETPAGE>( ::CreatePropertySheetPageW (reinterpret_cast<arg::carg32>(&pagedef)) ); }

inline
int PropertySheet (const PROPSHEETHEADER<char>& sheet)
 { return ::PropertySheetA (reinterpret_cast<arg::carg32>(&sheet)); }

inline
bool DestroyPropertySheetPage (types::HPROPSHEETPAGE h)
 { return ::DestroyPropertySheetPage (reinterpret_cast<arg::arg32>(h)); }
 
}}
ENDWRAP


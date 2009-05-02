// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID=static.cpp
// Revision: public build 8, shipped on 11-July-2006

#include "ratwin\COM\GUID.h"

extern "C" {
__declspec(dllimport) int __stdcall StringFromGUID2 (Dlugosz::ratwin::arg::carg32, wchar_t*, int);
__declspec(dllimport) unsigned __stdcall CoCreateGuid (Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {
namespace Win32API {

int __stdcall StringFromGUID2 (const _GUID* a, wchar_t* b, int c)
 {
 return ::StringFromGUID2 (reinterpret_cast<arg::carg32>(a), b, c);
 }
 
unsigned __stdcall CoCreateGuid (_GUID* a)
 {
 return ::CoCreateGuid (reinterpret_cast<arg::arg32>(a));
 }


}}  //end of namespaces
ENDWRAP


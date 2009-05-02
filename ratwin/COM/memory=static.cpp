// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\memory=static.cpp
// Revision: post-public build 5, modified 25-Feb-2000 or later

#include "ratwin\COM\memory.h"

extern "C" {
__declspec(dllimport) void* __stdcall CoTaskMemAlloc (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void* __stdcall CoTaskMemRealloc (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall CoTaskMemFree (Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

void CoTaskMemFree (void* p)
 {
 ::CoTaskMemFree (reinterpret_cast<arg::arg32>(p));
 }

void* CoTaskMemAlloc_bytes (int size)
 {
 return ::CoTaskMemAlloc (reinterpret_cast<arg::arg32>(size));
 }



}
ENDWRAP


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\memory.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) void* __stdcall CoTaskMemAlloc (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void* __stdcall CoTaskMemRealloc (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall CoTaskMemFree (Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {

template<typename T>
inline T* CoTaskMemAlloc (int elcount)
 {
 return static_cast<T*> (::CoTaskMemAlloc (reinterpret_cast<arg::arg32>(elcount * sizeof(T))));
 }
 

inline void CoTaskMemFree (void* p)
 {
 ::CoTaskMemFree (reinterpret_cast<arg::arg32>(p));
 }

 
}
ENDWRAP


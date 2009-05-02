// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\memory.h
// Revision: post-public build 6

#pragma once

#include "ratwin\base.h"


STARTWRAP
namespace ratwin {

void CoTaskMemFree (void* p);
void* CoTaskMemAlloc_bytes (int size);
 
template<typename T>
inline T* CoTaskMemAlloc (int elcount)
 {
 return static_cast<T*> (CoTaskMemAlloc_bytes (elcount * sizeof(T)));
 }
 

}
ENDWRAP


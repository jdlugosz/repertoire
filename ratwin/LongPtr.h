// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\LongPtr.h
// Revision: post - public build 9

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

#ifndef _WIN64

class LongPtr {
   arg::arg32 fourbytes;
public:
   LongPtr() : fourbytes(0) {}
   LongPtr (long x) : fourbytes( reinterpret_cast<arg::arg32>(x) ) {}
   LongPtr (void* hmenu) : fourbytes( reinterpret_cast<arg::arg32>( hmenu ) ) {}
   operator arg::arg32() { return fourbytes; }
   operator void*() { return reinterpret_cast<void*>(fourbytes); }
   operator long() { return reinterpret_cast<long>(fourbytes); }
   };

#else
   // >> 64-bit version goes here
   #error "File not set up for Win64."
#endif

}
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\NumOrName.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined I646693f0_f9dc_11d3_8ded_0006296222ef
#define I646693f0_f9dc_11d3_8ded_0006296222ef

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

template <typename Char>
class NumOrName {
   const void* value;
public:
   NumOrName (unsigned short s) : value (reinterpret_cast<const void*>(s)) {}
   NumOrName (const Char* s) : value (s) {}
   operator arg::carg32() const  { return reinterpret_cast<arg::carg32>(value); }
   };


template <typename Char, typename E>
class NumOrNameOrEnum  {
   const void* value;
public:
   NumOrNameOrEnum (E x) : value (reinterpret_cast<const void*>(x)) {}
   NumOrNameOrEnum (unsigned short s) : value (reinterpret_cast<const void*>(s)) {}
   NumOrNameOrEnum (const Char* s) : value (s) {}
   operator arg::carg32() const  { return reinterpret_cast<arg::carg32>(value); }
   };

}
ENDWRAP
#endif


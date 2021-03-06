// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\new.h
// Revision: public build 9, shipped on 18-Oct-2006

/*  This file is provided as a replacement for the Standard <NEW.H> and related
   operator new() issues to overcome problems in the Microsoft 5.x run-time library.

   * IMPORTANT:  include this file in order for ::operator new() to have the correct
   behavior as specified by the C++ Standard.
*/

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "ratwin\size_t.h"


STARTWRAP
namespace classics {
namespace Standard {

typedef void (*new_handler)();
CLASSICS_EXPORT new_handler set_new_handler (new_handler new_p) throw();
CLASSICS_EXPORT void* op_new (size_t);

}} //end namespaces
ENDWRAP

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// back to Global scope here

inline void* operator new (size_t x)
 {
 return classics::Standard::op_new (x);
 }

inline void* operator new[] (size_t x)
 {
 return classics::Standard::op_new (x);
 }


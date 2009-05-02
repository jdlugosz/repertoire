// The Repertoire Project copyright 2004 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\dispose_traits.h
// Revision: fresh

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename Storage>  struct dispose_traits;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
struct dispose_traits <T*> {
   static void dispose (T* p)  { delete p; }
   static T* null() { return 0; }
   // duplicate ... ?  Expand only if clone() exists.
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}

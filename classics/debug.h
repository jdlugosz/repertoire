// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\debug.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined DLUGOSZ_CLASSICS_DEBUG_DEFINED
#define DLUGOSZ_CLASSICS_DEBUG_DEFINED

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {

namespace debug {

class noisy1 {
protected:
   CLASSICS_EXPORT noisy1();
   CLASSICS_EXPORT ~noisy1();
   CLASSICS_EXPORT noisy1 (const noisy1& other);
   };


} //end of debug

}
ENDWRAP
#endif


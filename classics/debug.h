// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\debug.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

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


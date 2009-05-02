// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\event_flag.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\base.h"
#include "classics\common.h"

STARTWRAP
namespace classics {


class event_flag {
   ratwin::types::HANDLE H;  //later will have something more specific.
public:
   enum type { auto_reset= 0, manual_reset=1 };
   CLASSICS_EXPORT event_flag (type tp, bool initial_state=false, const char* name= 0);
   CLASSICS_EXPORT ~event_flag();
   ratwin::types::HANDLE h() const { return H; }
   CLASSICS_EXPORT void set() const;
   CLASSICS_EXPORT void reset() const;
   CLASSICS_EXPORT void pulse() const;
   CLASSICS_EXPORT bool wait (unsigned timeout=-1) const;
   };



} // end of classics
ENDWRAP





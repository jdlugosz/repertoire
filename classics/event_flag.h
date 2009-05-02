// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\event_flag.h
// Revision: updated

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\base.h"
#include "classics\ustring.h"

STARTWRAP
namespace classics {


class event_flag {
   ratwin::types::Kernel_HANDLE H;
   CLASSICS_EXPORT static ratwin::types::Kernel_HANDLE common_create (bool tp, bool initial_state, const ustring& name, const ratwin::types::SECURITY_ATTRIBUTES*);
public:
   enum type { auto_reset= 0, manual_reset=1 };
   CLASSICS_EXPORT event_flag (type tp, bool initial_state=false);
   event_flag (type tp, bool initial_state , const ustring& name)
     : H(common_create (tp, initial_state, name, 0)) {}
   event_flag (type tp, bool initial_state , const ustring& name, const ratwin::types::SECURITY_ATTRIBUTES& sa)
     : H(common_create (tp, initial_state, name, &sa)) {}
   CLASSICS_EXPORT ~event_flag();
   ratwin::types::Kernel_HANDLE h() const { return H; }
   CLASSICS_EXPORT void set() const;
   CLASSICS_EXPORT void reset() const;
   CLASSICS_EXPORT void pulse() const;
   CLASSICS_EXPORT bool wait (unsigned timeout=-1) const;
   };



} // end of classics
ENDWRAP





// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\critical_section.h
// Revision: 

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\tasking\CriticalSection=struct.h"

STARTWRAP
namespace classics {

class critical_section : private ratwin::tasking::CRITICAL_SECTION {
   critical_section (const critical_section&);  //never defined
   void operator= (const critical_section&);  //never defined
public:
   CLASSICS_EXPORT critical_section();
   CLASSICS_EXPORT critical_section (bool blocked);
   CLASSICS_EXPORT ~critical_section();
   CLASSICS_EXPORT void enter();
   CLASSICS_EXPORT void leave();
   CLASSICS_EXPORT bool try_enter();
   class locker;
   };

// ==========

class critical_section::locker {
   critical_section& cs;
   locker (const locker&);  //never defined
   void operator= (const locker&);  //never defined
public:
   locker (critical_section& cs) : cs(cs) { cs.enter(); }
   ~locker() { cs.leave(); }
   };

} //end namespace classics
ENDWRAP


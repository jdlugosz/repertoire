// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\mutex.h
// Revision: post-public build 6

#pragma once
#if !defined Iec302e48_4691_11d3_aadc_0020af6bccd6
#define Iec302e48_4691_11d3_aadc_0020af6bccd6

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\base.h"
#include "classics\ustring.h"

STARTWRAP
namespace classics {

class mutex {
   ratwin::types::HANDLE H;  //later will have something more specific.
   bool Created;
   const wstring Name;
public:
   mutex (const mutex&);  //never defined
   void operator= (const mutex&);  //never defined
public:
   CLASSICS_EXPORT mutex (bool blocked=false);
   CLASSICS_EXPORT mutex (const ustring& name, bool blocked=false);
   CLASSICS_EXPORT ~mutex();
   void enter()  { wait(); }
   bool try_enter() { return wait(0); }
   CLASSICS_EXPORT bool wait (unsigned timeout=-1);
   CLASSICS_EXPORT void leave();
   bool created() const  { return Created; }
   ratwin::types::HANDLE h() const  { return H; }
   class locker;
   };
   
// ==========

class mutex::locker {
   mutex& cs;
   locker (const locker&);  //never defined
   void operator= (const locker&);  //never defined
public:
   locker (mutex& cs) : cs(cs) { cs.enter(); }
   ~locker() { cs.leave(); }
   };


} //end namespace classics
ENDWRAP
#endif


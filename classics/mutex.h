// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\mutex.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\base.h"
#include "classics\ustring.h"

STARTWRAP
namespace classics {

class mutex {
   ratwin::types::Kernel_HANDLE H;
   bool Created;
   const wstring Name;
public:
   mutex (const mutex&);  //never defined
   void operator= (const mutex&);  //never defined
public:
   CLASSICS_EXPORT mutex (bool blocked=false);
   CLASSICS_EXPORT mutex (const ustring& name, bool blocked=false, ratwin::types::SECURITY_ATTRIBUTES* sa=0);
   CLASSICS_EXPORT ~mutex();
   void enter()  { wait(); }
   bool try_enter() { return wait(0); }
   CLASSICS_EXPORT bool wait (unsigned timeout=-1);
   CLASSICS_EXPORT void leave();
   bool created() const  { return Created; }
   ratwin::types::Kernel_HANDLE h() const  { return H; }
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


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=can_handle.h
// Revision: public build 8, shipped on 11-July-2006

#include "classics\common.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class can_handle {
   mutable unsigned cloaked_Lifetime; // assume unsigned same size as pointer.
   void operator= (const can_handle&);  //never defined
public:
   CLASSICS_EXPORT lifetime* get_lifetime_object() const;
   lifetime* get_lifetime_object_for_unit_test() const { return reinterpret_cast<lifetime*>(~cloaked_Lifetime); }
   inline void set_lifetime_object (lifetime* p) const { cloaked_Lifetime= ~reinterpret_cast<unsigned>(p); p->deleted=0; }
   can_handle() : cloaked_Lifetime(~0) {}
   can_handle (const can_handle&) : cloaked_Lifetime(~0) {}
   ~can_handle() { cloaked_Lifetime=~0;  /* for error trapping */ }
   CLASSICS_EXPORT int get_reference_count() const;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class debug_can_handle : public can_handle {
public:
   CLASSICS_EXPORT static int object_count;
   debug_can_handle() { ++object_count; }
   ~debug_can_handle() { --object_count; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline
lifetime* Get_lifetime_object (can_handle* p)
 {
 if (p)  return p->get_lifetime_object();
 else  return lifetime::null();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics


ENDWRAP


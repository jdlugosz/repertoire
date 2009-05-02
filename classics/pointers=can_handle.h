// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=can_handle.h
// Revision: updated

#include "classics\common.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class can_handle {
   mutable unsigned cloaked_Lifetime; // assume unsigned same size as pointer.
   void operator= (const can_handle&);  //never defined
public:
   CLASSICS_EXPORT lifetime* get_lifetime_object() const;
   inline void set_lifetime_object (lifetime* p) const { cloaked_Lifetime= ~reinterpret_cast<unsigned>(p); p->deleted=0; }
   can_handle() : cloaked_Lifetime(~0) {}
   can_handle (const can_handle&) : cloaked_Lifetime(~0) {}
   ~can_handle() { cloaked_Lifetime=~0;  /* for error trapping */ }
   int get_reference_count() const { return get_lifetime_object()->owned_count; }
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


// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=can_handle.h
// Revision: public build 4, shipped on 29-Aug-98

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class can_handle {
   mutable lifetime* Lifetime;
   void operator= (const can_handle&);  //never defined
public:
   inline lifetime* get_lifetime_object() const;
   inline void set_lifetime_object (lifetime* p) { Lifetime=p; }
   can_handle() : Lifetime(0) {}
   can_handle (const can_handle&) : Lifetime(0) {}
   int get_reference_count() const { return Lifetime->owned_count; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline
lifetime* can_handle::get_lifetime_object() const
 {
 if (!Lifetime) {
    Lifetime= new lifetime;
    Lifetime->clear();
    }
 return Lifetime;
 }
 
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


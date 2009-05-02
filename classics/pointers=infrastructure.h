// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=infrastructure.h
// Revision: post-public build 6

#include "classics\atomic_counter.h"
#include "classics\fixed_memory_pool.h"

STARTWRAP
namespace classics {

// note:  handle_structure and lifetime *should* be in an internal namespace,
// but VC++5 tends to crash with this.  I'll wrap them after the compiler is
// updated.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct lifetime {
   CLASSICS_EXPORT static ts_static_fixed_memory_pool pool;
   static void* operator new (size_t size) { return pool.alloc (size); }
   static void operator delete (void* p)  { pool.free(p); }
   static int get_pool_use_count()  { return pool.use_count; }
   atomic_counter<int> owned_count;
   atomic_counter<int> unowned_count;
   atomic_counter<short> hold;
   ushort deleted;
   void clear() { owned_count= 0; unowned_count= 0; hold= -1;  deleted= true; }
   CLASSICS_EXPORT static lifetime* null();
   void inc_owned_count()  { owned_count.inc(); }
   bool inc_owned_count_firstp()  { return 1 != ++owned_count; }  //can detect 1st owner
   void inc_unowned_count()  { unowned_count.inc(); }
   bool dec_owned_count()  { return owned_count.dec(); }
   bool dec_unowned_count()  { return unowned_count.dec(); }
   bool dec_hold()  { return -1 == --hold; }
   inline bool dec_hold_and_delete();
   void inc_hold()  { hold.inc(); }
   bool is_unique() const  // !!  need to analyse threading issues
      { return owned_count == 1 && unowned_count == 0; }
   CLASSICS_EXPORT void check_no_baro();
   CLASSICS_EXPORT void claim_owned_reference();
   };

// -----------------------------------------

inline bool lifetime::dec_hold_and_delete()
 {
 long* x= reinterpret_cast<long*>(&hold);
 long oldval= internal::Xadd (x,-1);
 return oldval==0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct handle_structure_nt {  //non-template base
   lifetime* Lifetime;
   void* Data;
   handle_structure_nt (lifetime* Lifetime, void* p) : Lifetime(Lifetime), Data(p) { Lifetime->deleted= false; }
   ~handle_structure_nt() { Lifetime=0; Data=0; }  // for debugging.
   void assign (lifetime* L, void* p)  { Lifetime=L;  Data=p;  }
   CLASSICS_EXPORT void zap_unowned() const;  //called when baro count hits zero
   void inc_unowned_reference() const { Lifetime->inc_unowned_count(); }
   void dec_unowned_reference() const { if (Lifetime->dec_unowned_count()) zap_unowned(); }   
   };


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
struct handle_structure : private handle_structure_nt {
   typedef T Type;
   T* data() const { return static_cast<T*> (Data); }
   handle_structure (T* p) : handle_structure_nt (Get_lifetime_object(p), p) {}
   void operator= (T* p)  { handle_structure_nt::assign (Get_lifetime_object(p), p); }
   void inc_owned_reference() const { Lifetime->inc_owned_count(); }
   void dec_owned_reference() const { if (Lifetime->dec_owned_count()) zap_owned(); }
   void zap_owned() const;  //called when owned count hits zero
   void claim_owned_reference() const { Lifetime->claim_owned_reference(); }
   bool is_unique() const  { return Lifetime->is_unique(); }
   bool points_to (const T* p) const  { return data() == p; }
   operator bool() const  { return data(); }
   bool operator!() const  { return !data(); }
   using handle_structure_nt::inc_unowned_reference;
   using handle_structure_nt::dec_unowned_reference;
   const lifetime* get_lifetime_object() const  { return Lifetime; }
   };

template <typename T>
bool operator== (const handle_structure<T>& a, const handle_structure<T>& b)
 {
 return a.data() == b.data();
 }

/* ======================================================== */

template <typename T>
void handle_structure<T>::zap_owned() const
 {
 // first, remove the object itself.
 if (Lifetime->dec_hold_and_delete()) {
    // no more owners, and no more prospective owners either
    //    Lifetime->deleted= true;
    //    done as a side effect of the "...and_delete()".
    // The dec, test, and deleted=false needs to be atomic.
    Lifetime->inc_hold();
      // must prevent the destructor from deleting Lifetime, if it happens to
      // remove the last unowned count.
    delete data();
    Lifetime->dec_hold();
    Lifetime->check_no_baro();
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


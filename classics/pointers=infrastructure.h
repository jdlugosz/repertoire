// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=infrastructure.h
// Revision: public build 9, shipped on 18-Oct-2006

// #define CLOAK_LIFETIME

#include "classics\atomic_counter.h"
#include "classics\fixed_memory_pool.h"
#ifdef CLOAK_LIFETIME
#include "cloaked_pointer.h"
#endif

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
   static int get_pool_use_count()  { return pool.get_use_count(); }
   atomic_counter<int> owned_count;
   atomic_counter<int> unowned_count;
   atomic_counter<short> hold;
   ushort deleted;
      // 0xffff set magically as sticky-bottom for hold, assuming this is normally 0x0000.
      // 0x0002 set as debugging flag to show that this is on the free list
      // higher bits reserved for future use, may be set independantly when "not deleted".
   void clear() { owned_count= 0; unowned_count= 0; hold= -1;  deleted= 0x0001; }
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
   void claim_known_first_owned_reference()
      {  // This is much faster than claim_owned_reference.  Ignores threading issues, because nobody else knows about the object yet.
      // Call when you know the owned count was zero, and no other threads will manipulate this object, because it was just created.
      owned_count= 1;
      hold= 0;
      }
#if defined _DEBUG
   ~lifetime() {
      if ( 2 == internal::Xexchange (&deleted, 2)) {
         // duplicate free, will be on the freelist twice!
         ++*(reinterpret_cast<int*>(0));  // force pointer deref error.
         }
      }  // works with Lifetime test
#endif
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
#ifdef CLOAK_LIFETIME
   cloaked_pointer<lifetime, 0xFF123456> Lifetime;
#else
   mutable lifetime* Lifetime;
#endif
   void* Data;
   handle_structure_nt () { /* nothing */ }
   handle_structure_nt (lifetime* Lifetime, void* p) : Lifetime(Lifetime), Data(p) { Lifetime->deleted= 0x0000; }
   ~handle_structure_nt() { Lifetime=0; Data=0; }  // for debugging.
   void assign (lifetime* L, void* p)  { Lifetime=L;  Data=p;  }
   CLASSICS_EXPORT void zap_unowned() const;  //called when baro count hits zero
   void inc_unowned_reference() const { get_Lifetime()->inc_unowned_count(); }
   void dec_unowned_reference() const { if (get_Lifetime()->dec_unowned_count()) zap_unowned(); }
   lifetime* get_Lifetime() const
    {
    lifetime* retval= Lifetime;
    if (retval->deleted == 2) {
       // trying to activly use a deleted lifetime object!
       ++*(reinterpret_cast<int*>(0));  // force pointer error
       }
    return retval;
    }
   void inc_owned_reference() const { get_Lifetime()->inc_owned_count(); }
   void claim_owned_reference() const { Lifetime->claim_owned_reference(); }
   bool is_unique() const  { return get_Lifetime()->is_unique(); }
   operator bool() const  { return Data; }
   bool operator!() const  { return !Data; }
   const lifetime* get_lifetime_object() const
    {
    const lifetime* retval= Lifetime;
    if (retval->deleted == 2) {
       // trying to activly use a deleted lifetime object!
       ++*(reinterpret_cast<int*>(0));  // force pointer error
       }
    return retval;
    }
   lifetime* atomic_swap (lifetime* B) const;
   CLASSICS_EXPORT static void atomic_swap (handle_structure_nt* atomic_dest, handle_structure_nt* lone_source);
   void set_lifetime_object (lifetime* L) const { Lifetime=L; }
   };


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class handle_structure : protected handle_structure_nt {
protected:
   void dec_owned_reference() const { if (get_Lifetime()->dec_owned_count()) zap_owned(); }
   static void dec_owned_reference (const handle_structure<T>& self) { self.dec_owned_reference(); }
   void zap_owned() const;  //called when owned count hits zero
   T* data() const { return static_cast<T*> (Data); }
   static T* data (const handle_structure<T>& x)  { return x.data(); }
   void set_data (T* p) { Data= p; }
   void assign_owned (const handle_structure_nt& other)
         { other.inc_owned_reference(); dec_owned_reference(); handle_structure_nt::operator=(other); }
public:
   typedef T Type;
   template <typename U> friend class handle_structure;
   handle_structure (T* p) : handle_structure_nt (Get_lifetime_object(p), p) {}
   handle_structure (lifetime* L, T* p) : handle_structure_nt (L, p) {}
   template <typename U>
   handle_structure (const handle_structure<U>& other) : handle_structure_nt (other) {}
   void operator= (T* p)  { handle_structure_nt::assign (Get_lifetime_object(p), p); }
   bool points_to (const T* p) const  { return data() == p; }
   bool points_to (const handle_structure& h) const  { return data() == h.data(); }
   const T* const_object() const { return data(); }
   using handle_structure_nt::get_lifetime_object;
   using handle_structure_nt::is_unique;
//   using handle_structure_nt::operator bool;
   operator bool() const  { return handle_structure_nt::operator bool(); }
   using handle_structure_nt::operator!;
   };

template <typename T>
bool operator== (const handle_structure<T>& a, const handle_structure<T>& b)
 {
 return a.points_to (b);
 }

template <typename T>
bool operator!= (const handle_structure<T>& a, const handle_structure<T>& b)
 {
 return ! a.points_to (b);
 }

/* ======================================================== */

template <typename T>
void handle_structure<T>::zap_owned() const
 {
 lifetime* L= get_Lifetime();
 L->inc_unowned_count();
 // first, remove the object itself.
 if (L->dec_hold_and_delete()) {
    // no more owners, and no more prospective owners either
    //    Lifetime->deleted= 0xffff;
    //    done as a side effect of the "...and_delete()".
    // The dec, test, and deleted=false needs to be atomic.
    delete data();
    if (L->unowned_count.dec()) delete L;
    }
 else L->dec_unowned_count();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


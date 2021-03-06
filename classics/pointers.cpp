// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\pointers.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

lifetime* can_handle::get_lifetime_object() const
 {
 /* the Lifetime pointer is cloaked, so that bugs in user's code can't easily obtain a pointer
   to the lifetime object.
 */
 lifetime* Lifetime= reinterpret_cast<lifetime*>(~cloaked_Lifetime);
 if (!Lifetime) {  // could avoid this test, but need to change a few details.  Get back to it.
    Lifetime= new lifetime;
    Lifetime->clear();
    set_lifetime_object(Lifetime);
    }
 if (Lifetime->deleted & 3)  { // either flagged as deleted (1) or on the free list (2) but ignore other bits
    // stray pointer bug discovered!
    *(reinterpret_cast<int*>(0));
    // serious problem:  memory may have already been corrupted.
    }
 return Lifetime;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int can_handle::get_reference_count() const
 {
 lifetime* Lifetime= reinterpret_cast<lifetime*>(~cloaked_Lifetime);
 if (!Lifetime)  return 0;
 return Lifetime->owned_count;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static lifetime create_null()
 {
 lifetime Null;
 Null.owned_count= 1;
 Null.unowned_count= 1;
 Null.hold= 1;
 Null.deleted= 0x0000;
 return Null;
 }

// ------------------------------------

lifetime* lifetime::null()
 {
 static lifetime Null= create_null();
 return &Null;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void lifetime::check_no_baro()
// this is called after I know there are no owners and no holds.
// Meanwhile, if there are no borrowers, then there is no way the
// borrower count can increase.  So, no special locking is needed.
 {
 if (unowned_count == 0)  delete this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ts_static_fixed_memory_pool lifetime::pool;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void handle_structure_nt::zap_unowned() const
// this is intentionally not inline.
// No holds means no owners and no prospective owners.  This is called
// when the unowned count hits zero.  So, no special locking is needed.
 {
 if (Lifetime->hold == -1)  delete Lifetime;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline lifetime* handle_structure_nt::atomic_swap (lifetime* B) const
 {
 address_t b= reinterpret_cast<address_t>(B);
 address_t a= internal::Xexchange (reinterpret_cast<address_t*>(&Lifetime), b);
 return reinterpret_cast<lifetime*>(a);
 }


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void handle_structure_nt::atomic_swap (handle_structure_nt* atomic_dest, handle_structure_nt* lone_source)
 {
 __int64* dest= reinterpret_cast<__int64*>(atomic_dest);
 __int64* source= reinterpret_cast<__int64*>(lone_source);
 *source= classics::internal::Xexchange (dest, *source);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void lifetime::claim_owned_reference()
// Get an owner from a borrower, or a raw pointer.
 {
 inc_hold();
 if (deleted&1)  {
    dec_hold();
    throw exception ("classics", "Expired Baro Object", __FILE__, __LINE__);
       /** Exception thrown when you try to construct a regular handle from
       a baro (non-owning) handle and the underlying object has already
       been destroyed.
       */
    }
 if (inc_owned_count_firstp())
    // 1st owner needs to hold.  That cancels out the releasing of this hold.
    // So, only release if this is not the first owner.
    dec_hold();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int debug_can_handle::object_count;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace internal {

int unique_helper (volatile int& trans)
 {
 int already_pending= classics::internal::Xexchange (&trans, 1);
 if (already_pending) {
    __asm PAUSE;
    ratwin::util::Sleep (1);
    while (trans != 0)  {
       __asm PAUSE;
       ratwin::util::Sleep (1);
       }
    return 0;  // other thread did (and finished) the work.
    }
 return 1;  // I need to do the work.
 }

}

} // end classics
ENDWRAP


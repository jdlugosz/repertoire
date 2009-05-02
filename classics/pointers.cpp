// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers.cpp
// Revision: updated

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\pointers.h"
#include "classics\exception.h"

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
 if (Lifetime->deleted)  {
    // stray pointer bug discovered!
    __asm int 3;
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
 Null.deleted= false;
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

void lifetime::claim_owned_reference()
// Get an owner from a borrower.  If there are no existing owners,
// the object does not exist so I can't get another owner.
 {
 inc_hold();
 if (deleted)  {
    dec_hold();
    throw exception ("classics", "Expired Baro Object", __FILE__, __LINE__);
       /** Exception thrown when you try to construct a regular handle from
       a baro (non-owning) handle and the underlying object has already
       been destroyed.
       */
    }
 if (inc_owned_count())
    // 1st owner needs to hold.  That cancels out the releasing of this hold.
    // So, only release if this is not the first owner.
    dec_hold();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int debug_can_handle::object_count;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end classics
ENDWRAP


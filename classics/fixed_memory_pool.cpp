// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\fixed_memory_pool.h"
#include "classics\exception.h"
#include "classics\atomic_counter.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct nt_base_fixed_memory_pool::node {
   node* next;
   node* addptr (int Recsize, int count=1)
      { return reinterpret_cast<node*>((Recsize*count) + reinterpret_cast<byte*>(this)); }
   };

static nt_base_fixed_memory_pool::node Busy;

struct nt_base_fixed_memory_pool::chunk {
   chunk* next;
   int reccount;
   node* top;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline nt_base_fixed_memory_pool::node* nt_base_fixed_memory_pool::Xexchange (node** dest, node* source)
 {
 if (single_thread_only)
    {
    node* old= *dest;
    *dest= source;
    return old;
    }
 else
    return (nt_base_fixed_memory_pool::node*) internal::Xexchange ((volatile address_t*)dest, (address_t)source);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void inline nt_base_fixed_memory_pool::wait()
 {
 _asm PAUSE
 internal::Inc (&wait_count);
 const int duration= lengthy_operation ? 10 : 1;
 ratwin::util::Sleep(duration);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

nt_base_fixed_memory_pool::~nt_base_fixed_memory_pool()
 {
 //abandon the nodelist, and free the items in the chunklist.
 chunk* p= chunklist;
 while (p) {
    chunk* q= p->next;
    byte* top= reinterpret_cast<byte*>(p->top);
    delete[] top;
    p= q;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
nt_base_fixed_memory_pool::node* general_static_fixed_memory_pool<FAST_HEAP_CHECK>::newchunk()
 {
 cumulative_size += Chunksize;
 int blocksize= Recsize*Chunksize;
 int totalsize= blocksize + sizeof(chunk);  //note: alignment not considered.
 byte* top= static_cast<byte*>(new byte[totalsize]);
 chunk* p= reinterpret_cast<chunk*> (top + blocksize);
 p->top= reinterpret_cast<node*>(top);
 p->reccount= Chunksize;
 p->next= chunklist;
 chunklist= p;
 // now chop into individual nodes
 node* first= reinterpret_cast<node*>(top);
 node* n= first;
 for (int loop= 0;  loop < Chunksize;  loop++) {
    node* nextnode= n->addptr (Recsize);
    n->next= nextnode;
    n= nextnode;
    }
 group_free (first->addptr(Recsize), first->addptr(Recsize, Chunksize-1));
 return first;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool nt_base_fixed_memory_pool::check_address (const void* p) const
 {
 __try {
    const address_t address= reinterpret_cast<address_t>(p);
    for (const chunk* current_chunk= chunklist; current_chunk; current_chunk= current_chunk->next) {
       const address_t top= reinterpret_cast<address_t>(current_chunk->top);
       if (top > address)  continue;  // is before this chunk.
       address_t offset= address-top;
       #pragma warning (push)
       #pragma warning (disable: 4018)  // all values positive.
       if (offset/Recsize >= current_chunk->reccount)  continue;  // is after this chunk.
       #pragma warning (pop)
       if (offset%Recsize != 0)  return false;  // error: is not properly aligned.
       return true;  // is part of this chunk.
       }
    }
 __except (1) {
    return false; // pointer is really bad.
    }
 return false;  // can't find a matching pointer anywhere.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool FAST_policy<false>::check_heap()
 {
 acquire:
 node* Nodelist= Xexchange (&nodelist, &Busy);
 if (Nodelist == &Busy) {
    wait();
    goto acquire;
    }
 ++lengthy_operation;
 int maxcount= cumulative_size - use_count + 1;
 __try {
    for (node* p= Nodelist;  p;  p=p->next)
       if (maxcount-- == 0 || !check_address (p)) return false;
    }
 __finally {
   --lengthy_operation;
    nodelist= Nodelist;
    }
 return true;  // all OK.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool FAST_policy<true>::check_heap()
 {
 acquire:
 node* Nodelist= Xexchange (&nodelist, &Busy);
 if (Nodelist == &Busy) {
    wait();
    goto acquire;
    }
 ++lengthy_operation;
 __try {
    __try {
       unsigned int check= 0;
       node*p= nodelist;
       for (int loop= 0;  loop < freecount;  ++loop) {
          check += reinterpret_cast<unsigned int>(p);
          p= p->next;
          }
       if (p)  return false;  // list should have stopped here.
       return check == checksum;
       }
    __except (1) {  // presumably a bad pointer!
       return false;
       }
    }
 __finally {
   --lengthy_operation;
    nodelist= Nodelist;
    }
 return true;  // all OK.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
bool general_static_fixed_memory_pool<FAST_HEAP_CHECK>::check_heap()
 {
 ++lengthy_operation;
 bool retval= FAST_policy<FAST_HEAP_CHECK>::check_heap();
 --lengthy_operation;
 return retval;
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* nt_base_fixed_memory_pool::check_heap_p()
 {
 acquire:
 node* Nodelist= Xexchange (&nodelist, &Busy);
 if (Nodelist == &Busy) {
    wait();
    goto acquire;
    }
 ++lengthy_operation;
 int maxcount= cumulative_size - use_count + 1;
 __try {
    node* q= (node*)1;  // special flag for heap-top (not a normal node)
    for (node* p= Nodelist; p; p=p->next) {
       if (maxcount-- == 0)  return (node*)2;  // infinite loop!
       if (!check_address (p)) return q;
       q= p;
       }
    }
 __finally {
    --lengthy_operation;
    nodelist= Nodelist;
    }
 return 0;  // all OK.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline void FAST_policy<true>::note_alloc (void* p)
 {
 -- freecount;
 checksum -= reinterpret_cast<unsigned int>(p);
 }


inline void FAST_policy<true>::note_free (void* p)
 {
 ++ freecount;
 checksum += reinterpret_cast<unsigned int>(p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
void general_static_fixed_memory_pool<FAST_HEAP_CHECK>::group_free (nt_base_fixed_memory_pool::node* head, nt_base_fixed_memory_pool::node* tail)
 {
 retry:
 nt_base_fixed_memory_pool::node* orig= Xexchange (&nodelist, &Busy);
 if (orig == &Busy) {
    wait();
    goto retry;
    }
 nt_base_fixed_memory_pool::node* n= head;
 do {
    note_free (n);
    n= n->next;
    } while (n != tail);
 tail->next= orig;
 nodelist= head;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
void* general_static_fixed_memory_pool<FAST_HEAP_CHECK>::alloc (int size)
 {
 if (size != Recsize) {
    if (Recsize == 0) {
       //OK, do a self-configuration
       Recsize= size;  //set upon first call
       if (Chunksize == 0)  Chunksize= 16;  //use a meaningful default
       }
    else {  // a real error
       exception X ("Classics", "Invalid call", __FILE__, __LINE__);
       // if you get this error, it probably means that a derived class is calling the operator new defined
       // in a base class, and this code is only for objects that are all the same size.
       throw X;
       }
    }
 retry:
 node* retval= Xexchange (&nodelist, &Busy);
 if (!retval)  {
    nodelist= 0;
    retval= newchunk();  //repopulate the free list
    }
 else {  // normal case
    if (retval == &Busy) {
       wait();
       goto retry;
       }
    nodelist= retval->next;  //pop off a record
    }
 note_alloc (retval);
 ++use_count;
 if (callback)  callback (1, retval);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
void general_static_fixed_memory_pool<FAST_HEAP_CHECK>::free (void* p_raw)
 {
 --use_count;
 if (callback)  callback (2, p_raw);
 node* p= static_cast<node*>(p_raw);
 note_free (p);
 // push the node onto my freelist
 retry:
 node* orig= Xexchange (&nodelist, &Busy);
 if (orig == &Busy) {
    wait();
    goto retry;
    }
 p->next= orig;
 nodelist= p;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<bool FAST_HEAP_CHECK>
void general_static_fixed_memory_pool<FAST_HEAP_CHECK>::clean()
 {
 // doesn't do anything yet.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// explicit instantiations
template class general_static_fixed_memory_pool <true>;
template class general_static_fixed_memory_pool <false>;

} //end namespace classics
ENDWRAP



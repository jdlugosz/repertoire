// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool.cpp
// Revision: post-public build 6, updated 21 May 2004.

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\new.h"
#include "classics\fixed_memory_pool.h"
#include "classics\exception.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct static_fixed_memory_pool::node {
   node* next;
   };
   
struct static_fixed_memory_pool::chunk {
   chunk* next;
   int reccount;
   node* top;
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
static_fixed_memory_pool::~static_fixed_memory_pool()
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

void static_fixed_memory_pool::newchunk()
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
 int oldcount= use_count;
 if (callback)  callback (3, 0);
 for (int loop= 0;  loop < Chunksize;  loop++) {
    free (top);
    top += Recsize;  //advance position in bytes
    }
 if (callback)  callback (4, 0);
 use_count= oldcount;  //only counting what the user asked for
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool static_fixed_memory_pool::check_address (const void* p) const
 {
 #ifdef _WIN64
 	typedef __int64 address_t;
 #else
 	typedef unsigned int address_t;
 #endif
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
 return false;  // can't find a matching pointer anywhere.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
bool static_fixed_memory_pool::check_heap()
 {
 for (node* p= nodelist;  p;  p=p->next)
    if (!check_address (p)) return false;
 return true;  // all OK.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void* static_fixed_memory_pool::alloc (int size)
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
 if (!nodelist)  newchunk();  //repopulate the free list
 node* retval= nodelist;
 nodelist= retval->next;  //pop off a record
 ++use_count;
 if (callback)  callback (1, retval);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void static_fixed_memory_pool::free (void* p_raw)
 {
 --use_count;
 if (callback)  callback (2, p_raw);
 node* p= static_cast<node*>(p_raw);
 // push the node onto my freelist
 p->next= nodelist;
 nodelist= p;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void static_fixed_memory_pool::clean()
 {
 // doesn't do anything yet.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void* ts_static_fixed_memory_pool::alloc (int size)
 {
 if (!cs) {
    // first time through.  Must self-initialize, because this may be used by
    // constructors before static variables are constructed.
    cs= new critical_section;
    // >> but beware of race condition on (only) the first call.
    }
 critical_section::locker lock (*cs);
 return static_fixed_memory_pool::alloc (size);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void ts_static_fixed_memory_pool::free (void* p)
 {
#if 0
 if (!cs) {
    // first time through.  Must self-initialize, because this may be used by
    // constructors before static variables are constructed.
    cs= new critical_section;
    }
 // should not call free without calling alloc first!
#endif
 critical_section::locker lock (*cs);
 static_fixed_memory_pool::free (p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP



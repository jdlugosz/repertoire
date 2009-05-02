// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\fixed_memory_pool.h"

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
 
void* static_fixed_memory_pool::alloc (int size)
 {
 if (size != Recsize) {
    if (Recsize == 0) {
       //OK, do a self-configuration
       Recsize= size;  //set upon first call
       if (Chunksize == 0)  Chunksize= 16;  //use a meaningful default
       }
    else {  // a real error
       // >> error throw goes here.
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
    }
 critical_section::locker lock (*cs);
 return static_fixed_memory_pool::alloc (size);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void ts_static_fixed_memory_pool::free (void* p)
 {
 if (!cs) {
    // first time through.  Must self-initialize, because this may be used by
    // constructors before static variables are constructed.
    cs= new critical_section;
    }
 critical_section::locker lock (*cs);
 static_fixed_memory_pool::free (p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP



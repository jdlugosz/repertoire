// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool.h
// Revision: post-public build 6

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "classics\critical_section.h"

STARTWRAP
namespace classics {

class static_fixed_memory_pool {
   struct chunk;
   struct node;
   chunk* chunklist;
   node* nodelist;
   int Recsize;
   void newchunk();
protected:
   int Chunksize;
public:
   // note: no constructor, intentional! Requires all-zero filling.
   CLASSICS_EXPORT ~static_fixed_memory_pool();
   CLASSICS_EXPORT void* alloc (int size);
   CLASSICS_EXPORT void free (void*);
   CLASSICS_EXPORT void clean();
   int use_count;  //for auditing and leak detection
   void (*callback)(int mode, void* p);
   void* get_nodelist() const  { return nodelist; }  //for debugging and testing only.
   CLASSICS_EXPORT bool check_address (const void*p) const;  //for debugging: verify p is part of this pool, not forign.
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

//>> have another class that =does= have a proper constructor.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class ts_static_fixed_memory_pool : public static_fixed_memory_pool {
   critical_section* cs;
public:
   CLASSICS_EXPORT void* alloc (int size);
   CLASSICS_EXPORT void free (void*);
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// Important Note:
// The pool mixin idea does work (see memory_pool_benchmark.cxx and fixed_memory_pool_UT.cxx)
// but because of how the template works (each DLL contains its own copy
// of the `pool` static member), it won't correctly span DLL's.  That's
// why I'm not using it inside Classics!  These only work if all calls to the specialized
// `new` and `delete` take place from the same DLL.

template <typename T>
class pool_mixin {
   static static_fixed_memory_pool pool;
public:
   void* operator new (size_t size) { return pool.alloc (size); }
   void operator delete (void* p)  { pool.free(p); }
   static int get_pool_use_count()  { return pool.use_count; }
   static bool check_address (const void* p)  { return pool.check_address(p); }
   };

template <typename T>
static_fixed_memory_pool pool_mixin<T>::pool;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class ts_pool_mixin {
   static static_fixed_memory_pool pool;
   static critical_section cs;
public:
   void* operator new (size_t size);
   void operator delete (void* p);
   static int get_pool_use_count()  { return pool.use_count; }
   static bool check_address (const void* p)  { return pool.check_address(p); }
   };

template <typename T>
static_fixed_memory_pool ts_pool_mixin<T>::pool;

template <typename T>
critical_section ts_pool_mixin<T>::cs;

template <typename T>
void* ts_pool_mixin<T>::operator new (size_t size)
 {
 critical_section::locker lock (cs);
 return pool.alloc (size);
 }

template <typename T>
void ts_pool_mixin<T>::operator delete (void* p)
 {
 critical_section::locker lock (cs);
 pool.free(p);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


} //end namespace classics
ENDWRAP


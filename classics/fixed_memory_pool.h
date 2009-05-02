// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\fixed_memory_pool.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {

class nt_base_fixed_memory_pool {
public:
   struct chunk;
   struct node;
protected:
   chunk* chunklist;
   node* nodelist;
   int Recsize;
   int cumulative_size;
   int lengthy_operation;
   int use_count;  // important for delayed destructor
   bool shutdown_commanded;
   inline void wait();
   inline node* Xexchange (node** dest, node* source);
public:
   bool single_thread_only;
   int get_use_count() const { return use_count; }  //for auditing and leak detection
   void (*callback)(int mode, void* p);
   int Chunksize;
   int wait_count;  //for performance monitoring
   CLASSICS_EXPORT void purge();
   ~nt_base_fixed_memory_pool() { shutdown_commanded= true;  purge(); }
   void* get_nodelist() const  { return nodelist; }  //for debugging and testing only.
   int get_Recsize() const { return Recsize; }
   const chunk* get_chunklist() const  { return chunklist; }  // for debugging
   CLASSICS_EXPORT bool check_address (const void*p) const;  //for debugging: verify p is part of this pool, not forign.
   CLASSICS_EXPORT void* check_heap_p();  //variation returns the (first) offending node or null.
   };


template <bool FAST_HEAP_CHECK>
class FAST_policy;

template<>
class FAST_policy<true> : public nt_base_fixed_memory_pool {
   address_t checksum;
   int freecount;
protected:
   inline void note_alloc (void*);
   inline void note_free (void*);
   CLASSICS_EXPORT bool check_heap();  //for debugging: check the entire freelist.
public:
   };

template<>
class FAST_policy<false>  : public nt_base_fixed_memory_pool {
   // no data members.
protected:
   void note_alloc (void*) { /* nothing */ }
   void note_free (void*) { /* nothing */ }
   CLASSICS_EXPORT bool check_heap();  //for debugging: check the entire freelist.
public:
   };

template<bool FAST_HEAP_CHECK=false>
class general_static_fixed_memory_pool : public FAST_policy<FAST_HEAP_CHECK> {
   void group_free (nt_base_fixed_memory_pool::node* head, nt_base_fixed_memory_pool::node* tail);
   nt_base_fixed_memory_pool::node* newchunk();
public:
   general_static_fixed_memory_pool()
      { /* nothing */
         // note: no constructor, intentional! Requires all-zero filling.
      }
   general_static_fixed_memory_pool (bool single_threaded)
      {
      // this may be executed after the static instance of this class has already been in use!
      // it just sets an option, and does not change the internal state.
      single_thread_only= single_threaded;
      }
   CLASSICS_EXPORT void* alloc (int size);
   CLASSICS_EXPORT void free (void*);
   CLASSICS_EXPORT void clean();
   CLASSICS_EXPORT bool check_heap();
   };


class static_fixed_memory_pool : public general_static_fixed_memory_pool<> {
public:
   static_fixed_memory_pool() : general_static_fixed_memory_pool<>(true) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class ts_static_fixed_memory_pool : public general_static_fixed_memory_pool<> {
public:
   ts_static_fixed_memory_pool() : general_static_fixed_memory_pool<>(false) {}
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
protected:
   static static_fixed_memory_pool pool;
public:
   void* operator new (size_t size) { return pool.alloc (size); }
   void operator delete (void* p)  { pool.free(p); }
   static int get_pool_use_count()  { return pool.use_count; }
   static bool check_address (const void* p)  { return pool.check_address(p); }
#if _MSC_VER == 1200  //Microsoft v6.0
   void operator= (const pool_mixin&) {}  // work-around compiler bug.
#endif
   };

template <typename T>
static_fixed_memory_pool pool_mixin<T>::pool;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class ts_pool_mixin {
protected:
   static ts_static_fixed_memory_pool pool;
public:
   void* operator new (size_t size) { return pool.alloc (size); }
   void operator delete (void* p)  { pool.free(p); }
   static int get_pool_use_count()  { return pool.use_count; }
   static bool check_address (const void* p)  { return pool.check_address(p); }
#if _MSC_VER == 1200  //Microsoft v6.0
   void operator= (const pool_mixin&) {}  // work-around compiler bug.
#endif
   };

template <typename T>
ts_static_fixed_memory_pool ts_pool_mixin<T>::pool;



} //end namespace classics
ENDWRAP


// The Repertoire Project copyright 2004 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\data_t.h
// Revision: 

#pragma once
#include "classics\copy_semantics.h"
#include "classics\pointers.h"

namespace classics {

struct snoop_t;

// internal array, with virtual functions for handling actual element type.
class data_t : public virtual I_copy_semantics, public can_handle {
   void* Data;
   int Count;
   int Capacity;
protected:   
   const int Elsize;  // redundant, because I_copy_semantics has it, but faster to compute indexes.
   void initialize_all() { initialize_elements (Data, Count); }
   void initialize_all (const data_t& other)  { initialize_elements (Data, other.Data, Count); }
   void initialize_all (const void* data)  { initialize_elements (Data, data, Count); }
public:
   void* offset (void* data, int count) const  { return static_cast<byte*>(data) + (count*Elsize); }
   const void* offset (const void* data, int count) const  { return static_cast<const byte*>(data) + (count*Elsize); }
   CLASSICS_EXPORT data_t (int elsize);
   CLASSICS_EXPORT data_t (int elsize, int elcount);
   CLASSICS_EXPORT data_t (int elsize, int elcount, int capacity);
   CLASSICS_EXPORT virtual ~data_t();
   CLASSICS_EXPORT void* access (int index);
   void* iaccess (int index);  //internal access
   CLASSICS_EXPORT void* raccess (int index, int len);  // range access
   void* get_buffer() { return Data; }
   const void* get_buffer() const { return Data; }
   void debug_print() const;
   void debug_snoop (snoop_t&) const;
   virtual data_t* clone() const =0;
   virtual data_t* clone_empty (int reserve) const =0;
   data_t* resize_duplicate (int newsize);
   int elcount() const  { return Count; }
   int elcapacity() const { return Capacity; }
   CLASSICS_EXPORT void put (const void* data, int count, int startpos);
   CLASSICS_EXPORT void get (void* data, int count, int startpos) const;
   CLASSICS_EXPORT void truncate (int newsize);
   CLASSICS_EXPORT void reserve (int newsize);
   CLASSICS_EXPORT virtual void* resize (int size, int capacity);
   bool same_object (int pos, const void* data, int datalen) const;
   void splice_result (const void* old, int len, int pos, int dellen, const void* data, int datalen);
   void splice_result_inplace (int pos, int dellen, const void* data, int datalen);
   };

//////////////////////////////////////////////////

template <typename T>
struct specify_data_t {
   typedef T type;
   };

//////////////////////////////////////////////////

template <class T>
class g_data_t : private copy_semantics_g<T>, public data_t {
public:
   g_data_t () : data_t (sizeof(T)) {}
   ~g_data_t() { destroy_elements (get_buffer(), elcount()); }
   g_data_t (const g_data_t& other)
      : data_t (sizeof(T), other.elcount()) { initialize_all (other); }
   g_data_t (int elcount) 
      : data_t (sizeof(T), elcount) {initialize_all();}
   g_data_t (int elcount, int capacity)
      : data_t (sizeof(T), elcount, capacity) { initialize_all(); }
   g_data_t (int elcount, const void* data)
     : data_t (sizeof(T), elcount) { initialize_all (data); }
   g_data_t<T>* clone() const { return new g_data_t<T> (*this); }
   g_data_t<T>* clone_empty(int reserve) const { return new g_data_t<T> (0,reserve); }
   };

//////////////////////////////////////////////////

namespace vararray_internal {
// I can't make a static template member of a class, or these
// would go into data_t.

template <typename T>
T* make_the_empty()
 {
 static dynalloc_reservation<T> placement;
 T* p= ::new (placement) T;
 static dynalloc_reservation<lifetime> life_placement;
 lifetime* life= ::new(life_placement) lifetime;
 life->clear();
 life->inc_owned_count();
 p->set_lifetime_object(life);
 return p;
 }

template <typename T>
T* shared_empty()
 {
 static T* the_empty= 0;
 if (!the_empty)  the_empty= make_the_empty<T>();
 return the_empty;
 }

}

 
//////////////////////////////////////////////////

namespace vararray_internal {
// non-template base class for s_data_t
// because the code only needs the size, not the type itself.
class s_data_ntbase : public copy_semantics_s, public data_t {
public:
   s_data_ntbase (int elsize) : data_t (elsize), copy_semantics_s (elsize) {}
   ~s_data_ntbase() { }
   CLASSICS_EXPORT s_data_ntbase (const s_data_ntbase&);
   CLASSICS_EXPORT s_data_ntbase (int elsize, int elcount);
   CLASSICS_EXPORT s_data_ntbase (int elsize, int elcount, int capacity);
   CLASSICS_EXPORT s_data_ntbase (int elsize, int elcount, const void* data);
   CLASSICS_EXPORT data_t* clone() const;
   CLASSICS_EXPORT data_t* clone_empty(int reserve) const;
   };
   
} // end internal

//////////////////////////////////////////////////

template <typename T>
class s_data_t : public vararray_internal::s_data_ntbase {
public:
   s_data_t() : s_data_ntbase (sizeof(T)) {}
   s_data_t (const s_data_t& other) : s_data_ntbase (other) {}
   s_data_t (int elcount) : s_data_ntbase (sizeof(T), elcount) {}
   s_data_t (int elcount, int capacity) : s_data_ntbase (sizeof(T), elcount, capacity) {}
   s_data_t (int elcount, const void* data) : s_data_ntbase (sizeof(T), elcount, data) {}
   };
   

}


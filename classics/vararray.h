// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined CLASSICS_VARARRAY_INCLUDED
#define CLASSICS_VARARRAY_INCLUDED

#include "classics\pointers.h"
#include "classics\dynalloc_reservation.h"
#include <new>

STARTWRAP
namespace classics {


struct snoop_t;
enum make_alias_t { alias };

//namespace vararray_internal { //helpers for vararray

//////////////////////////////////////////////////

// internal array, with virtual functions for handling actual element type.
class data_t : public can_handle {
   void* Data;
   int Count;
   int Capacity;
protected:   
   const int Elsize;
   void initialize_all() { initialize_elements (Data, Count); }
   void initialize_all (const data_t& other)  { initialize_elements (Data, other.Data, Count); }
   void initialize_all (const void* data)  { initialize_elements (Data, data, Count); }
   virtual void initialize_elements (void* dest, int count) const =0;
   virtual void initialize_elements (void* dest, const void* src, int count) const =0;
   virtual void copy_elements (void* dest, const void* src, int count) const =0;
   virtual void destroy_elements (void* dest, int count) const =0;
   virtual void move_elements (void* dest, void* src, int count) const =0;   
public:
   void* offset (void* data, int count) const  { return static_cast<byte*>(data) + (count*Elsize); }
   const void* offset (const void* data, int count) const  { return static_cast<const byte*>(data) + (count*Elsize); }
   CLASSICS_EXPORT data_t (int elsize);
   data_t (int elsize, int elcount, void* mem) : Count(elcount), Capacity(elcount), Elsize(elsize), Data(mem) {}
   data_t (int elsize, int elcount, int capacity, void* mem) : Count(elcount), Capacity(capacity), Elsize(elsize), Data(mem) {}
   CLASSICS_EXPORT virtual ~data_t();
   CLASSICS_EXPORT void* access (int index);
   void* iaccess (int index);  //internal access
   CLASSICS_EXPORT void* raccess (int index, int len);  // range access
   void* get_buffer() { return Data; }
   void debug_print() const;
   void debug_snoop (snoop_t&) const;
   virtual data_t* clone() const =0;
   virtual data_t* clone_empty (int reserve) const =0;
   data_t* resize_duplicate (int newsize);
   int elcount() const  { return Count; }
   CLASSICS_EXPORT void put (const void* data, int count, int startpos);
   CLASSICS_EXPORT void get (void* data, int count, int startpos) const;
   CLASSICS_EXPORT void truncate (int newsize);
   CLASSICS_EXPORT void reserve (int newsize);
   CLASSICS_EXPORT virtual void* prep_result (int size, int capacity);
   CLASSICS_EXPORT virtual void* resize (int size, int capacity);
   CLASSICS_EXPORT void splice_result (const void* old, int len, int pos, int dellen, const void* data, int datalen);
   };

//////////////////////////////////////////////////

template <class T>
class g_data_t : public data_t {
   void initialize_elements (void* dest, int count) const;
   void initialize_elements (void* dest, const void* src, int count) const;
   void copy_elements (void* dest, const void* src, int count) const;
   void move_elements (void* dest, void* src, int count) const;
   void destroy_elements (void* dest, int count) const;
public:
   g_data_t ();
   ~g_data_t() { destroy_elements (get_buffer(), elcount()); }
   g_data_t (const g_data_t&);
   g_data_t (int elcount);
   g_data_t (int elcount, int capacity);
   g_data_t (int elcount, const void* data);
   data_t* clone() const;
   data_t* clone_empty(int reserve) const;
   };

// This is not inline because of an optomization problem with VC++5.0
template <typename T>
g_data_t<T>::g_data_t()
 : data_t (sizeof(T))
 {}

template <class T>
data_t* g_data_t<T>::clone() const
 {
 return new g_data_t<T> (*this);
 }

template <typename T>
data_t* g_data_t<T>::clone_empty (int reserve) const
 {
 return new g_data_t<T> (0,reserve);
 }

template <class T>
void g_data_t<T>::initialize_elements (void* dest_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 for (int loop= 0;  loop < count;  loop++) {
    new (dest++) T;
    }
 }

template <class T>
void g_data_t<T>::initialize_elements (void* dest_raw, const void* src_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 const T* src= static_cast<const T*>(src_raw);
 for (int loop= 0;  loop < count;  loop++) {
    new (dest++) T (*src++);
    }
 }
 
template <class T>
void g_data_t<T>::copy_elements (void* dest_raw, const void* src_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 const T* src= static_cast<const T*>(src_raw);
 for (int loop= 0;  loop < count;  loop++) {
    *dest++ = *src++;  //assignment
    }
 }
 
template <class T>
void g_data_t<T>::move_elements (void* dest_raw, void* src_raw, int count) const
 {
 // >> needs to handle overlapping elements!
 T* dest= static_cast<T*>(dest_raw);
 T* src= static_cast<T*>(src_raw);
 for (int loop= 0;  loop < count;  loop++) {
    new (dest++) T (*src);  //duplicate at new position
    src->T::~T();  //destroy the old
    ++src;
    }
 }

template <class T>
void g_data_t<T>::destroy_elements (void* dest_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 for (int loop= 0;  loop < count;  loop++) {
    dest->T::~T();
    ++dest;
    }
 }

template <class T>
g_data_t<T>::g_data_t (int elcount)
 : data_t (sizeof(T), elcount, ::operator new (elcount*sizeof(T)))
 {
 initialize_all();
 }

template <class T>
g_data_t<T>::g_data_t (int elcount, int capacity)
 : data_t (sizeof(T), elcount, capacity, ::operator new (capacity*sizeof(T)))
 {
 initialize_all();
 }

template <class T>
g_data_t<T>::g_data_t (int elcount, const void* data)
 : data_t (sizeof(T), elcount, ::operator new (elcount*sizeof(T)))
 {
 initialize_all (data);
 }

template <class T>
g_data_t<T>::g_data_t (const g_data_t& other)
 : data_t (sizeof(T), other.elcount(), ::operator new (sizeof(T)*other.elcount()))
 {
 initialize_all (other);
 }

//////////////////////////////////////////////////

class s_data_t : public data_t {
   CLASSICS_EXPORT void initialize_elements (void* dest, int count) const;
   CLASSICS_EXPORT void initialize_elements (void* dest, const void* src, int count) const;
   CLASSICS_EXPORT void copy_elements (void* dest, const void* src, int count) const;
   CLASSICS_EXPORT void move_elements (void* dest, void* src, int count) const;
   void destroy_elements (void* dest, int count) const   { /* does nothing */ }
public:
   s_data_t (int elsize) : data_t (elsize) {}
   ~s_data_t() { }
   CLASSICS_EXPORT s_data_t (const s_data_t&);
   CLASSICS_EXPORT s_data_t (int elsize, int elcount);
   CLASSICS_EXPORT s_data_t (int elsize, int elcount, int capacity);
   CLASSICS_EXPORT s_data_t (int elsize, int elcount, const void* data);
   CLASSICS_EXPORT data_t* clone() const;
   CLASSICS_EXPORT data_t* clone_empty(int reserve) const;
   };

//////////////////////////////////////////////////

class intermediate : public cow<data_t>, public can_handle {
   typedef cow<data_t> Base;
public:
   explicit intermediate (data_t* p) : Base(p) {}
   void operator= (data_t* p)  { Base::operator=(p); }
   ~intermediate() {}
   void debug_print() const;
   void debug_snoop (snoop_t&) const;
   data_t* get_data() const { return data(); }
   bool lazy_dup_core (data_t*&core);
   };
   
//////////////////////////////////////////////////

class chdata : public handle<intermediate> {
   typedef handle<intermediate> Base;
public:
   CLASSICS_EXPORT chdata (intermediate* core) : Base(core) {}
   ~chdata() {}
   void debug_print() const;
   CLASSICS_EXPORT void debug_snoop (snoop_t&) const;
   intermediate* get_data() const { return data(); }
   };

//////////////////////////////////////////////////

// A non-template base to abstract code out of all instantiations.
class nt_base {
   chdata data;
protected:
   nt_base (const chdata& data) : data(data) {}
   CLASSICS_EXPORT nt_base (data_t* core);
   CLASSICS_EXPORT nt_base (const nt_base&);
   CLASSICS_EXPORT void operator= (const nt_base&);
   void alias_with (const nt_base& other)  { data=other.data; }
   nt_base (nt_base& other, make_alias_t) : data (other.data) {}
   data_t& get_core() const  { return *data.get_data()->get_data(); }
   data_t& get_unique_core() const  { return *data.get_data()->operator->(); }
   void set_core (data_t* p)  { *data.get_data() = p; }
   void* access (int index)  { return get_unique_core().access(index); }
//   void* iaccess (int index)  { return get_unique_core().iaccess(index); }
   void* raccess (int index, int len)  { return get_unique_core().raccess(index, len); }
   const void* access (int index) const { return get_core().access(index); }
   const void* raccess (int index, int len) const { return get_core().raccess(index, len); }
   CLASSICS_EXPORT void replace (int pos, int lendel, const void* data, int buflen);
   virtual data_t* create_core (int capacity)  { return 0; } //***
   bool lazy_dup_core (data_t*&core)
      { return data.get_data()->lazy_dup_core (core); }
   ~nt_base() {}
public:
   CLASSICS_EXPORT void debug_print() const;
   CLASSICS_EXPORT void debug_snoop (snoop_t& results) const  { data.debug_snoop(results); }
   void truncate (int newsize) { get_unique_core().truncate (newsize); }
   CLASSICS_EXPORT void resize (int newsize);
   void reserve (int newsize) { get_core().reserve (newsize); }
   int elcount() const { return get_core().elcount(); }
   void remove (int pos, int len=1)
      { replace (pos, len, 0,0); }
   void remove_all ()
      { replace (0, elcount(), 0,0); }
   };


//}  //end of internal

//////////////////////////////////////////////////

template <class T>
class vararray : public /*vararray_internal::*/nt_base {
public:
   typedef T eltype;
   vararray (const /*vararray_internal::*/chdata& data) : nt_base(data) {}
   vararray (/*vararray_internal::*/data_t* core) : nt_base (core) {}
   vararray (vararray<T>& other, make_alias_t alias) : nt_base (other,alias) {}
   ~vararray() {}
   const T& get_at (int index) const  { return *static_cast<const T*>(access(index)); }
   void get (T* dest, int count, int startpos=0) const  { get_core().get (dest, count, startpos); }
   const T& operator[] (int index) const  { return get_at (index); }
   T& operator[] (int index)  { return *static_cast<T*>(access(index)); }  
      //necessary evil?
   void put_at (const T& val, int index)  { *static_cast<T*>(access(index)) = val; }
   void put (const T* src, int count, int startpos=0)  { get_unique_core().put (src, count, startpos); }
   T* get_buffer() { return static_cast<T*>(get_unique_core().get_buffer()); }
   const T* get_buffer() const { return static_cast<T*>(get_core().get_buffer()); }
   void replace (int pos, int lendel, const T* data, int buflen)
      { nt_base::replace (pos, lendel, data, buflen); }
   void replace (int pos, int lendel, const vararray<T>& other, int frompos, int fromlen)
      { nt_base::replace (pos, lendel, other.raccess(frompos, fromlen), fromlen); }
   int append (const T& x)  { int pos= elcount(); replace (pos, 0, &x, 1); return pos; }
   void append (const vararray<T>& other, int frompos, int fromlen)
      { replace (elcount(), 0, other, frompos, fromlen); }
   int sorted_insert (const T& value, int (*compare)(const T&, const T&));
   class iterator;
   };

//////////////////////////////////////////////////

template <typename T>
   class iterator {
      vararray<T> list;
      T* cheating;
      int count, loop;
   public:
      iterator (vararray<T>& list_) : list(list_), cheating(list.get_buffer()), count(list.elcount()), loop(0) {}
      iterator (vararray<T>& list_, make_alias_t) : list(list_,alias), cheating(list.get_buffer()), count(list.elcount()), loop(0) {}
      T* operator-> () const  { return cheating+loop; }
      T& operator* () const { return cheating[loop]; }
      operator bool() const { return loop < count; }
      bool operator++ ()
         { if (++loop < count)  return true;
           else { cheating=0; return false; } }
      int index() const  { return loop; }   //added 10-Dec-97
      };

template <typename T>
   class const_iterator {
      const vararray<T> list;
      const T* cheating;
      int count, loop;
   public:
      const_iterator (const vararray<T>& list_) : list(const_cast<vararray<T>&>(list_)), cheating(list.get_buffer()), count(list.elcount()), loop(0) {}
      const T* operator-> () const  { return cheating+loop; }
      const T& operator* () const { return cheating[loop]; }
      operator bool() const { return loop < count; }
      bool operator++ ()
         { if (++loop < count)  return true;
           else { cheating=0; return false; } }
      int index() const  { return loop; }   //added 10-Dec-97
      };

template <typename T>
int vararray<T>::sorted_insert (const T& value, int (*compare)(const T&, const T&))
 {
 for (int loop= elcount()-1;  loop >= 0;  loop--)
    if (compare (get_at(loop), value) <= 0)  break;
 replace (loop+1, 0, &value, 1);
 return loop+1;
 }

//////////////////////////////////////////////////

template <class T>
class vararray_g : public vararray<T> {
   static /*vararray_internal::*/g_data_t<T>* empty();
   static /*vararray_internal::*/g_data_t<T>* make_the_empty();
   data_t* create_core (int capacity);
public:
   vararray_g() : vararray<T> (empty()) {}
   explicit vararray_g (int elcount);
   vararray_g (int elcount, int capacity);
   void alias_with (vararray_g<T>& other) { nt_base::alias_with (other); }
   vararray_g (vararray_g<T>& other, make_alias_t alias) : vararray<T>(other,alias) {}
   vararray_g (const T* data, int len);
   ~vararray_g() {}
   };

template <typename T>
data_t* vararray_g<T>::create_core (int capacity)
 {
 return new /*vararray_internal::*/g_data_t<T>(0,capacity);
 }

template <class T>
g_data_t<T>* vararray_g<T>::make_the_empty()
 {
 static dynalloc_reservation<g_data_t<T> > placement;
 g_data_t<T>* p= new (placement) g_data_t<T>;
 static dynalloc_reservation<lifetime> life_placement;
 lifetime* life= ::new(life_placement) lifetime;
 life->clear();
 life->owned_count ++;
 p->set_lifetime_object(life);
 return p;
 }

template <class T>
g_data_t<T>* vararray_g<T>::empty()
 {
 static g_data_t<T>* p= make_the_empty();
 return p;
 }

template <class T>
vararray_g<T>::vararray_g (int elcount)
 : vararray<T> (new /*vararray_internal::*/g_data_t<T> (elcount))
 { }

template <class T>
vararray_g<T>::vararray_g (int elcount, int capacity)
 : vararray<T> (new /*vararray_internal::*/g_data_t<T> (elcount, capacity))
 { }

template <class T>
vararray_g<T>::vararray_g (const T* data, int elcount)
 : vararray<T> new (/*vararray_internal::*/g_data_t<T> (elcount, data))
 { }


//////////////////////////////////////////////////

template <class T>
class vararray_s : public vararray<T> {
   static /*vararray_internal::*/s_data_t* make_the_empty();
   static /*vararray_internal::*/s_data_t* empty();
   data_t* create_core (int capacity)  { return new /*vararray_internal::*/s_data_t(sizeof(T),0,capacity); }
public:
   vararray_s() : vararray<T> (empty()) {}
   explicit vararray_s (int elcount);
   vararray_s (int elcount, int capacity);
   void alias_with (vararray_s<T>& other) { nt_base::alias_with (other); }
   vararray_s (vararray_s<T>& other, make_alias_t alias) : vararray<T>(other,alias) {}
   vararray_s (const T* data, int len);
   ~vararray_s() {}
   };


template <class T>
vararray_s<T>::vararray_s (int elcount)
 : vararray<T> (new /*vararray_internal::*/s_data_t (sizeof T, elcount))
 { }

template <class T>
s_data_t* vararray_s<T>::make_the_empty()
 {
 static dynalloc_reservation<lifetime> life_placement;
 lifetime* life= ::new (life_placement) lifetime();
 static dynalloc_reservation<s_data_t> placement;
 s_data_t* p= new (placement) s_data_t (sizeof(T));
 life->clear();
 life->owned_count ++;
 p->set_lifetime_object(life);
 return p;
 }

template <typename T>
s_data_t* vararray_s<T>::empty()
 {
 static s_data_t* p= make_the_empty();
 return p;
 }


template <class T>
vararray_s<T>::vararray_s (int elcount, int capacity)
 : vararray<T> (new /*vararray_internal::*/s_data_t (sizeof T, elcount, capacity))
 { }

template <class T>
vararray_s<T>::vararray_s (const T* data, int elcount)
 : vararray<T> (new /*vararray_internal::*/s_data_t (sizeof T, elcount, data))
 { }


//////////////////////////////////////////////////

struct snoop_t {
   const /*vararray_internal::*/chdata* h1;
   const /*vararray_internal::*/intermediate* h2;
   const /*vararray_internal::*/data_t* core;
   };



}
ENDWRAP

#endif


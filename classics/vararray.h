// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "classics\data_t.h"
#include "classics\dynalloc_reservation.h"
#include <new>

STARTWRAP
namespace classics {


struct snoop_t;
enum make_alias_t { alias };

//////////////////////////////////////////////////

class intermediate : public cow<data_t>, public can_handle {
   typedef cow<data_t> Base;
public:
   explicit intermediate (data_t* p) : Base(p) {}
   void operator= (data_t* p)  { Base::operator=(p); }
   ~intermediate() {}
   void debug_print() const;
   void debug_snoop (snoop_t&) const;
   data_t* get_data() const { return const_cast<data_t*>(const_object()); }
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

namespace vararray_internal {
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
   bool lazy_dup_core (data_t*&core)
      { return data.get_data()->lazy_dup_core (core); }
   ~nt_base() {}
public:
   CLASSICS_EXPORT void debug_print() const;
   CLASSICS_EXPORT void debug_snoop (snoop_t& results) const  { data.debug_snoop(results); }
   void truncate (int newsize) { get_unique_core().truncate (newsize); }
   CLASSICS_EXPORT void resize (int newsize);
   void reserve (int new_capacity) { get_core().reserve (new_capacity); }
   int elcount() const { return get_core().elcount(); }
   bool is_empty() const { return elcount() == 0; }
   void remove (int pos, int len=1)
      { replace (pos, len, 0,0); }
   void remove_all ()
      { replace (0, elcount(), 0,0); }
   };


}  //end of internal

//////////////////////////////////////////////////

template <typename T>
class vararray : public vararray_internal::nt_base {
public:
   typedef T eltype;
   vararray (const /*vararray_internal::*/chdata& data) : nt_base(data) {}
   vararray (data_t* core) : nt_base (core) {}
   vararray (vararray<T>& other, make_alias_t alias) : nt_base (other,alias) {}
   template <typename Core_T>
    vararray (specify_data_t<Core_T>) : nt_base (
        vararray_internal::shared_empty<Core_T>()
        ) {}
#if 0
   explicit vararray_g (int elcount)
      : vararray<T> (new Core_T (elcount)) { }
   vararray_g (int elcount, int capacity)
      : vararray<T> (new Core_T (elcount, capacity)) { }
   void alias_with (vararray_g<T>& other) { nt_base::alias_with (other); }
   vararray_g (vararray_g<T>& other, make_alias_t alias) : vararray<T>(other,alias) {}
   vararray_g (const T* data, int elcount)
      : vararray<T> (new Core_T (elcount, data)) { }
#endif
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
   void replace_all (const T* data, int datacount)  // like an assignment
      { nt_base::replace (0, elcount(), data, datacount); }
   int append (const T& x)  { int pos= elcount(); replace (pos, 0, &x, 1); return pos; }
   void append (const vararray<T>& other, int frompos, int fromlen)
      { replace (elcount(), 0, other, frompos, fromlen); }
   int sorted_insert (const T& value, int (*compare)(const T&, const T&));
   int sorted_insert (const T& value, int starting, int (*compare)(const T&, const T&));
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

template <typename T>
int vararray<T>::sorted_insert (const T& value, int starting, int (*compare)(const T&, const T&))
 {
 if (starting >= elcount())  starting= elcount()-1;
 else if (starting < 0)  starting= 0;
 for (int loop= starting;  loop >= 0;  loop--)
    if (compare (get_at(loop), value) <= 0)  break;
 replace (loop+1, 0, &value, 1);
 return loop+1;
 }

template <typename ElementT, typename KeyT>
int binary_search (const vararray<ElementT>& A, const KeyT& searchkey, int (*compare)(const ElementT&, const KeyT&))
// returns index of the element, or ~H if not found
// H is where the element should be inserted.  (ones complement used instead of 2's complement to avoid "negative zero")
 {
 int low= -1;
 int high= A.elcount();
 for (;;) {
    int mid= (high+low) >> 1;  // note: >>1 not the same as /2 for negative numbers!
    if (mid == low)  return ~high;
    int compr= compare(A.get_at(mid), searchkey);
    if (compr==0)  return mid;  // found it!
    if (compr > 0) // A[mid] is too high.  Look lower
       high= mid;
    else // must be <0.  A[mid] is too low.  Look higher
       low= mid;
    }
 }

//////////////////////////////////////////////////

template <class T>
class vararray_g : public vararray<T> {
public:
   typedef g_data_t<T> Core_T;
   static Core_T* the_empty;
public:
   vararray_g() : vararray<T> (vararray_internal::shared_empty<Core_T>()) {}
   explicit vararray_g (int elcount)
      : vararray<T> (new Core_T (elcount)) { }
   vararray_g (int elcount, int capacity)
      : vararray<T> (new Core_T (elcount, capacity)) { }
   void alias_with (vararray_g<T>& other) { nt_base::alias_with (other); }
   vararray_g (vararray_g<T>& other, make_alias_t alias) : vararray<T>(other,alias) {}
   vararray_g (const T* data, int elcount)
      : vararray<T> (new Core_T (elcount, data)) { }
   ~vararray_g() {}
   };

//////////////////////////////////////////////////

template <class T>
class vararray_s : public vararray<T> {
   typedef s_data_t<T> Core_T;
   static vararray_internal::s_data_ntbase* the_empty;
public:
   vararray_s() : vararray<T> (vararray_internal::shared_empty<Core_T>()) {}
   explicit vararray_s (int elcount);
   vararray_s (int elcount, int capacity);
   void alias_with (vararray_s<T>& other) { nt_base::alias_with (other); }
   vararray_s (vararray_s<T>& other, make_alias_t alias) : vararray<T>(other,alias) {}
   vararray_s (const T* data, int len);
   ~vararray_s() {}
   };


template <class T>
vararray_s<T>::vararray_s (int elcount)
 : vararray<T> (new Core_T (elcount))
 { }


template <class T>
vararray_s<T>::vararray_s (int elcount, int capacity)
 : vararray<T> (new Core_T (elcount, capacity))
 { }

template <class T>
vararray_s<T>::vararray_s (const T* data, int elcount)
 : vararray<T> (new Core_T (elcount, data))
 { }


//////////////////////////////////////////////////

struct snoop_t {
   const /*vararray_internal::*/chdata* h1;
   const /*vararray_internal::*/intermediate* h2;
   const /*vararray_internal::*/data_t* core;
   };



}
ENDWRAP



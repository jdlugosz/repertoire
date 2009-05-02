// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\copy_semantics.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {


class __declspec(novtable) I_copy_semantics {
public:
   virtual void initialize_elements (void* dest, int count) const =0;
   virtual void initialize_elements (void* dest, const void* src, int count) const =0;
   virtual void copy_elements (void* dest, const void* src, int count) const =0;
   virtual void destroy_elements (void* dest, int count) const =0;
   virtual void move_elements (void* dest, void* src, int count) const =0;
   virtual int elsize() const =0;
   };


class copy_semantics_s : public virtual I_copy_semantics {
public:
   const int Elsize;
   copy_semantics_s (int elsize) : Elsize(elsize) {}
   CLASSICS_EXPORT void initialize_elements (void* dest, int count) const;
   CLASSICS_EXPORT void initialize_elements (void* dest, const void* src, int count) const;
   CLASSICS_EXPORT void copy_elements (void* dest, const void* src, int count) const;
   CLASSICS_EXPORT void move_elements (void* dest, void* src, int count) const;
   void destroy_elements (void* dest, int count) const   { /* does nothing */ }
   int elsize() const { return Elsize; }
   };


template <typename T>
class copy_semantics_g : public virtual I_copy_semantics {
public:
   copy_semantics_g (int elsize) { /* ignored */ } // for consistancy in the templates.
   copy_semantics_g() {}
   void initialize_elements (void* dest, int count) const;
   void initialize_elements (void* dest, const void* src, int count) const;
   void copy_elements (void* dest, const void* src, int count) const;
   void move_elements (void* dest, void* src, int count) const;
   void destroy_elements (void* dest, int count) const;
   virtual int elsize() const { return sizeof(T); }
   };

template <typename T>
void copy_semantics_g<T>::initialize_elements (void* dest_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 for (int loop= 0;  loop < count;  loop++) {
    ::new (dest++) T();  // JMD 2-Sept-2003  Compilers before VC++7.1 initialized even without the () initializer on POD types.  Put in () to keep behavior of known initialization to zero.
    }
 }

template <typename T>
void copy_semantics_g<T>::initialize_elements (void* dest_raw, const void* src_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 const T* src= static_cast<const T*>(src_raw);
 for (int loop= 0;  loop < count;  loop++) {
    ::new (dest++) T (*src++);
    }
 }

template <typename T>
void copy_semantics_g<T>::copy_elements (void* dest_raw, const void* src_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 const T* src= static_cast<const T*>(src_raw);
 if (dest < src) {  // in case they overlap...
    // copy left-to-right
 for (int loop= 0;  loop < count;  loop++) {
    *dest++ = *src++;  //assignment
    }
 }
 else {  // copy right-to-left
    dest += count;
    src += count;
    for (int loop= 0;  loop < count;  loop++) {
       *--dest = *--src;  // assignment
       }
    }
 }
 
template <typename T>
void copy_semantics_g<T>::move_elements (void* dest_raw, void* src_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 T* src= static_cast<T*>(src_raw);
 if (dest < src) {  // in case they overlap...
    // copy left-to-right
 for (int loop= 0;  loop < count;  loop++) {
       ::new (dest++) T (*src);  //duplicate at new position
    src->T::~T();  //destroy the old
    ++src;
    }
 }
 else {  // copy right-to-left
    dest += count;
    src += count;
    for (int loop= 0;  loop < count;  loop++) {
       --src;
       ::new (--dest) T (*src);  //duplicate at new position
       src->T::~T();  //destroy the old
       }
    }
 }

template <typename T>
void copy_semantics_g<T>::destroy_elements (void* dest_raw, int count) const
 {
 T* dest= static_cast<T*>(dest_raw);
 for (int loop= 0;  loop < count;  loop++) {
    dest->T::~T();
    ++dest;
    }
 }


template <typename T>
class copy_semantics;
// figure out which type, _g or _s, to use automatically.

//   class copy_semantics : public copy_traits <T>::semantics {}
// 



}
ENDWRAP


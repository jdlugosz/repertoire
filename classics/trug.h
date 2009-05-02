// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\trug.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\dispose_traits.h"

namespace classics {

template <typename T, typename Storage>  class trule;  // forward declaration

template <bool CanUnown>
struct ownbase;

template <>
struct ownbase<true> {
   bool owned;
   bool is_owned() const  { return owned; }
   };

template <>
struct ownbase<false> { 
   bool is_owned() const  { return true; }
   };

//---------------

template <typename T, typename Storage=T, bool CanUnown=false, typename D=dispose_traits<Storage>, typename Trule= trule<T, Storage> >
class hypothetical_trug : public ownbase <CanUnown> {
protected:
   Storage storage;
   typedef D dispose_t;
public:
   typename T element_type;
   typename Storage storage_type;
   T get_r() const;
   T& get_w();
   T& get_for_outparam();
   bool try_get_for_update (T&);
   void set (const T& value)
      { free(); storage= value; }
   Storage eject();
   // duplicate ...
   void free()
      { if (is_owned()) dispose_t::dispose (storage); storage=dispose_t::null(); }
   bool is_valid() const;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T, typename Storage=T, bool CanUnown=false, typename D=dispose_traits<Storage>, typename Trule= trule<T, Storage> >
class trug;

template <typename T> 
class trug<T*, T*, false> : public hypothetical_trug <T*, T*, false> {
public:
   explicit trug (T* p)  { storage= p; }
   trug() { storage= dispose_t::null(); }
   };


}


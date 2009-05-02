// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\chain.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* This is just getting started.  It's not anywhere near ready for use.
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class chain_base {
public:
   chain_base* Prev;
   chain_base* Next;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class chain_link : public chain_base {
public:
   T Data;
   chain_link (chain_link&, const T&);
   T operator->()  { return Data; }
   void fastfree();
   };


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class chain_head_nt : public chain_base {
protected:
   chain_head_nt() { Prev=Next=this; }
   CLASSICS_EXPORT chain_base* first();
   CLASSICS_EXPORT chain_base* next_after (chain_base*);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class chain : private chain_head_nt {
public:
   ~chain();
   chain_link<T>* first()  { return static_cast<chain_link<T>*>(chain_head_nt::first()); }
   chain_link<T>* last();
   chain_link<T>* next_after (chain_link<T>*p)  { return static_cast<chain_link<T>*>(chain_head_nt::next_after(p)); }
   chain_link<T>* prev_before (chain_link<T>*);
   chain_link<T>* insert_after (chain_link<T>*, const T&);
   void remove (chain_link<T>*);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
chain<T>::~chain()
 {
 for (chain_link<T>* p= first();  p;  p=next_after(p)) {
    p->fastfree();
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class chain_iterator {
public:
   chain_iterator (chain<T>&);
   T operator->();
   bool tofirst();
   bool tolast();
   bool next();
   bool prev();
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


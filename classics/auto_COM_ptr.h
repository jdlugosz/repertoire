// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\auto_COM_ptr.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "classics\common.h"


STARTWRAP
namespace classics {

template <typename T>
class auto_COM_ptr {
   T* p;
   void operator= (const auto_COM_ptr&);  //never defined
public:
   auto_COM_ptr() : p(0) {}
   ~auto_COM_ptr() { reset(); }
   template<typename U>
      auto_COM_ptr (const auto_COM_ptr<U>& other)
         : p(other.get()) { if(p)  p->AddRef(); }
   // repeat myself because...
   template<> auto_COM_ptr (const auto_COM_ptr& other)
      : p(other.get()) { if(p)  p->AddRef(); }
   
   void reset (T* newvalue=0) { if(p) p->Release(); p=newvalue; }
   T* get() const  { return p; }
   T* operator-> () const  { return p; }
   T* relinquish()  { T* temp= p;  p=0;  return temp; }
      // std::auto_ptr calls it release(), here it is relinquish() to avoid confusion with
      // COM's meaning of ->Release().
   operator T** ()  { reset(); return &p; }
      // designed for [out] parameters, unsiutable for [in.out] parameters
   operator bool() const  { return p != 0; }
      // operator bool needed to prevent accidential calling of operator T** which is destructive.
   operator ! () const  { return p == 0; }
      // if I have operator bool, ought to have this one too.
   };

}  //end of namespace
ENDWRAP


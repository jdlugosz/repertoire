// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\dynalloc_reservation.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "classics\common.h"

STARTWRAP
namespace classics {

template <typename T>
class dynalloc_reservation {
public:
   byte buffer[sizeof(T)];
   T& operator*() { return *reinterpret_cast<T*>(buffer); }
   T* operator->() { return reinterpret_cast<T*>(buffer); }
   void free() { reinterpret_cast<T*>(buffer) -> T::~T(); }
   };

}
ENDWRAP

// not in a namespace
template <typename T>
inline
void* operator new (unsigned int, classics::dynalloc_reservation<T>& x)
 {
 return x.buffer;
 }

#if defined ccfg_PLACEMENT_DELETE

template <typename T>
inline
void operator delete (void* p, classics::dynalloc_reservation<T>&)
 {
 // nothing to do at this level.  Just here to satisfy the compiler.
 }
 
#endif

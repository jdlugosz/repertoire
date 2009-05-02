// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\2D_point.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class generic_2D_point {
public:
   T x,y;
   generic_2D_point() : x(T()), y(T()) {}
   generic_2D_point (T x_, T y_) : x(x_), y(y_) {}
   generic_2D_point& operator+= (const generic_2D_point& other)
      { x+=other.x; y+=other.y; return *this; }
   generic_2D_point& operator-= (const generic_2D_point& other)
      { x-=other.x; y-=other.y; return *this; }
   generic_2D_point plusX (generic_2D_point other)
      { return generic_2D_point (x+other.x, y); }
   generic_2D_point plusY (generic_2D_point other)
      { return generic_2D_point (x, y+other.y); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline generic_2D_point<T> operator+ (generic_2D_point<T> a, const generic_2D_point<T>& b)
 {
 return a+=b;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline generic_2D_point<T> operator- (generic_2D_point<T> a, const generic_2D_point<T>& b)
 {
 return a-=b;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline T operator* (const generic_2D_point<T>& a, const generic_2D_point<T>& b)
// inner product
 {
 return a.x*b.x + a.y*b.y;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


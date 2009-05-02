// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\dimensional.h
// Revision: public build 6, shipped on 28-Nov-1999

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {


template <typename T, const T* U>
class dimensional {
protected:
   T Value;
   dimensional (const T& x) : Value(x) {}
public:
   T value() const  { return Value; }
   static dimensional unit();
   dimensional operator+= (const dimensional& other)
      { Value += other.Value;  return *this; }
   dimensional operator-= (const dimensional& other)
      { Value -= other.Value;  return *this; }
   dimensional operator*= (const T& factor)
      { Value *= factor;  return *this; }
   dimensional operator/= (const T& factor)
      { Value /= factor;  return *this; }
   // these do not need to be friends, and should not be.  But the stupid Microsoft compiler
   // won't handle the template unless it's defined inside the class body.
   friend
   inline dimensional<T,U> operator+ (dimensional<T,U> a, dimensional<T,U> b)
    {
    a += b;
    return a;
    }
   friend
   inline dimensional<T,U> operator- (dimensional<T,U> a, dimensional<T,U> b)
    {
    a -= b;
    return a;
    }
   friend
   inline dimensional<T,U> operator* (dimensional<T,U> a, const T& b)
    {
    a *= b;
    return a;
    }
   friend
   inline dimensional<T,U> operator* (const T& b, dimensional<T,U> a)
    {
    a *= b;
    return a;
    }
   friend
   inline dimensional<T,U> operator/ (dimensional<T,U> a, const T& b)
    {
    a /= b;
    return a;
    }
   friend
   inline dimensional<T,U> operator* (const T& b, dimensional<T,U> a)
    {
    return b / a.value();
    }
   };


// ==========

template <typename T, const T* U>
dimensional<T,U> dimensional<T,U>::unit()
 {
 return dimensional<T,U>(*U);
 }


} // end namespace classics
ENDWRAP

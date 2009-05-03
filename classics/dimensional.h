// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\dimensional.h
// Revision: post-public build 9, modified January 15, 2009 or later

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {


template <typename T, const T* U, typename V=T>
class dimensional {
protected:
   T Value;
   dimensional (const T& x) : Value(x) {}
public:
   dimensional () : Value(T()) {}
   T value() const  { return Value; }
   static dimensional unit();
   bool is_negative() const { return Value < 0; }
   bool is_positive() const { return Value > 0; }
   bool is_zero() const { return Value==0; }
   dimensional operator+= (const dimensional& other)
      { Value += other.Value;  return *this; }
   dimensional operator-= (const dimensional& other)
      { Value -= other.Value;  return *this; }
#if 0
   dimensional operator*= (const V& factor)
      { Value= T(Value* factor);  return *this; }
#endif
   template <typename Param>
   dimensional operator*= (const Param& factor)
      { Value= T(Value* factor);  return *this; }

   dimensional operator/= (const V& factor)
      { Value /= factor;  return *this; }
   V operator/ (const dimensional& other) const
      { return V(Value) / V(other.Value);  }
   bool operator== (const dimensional& other) const
      { return Value == other.Value; }
   bool operator!= (const dimensional& other) const
      { return Value != other.Value; }
   bool operator> (const dimensional& other) const
      { return Value < other.Value; }
   bool operator< (const dimensional& other) const
      { return Value < other.Value; }
   bool operator>= (const dimensional& other) const
      { return Value >= other.Value; }
   bool operator<= (const dimensional& other) const
      { return Value <= other.Value; }
   
   // these do not need to be friends, and should not be.  Originally, the stupid Microsoft compiler
   // won't handle the template unless it's defined inside the class body.
   // With newer compilers, this is still here so that the only operators available are the ones
   // that exactly match the T of the generated class.  If defined outside of the class, it will
   // not allow implicit conversions of T in cases like operator*, but will be ambiguous between
   // the actual type passed and the desired type T.
   friend
   inline dimensional<T,U,V> operator+ (dimensional<T,U,V> a, dimensional<T,U,V> b)
    {
    a += b;
    return a;
    }
   friend
   inline dimensional<T,U,V> operator- (dimensional<T,U,V> a, dimensional<T,U,V> b)
    {
    a -= b;
    return a;
    }

   template <typename Param>
   friend
   inline dimensional<T,U,V> operator* (dimensional<T,U,V> a, const Param& b)
    {
    a *= b;
    return a;
    }

   template <typename Param>
   friend
   inline dimensional<T,U,V> operator* (const Param& b, dimensional<T,U,V> a)
    {
    a *= b;
    return a;
    }
   friend
   inline dimensional<T,U,V> operator/ (dimensional<T,U,V> a, const V& b)
    {
    a /= b;
    return a;
    }
   };


// ==========

template <typename T, const T* U, typename V>
dimensional<T,U,V> dimensional<T,U,V>::unit()
 {
 return dimensional<T,U,V>(*U);
 }


} // end namespace classics
ENDWRAP

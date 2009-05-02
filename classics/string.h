// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string.h
// Revision: public build 9, shipped on 18-Oct-2006

// TODO:  Add unit test code, improve class and documentation, 32-bit form.

#pragma once

#include "classics\vararray.h"
//#include "classics\std_forward_declare.h"

STARTWRAP
namespace classics {
   
template <class T>
class generic_string : public vararray_s<T> {
   typedef vararray_s<T> Base;
public:
   CLASSICS_EXPORT generic_string (const T* s);
   CLASSICS_EXPORT generic_string (const T* s, int len);
//   CLASSICS_EXPORT generic_string (const std::basic_string<T>&);
   generic_string() {}  //default constructor
   explicit generic_string (int len) : Base (len,1+len) {}
   generic_string (int len, int capacity) : Base (len,capacity) {}
   generic_string (generic_string<T>& other, make_alias_t alias)
      : Base (other,alias) {}
   CLASSICS_EXPORT const T* c_str() const;
//   CLASSICS_EXPORT operator std::basic_string<T>() const;
   CLASSICS_EXPORT int compare (const generic_string&, bool case_sensitive=true) const;
   CLASSICS_EXPORT generic_string& operator= (const T*);
   CLASSICS_EXPORT generic_string& operator+= (const generic_string& other);
   CLASSICS_EXPORT generic_string& operator+= (const T* other);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
inline
bool operator== (const generic_string<T>& left, const generic_string<T>& right)
 {
 return left.compare(right) == 0;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
inline
bool operator!= (const generic_string<T>& left, const generic_string<T>& right)
 {
 return left.compare(right) != 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
inline
generic_string<T> operator+ (generic_string<T> left, const generic_string<T>& right)
 {
 return left += right;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

typedef generic_string<char> string;
typedef generic_string<wchar_t> wstring;


} // end of classics

ENDWRAP


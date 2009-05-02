// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=handle.h
// Revision: public build 5, shipped on 8-April-1999

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class handle : public const_handle<T> {
public:
   explicit handle (T* p=0) : const_handle<T> (p) {}
   explicit handle (const baro<T>& other) : const_handle<T> (other) {}
   T* operator->() const { return data(); }
   handle& operator= (T* other)
      { const_handle<T>::operator= (other);  return *this; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
} // end of classics


ENDWRAP



// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=handle.h
// Revision: public build 4, shipped on 29-Aug-98

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



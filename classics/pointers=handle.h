// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=handle.h
// Revision: public build 8, shipped on 11-July-2006

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class handle : public const_handle<T> {
public:
   explicit handle (T* p=0) : const_handle<T> (p) {}
   explicit handle (const baro<T>& other) : const_handle<T> (other) {}
   template <typename U>
   handle (const handle<U>& other) : const_handle<T> (other) {}
   T* operator->() const { return data(); }
   T* data() const { return handle_structure<T>::data(); }
   handle& operator= (T* other)
      { const_handle<T>::operator= (other);  return *this; }
   template <typename U>
   handle<T>& operator= (const handle<U>& other)
      { const_handle<T>::operator= (other);  return *this; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
} // end of classics


ENDWRAP



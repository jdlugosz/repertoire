// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=const_handle.h
// Revision: public build 9, shipped on 18-Oct-2006

STARTWRAP
namespace classics {

template <typename T> class const_baro;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class const_handle : public handle_structure<T> {
   typedef handle_structure<T> Base;
public:
   explicit const_handle (const const_baro<T>& other)
      : Base(other) { claim_owned_reference(); }
   explicit const_handle (const T* p=0)
      : Base(const_cast<T*>(p)) { claim_owned_reference(); }
   explicit const_handle (T* p)
      : Base(p) { claim_owned_reference(); }
   const_handle (const const_handle& other)
      : Base(other) { inc_owned_reference(); }
   template <typename U>
   const_handle (const const_handle<U>& other)
      : Base(other) { inc_owned_reference(); }
   ~const_handle()
      { dec_owned_reference(); }
   template <typename U>
   const_handle<T>& operator= (const const_handle<U>& other)
      { assign_owned (other);  return *this; }
   const_handle& operator= (const const_handle& other)
      { assign_owned (other);  return *this; }
   const_handle& operator= (T* other);
   const T* data() const { return Base::data(); }
   const T* operator->() const  { return data(); }
   };

/* ======================================================== */

template <typename T>
const_handle<T>& const_handle<T>::operator= (T* other)
 {
 // make a spare copy of my existing data before I overwrite it
 Base old (*this);
 // grab "other"
 Base::operator= (other);
 claim_owned_reference();
 // now get rid of the old.  I have to grab first then delete the old, in
 // case both old and other refer to the same complete object and
 // the reference count was 1.
 dec_owned_reference(old);
 return *this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP





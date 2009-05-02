// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=cow.h
// Revision: public build 9, shipped on 18-Oct-2006

STARTWRAP
namespace classics {

namespace internal {
CLASSICS_EXPORT int unique_helper (volatile int& trans);
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class cow : public const_handle<T> {
   int make_unique_transaction;  // will replace this with a micro_mutex when that class is available
   void assign_common (const handle_structure<T>&);
public:
   explicit cow (T* p=0) : const_handle<T> (p), make_unique_transaction(0) { }
   template <typename U>
   cow (const cow<U>& other) : const_handle<T> (other), make_unique_transaction(0) {}
   cow (const cow<T>& other) : const_handle<T> (other), make_unique_transaction(0) {}
   T* operator->() const  //the interesting part
      { return data(); }
   T* data() const { const_cast<cow<T>*>(this)->make_unique();  return handle_structure<T>::data(); }
   cow& operator= (T* other)
      {  const_handle<T>::operator= (other);  return *this;  }
   template <typename U>
   cow<T>& operator= (const handle<U>& other)
      { const_handle<T>::operator= (other);  return *this; }
   bool make_unique();  //returns true if it did any work
   static T* clone (const T*);  //explicitly specialize this for non-standard clone interface.
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
__declspec(noinline)
bool cow<T>::make_unique()
 {
 if (is_unique())  return false;

 if (internal::unique_helper (make_unique_transaction) == 0)
    return true;  // the other thread did the work for me.  DON'T REDO IT!

 T* D= clone (const_object());
 lifetime* L= Get_lifetime_object(D);
 L->claim_known_first_owned_reference();
 handle_structure<T> mycopy (L, D);

 atomic_swap (this, &mycopy);
 make_unique_transaction= 0;  // release this cow
 dec_owned_reference (mycopy);
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline
T* cow<T>::clone (const T* original)
 {
 return original->clone();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics


ENDWRAP



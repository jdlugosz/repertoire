// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=cow.h
// Revision: public build 5, shipped on 8-April-1999

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class cow : public const_handle<T> {
public:
   explicit cow (T* p=0) : const_handle<T> (p) {}
   T* operator->() const  //the interesting part
      { make_unique();  return data(); }
   const T* const_object() const { return data(); }  //no duplication
   cow& operator= (T* other)
      { const_handle<T>::operator= (other);  return *this; }
   bool make_unique() const;  //returns true if it did any work
   static T* clone (T*);  //explicitly specialize this for non-standard clone interface.
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
bool cow<T>::make_unique() const
 {
 if (is_unique())  return false;
 T* temp= clone (data());
 const_cast<cow<T>*>(this)->operator= (temp);
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline
T* cow<T>::clone (T* original)
 {
 return original->clone();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
} // end of classics


ENDWRAP



// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=const_baro.h
// Revision: post-public build 9

STARTWRAP
namespace classics {

template <typename T> class handle;  //forward declaration

template <typename T>
class const_baro : public handle_structure<T> {
   typedef handle_structure<T> Base;
   unsigned flags;
   void release() const;
   void claim (unsigned flags) const;
public:
   explicit const_baro (T* p=0)
      : Base(p), flags(0) { inc_unowned_reference(); }
   const_baro (const Base& other)
      : Base(other), flags(0) { inc_unowned_reference(); }
   const_baro (const const_baro& other)
      : Base(other), flags(other.flags) { claim(flags); }
   ~const_baro()
      { release(); }
   const_baro& operator= (const const_baro<T>& other)
      { other.claim(other.flags); release(); flags=other.flags; Base::operator=(other); return *this; }
   const_baro& operator= (const const_handle<T>& other)
      { other.inc_unowned_reference(); release(); flags=0; Base::operator=(other); return *this; }
   const_baro& operator= (T* p);
   void own (bool);  //turn ownership on or off.
   };

template <typename T>
void const_baro<T>::release() const
 {
 if (flags & 1)  dec_owned_reference();
 dec_unowned_reference();
 }

template <typename T>
void const_baro<T>::claim (unsigned flags_) const
 {
 inc_unowned_reference();
 if (flags_ & 1)  claim_owned_reference();
 }

template <typename T>
void const_baro<T>::own (bool state)
 {
 if (flags & 1)  { //already on
    if (!state)  {
       dec_owned_reference();  //release ownership
       flags &= ~1;
       }
    }
 else  { //currently off
    if (state)  {
       claim_owned_reference();  //claim ownership
       flags |= 1;
       }
    }
 }

template <typename T>
const_baro<T>& const_baro<T>::operator= (T* other)
 {
 // make a spare copy of my existing data before I overwrite it
 Base old (*this);
 // grab "other"
 Base::operator= (other);
 inc_unowned_reference();
 // now get rid of the old.  I have to grab first then delete the old, in
 // case both old and other refer to the same complete object and
 // the reference count was 1.
 if (flags & 1)  dec_owned_reference(old);
 dec_unowned_reference(old);
 flags= 0;
 return *this;
 }
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=cow.h
// Revision: public build 8, shipped on 11-July-2006

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class cow : public const_handle<T> {
   void assign_common (const handle_structure<T>&);
public:
   explicit cow (T* p=0) : const_handle<T> (p) {}
   template <typename U>
   cow (const cow<U>& other) : const_handle<T> (other) {}
   cow (const cow<T>& other) : const_handle<T> (other) {}
   T* operator->() const  //the interesting part
      { return data(); }
   T* data() const { make_unique();  return handle_structure<T>::data(); }
   cow& operator= (T* other)
      {
//      const_handle<T>::operator= (other);
      handle_structure<T> rhs(other);
      assign_common (rhs);
      return *this;
      }
   cow& operator= (const cow<T>& other)
      {
      assign_common (other);
      return *this;
      }
   bool make_unique() const;  //returns true if it did any work
   static T* clone (T*);  //explicitly specialize this for non-standard clone interface.
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
bool cow<T>::make_unique() const
 {
 if (is_unique())  return false;

 lifetime* L= check_out_Lifetime();
 T* D= handle_structure<T>::data();
 handle_structure<T> checkout (L, D);
 D= clone (D);
 L= Get_lifetime_object (D);
 L->owned_count= 1;
 L->hold= 0;
 (const_cast<cow<T>*>(this) )->set_data (D);
 set_lifetime_object (L);
 dec_owned_reference (checkout);
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

template <typename T>
inline
void cow<T>::assign_common (const handle_structure<T>& rhs)
 {
 lifetime* L= rhs.check_out_Lifetime();
 T* D= handle_structure<T>::data (rhs);
 if (!L->inc_owned_count_firstp())  L->inc_hold();
 rhs.set_lifetime_object (L);
 lifetime* L2= check_out_Lifetime();  // force this to be done before getting data(), so need the temporary L2.
 handle_structure<T> checkout (L2, handle_structure<T>::data());
 dec_owned_reference (checkout);
 // must set lifetime last, so don't rely on structure copy assignment
 set_data (D);
 set_lifetime_object (L);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline
void const_handle<T>::assign_from_cow (const cow<T>& rhs)
 {
 lifetime* L= rhs.check_out_Lifetime();
 T* D= handle_structure<T>::data (rhs);
 L->inc_owned_count();
 rhs.set_lifetime_object (L);  // check it back in.
 dec_owned_reference();
 set_data (D);
 set_lifetime_object (L);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
inline
handle_structure<T>::handle_structure (const cow<T>& rhs)
 {
 lifetime* L= rhs.check_out_Lifetime();
 T* D= handle_structure<T>::data (rhs);
 L->inc_owned_count();
 rhs.set_lifetime_object (L);  // check it back in.
 set_data (D);
 set_lifetime_object (L);
 }

} // end of classics


ENDWRAP



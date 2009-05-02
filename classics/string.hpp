// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string.hpp
// Revision: public build 4, shipped on 29-Aug-98

/* These are the template bodies for the string class.  Since the instansiations of
   the normal cases are already in the DLL, you don't need to include this.  This
   is available should you need to instansiate some other kind of generic_string.
*/

#define CLASSICS_EXPORT __declspec(dllexport)

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
generic_string<T>::generic_string (const T* s, int len)
 : Base (s, len)
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
const T* generic_string<T>::c_str() const
 {
 data_t& core= get_core();
 const int len= core.elcount();
 core.reserve (1+len);
 T* buf= static_cast<T*>(core.get_buffer());
 buf[len]= '\0';
 return buf;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
int generic_string<T>::compare (const generic_string& other, bool case_sensitive) const
 {
 data_t& core1= get_core();
 const T* const left= static_cast<const T*>(core1.get_buffer());
 const int left_len= core1.elcount();
 data_t& core2= other.get_core();
 const T* const right= static_cast<const T*>(core2.get_buffer());
 const int right_len= core2.elcount();
 // the preliminaries out of the way, do the actual string compare.  I do it
 // this way instead of just calling strcmp() so I don't need to produce
 // nul-terminated strings.
 const int len= left_len < right_len ? left_len : right_len;  //the shorter length
 const int result= compare_ (left, right, len, case_sensitive);
 if (result == 0) {
    // strings equal up to the length of the shorter.  The shorter one is "less".
    return left_len - right_len;
    }
 else  return result;   
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
generic_string<T>& generic_string<T>::operator= (const T* s)
 {
 const int len= len_(s);
 T* outbuf= static_cast<T*>(get_unique_core().prep_result (len, 1+len));
 memcpy (outbuf, s, len*sizeof(T));
 return *this;
 }
 

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
generic_string<T>& generic_string<T>::operator+= (const generic_string<T>& other)
 {
 append (other, 0, other.elcount());
 return *this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <class T>
generic_string<T>::generic_string (const T* s)
 : Base (s, len_(s))
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
#if 0

template <typename T>
generic_string<T>::generic_string (const std::basic_string<T>& input)
 : Base (input.data(), input.length())
 { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
generic_string<T>::operator std::basic_string<T>() const
 {
 const T* data= get_buffer();
 int size= elcount();
 return std::basic_string<T> (data, size);
 }
#endif

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end classics
ENDWRAP



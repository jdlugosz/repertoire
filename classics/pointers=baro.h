// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=baro.h
// Revision: public build 4, shipped on 29-Aug-98

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class baro : public const_baro<T> {
   typedef const_baro<T> Base;
public:
   explicit baro (T* p=0) : const_baro<T> (p) {}
   baro (const baro<T>& other) : Base(other) {}
   baro (const handle<T>& other) : Base(other) {}
   baro& operator= (const baro& other)   { Base::operator=(other); return *this; }
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
} // end of classics


ENDWRAP


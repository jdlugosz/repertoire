// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\pointers=baro.h
// Revision: public build 9, shipped on 18-Oct-2006

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
   baro& operator= (T* p) { Base::operator=(p); return *this; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
} // end of classics


ENDWRAP


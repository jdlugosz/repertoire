// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\point_ios.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\point_ios.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename CharT>
std::basic_ostream<CharT>& operator<< (std::basic_ostream<CharT>& o, const point& val)
 {
 const long saveflags= o.flags();
 o << std::dec;  //format numbers as decimal
 o << "(" << val.x << ", " << val.y << ")";
 o.flags (saveflags);  //restore original settings
 return o;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template  std::ostream& operator<< (std::ostream&, const point&);
template  std::wostream& operator<< (std::wostream&, const point&);

} // end of tomahawk
ENDWRAP


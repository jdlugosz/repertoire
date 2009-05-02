// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\point_ios.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "classics\2D_point.h"
#include "classics\string_ios.h"

STARTWRAP
namespace classics {

template <typename CharT, typename ElType>
std::basic_ostream<CharT>& operator<< (std::basic_ostream<CharT>& o, const generic_2D_point<ElType>& val)
 {
 const long saveflags= o.flags();
 o << std::dec;  //format numbers as decimal
 o << "(" << val.x << ", " << val.y << ")";
 o.flags (saveflags);  //restore original settings
 return o;
 }

} // end of classics
ENDWRAP


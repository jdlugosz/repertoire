// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\point_ios.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "tomahawk\base.h"
#include "classics\string_ios.h"

STARTWRAP
namespace tomahawk {


template <typename CharT>
TOMAHAWK_EXPORT std::basic_ostream<CharT>& operator<< (std::basic_ostream<CharT>&, const point&);


} // end of tomahawk
ENDWRAP


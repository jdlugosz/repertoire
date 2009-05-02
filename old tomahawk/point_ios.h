// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\point_ios.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "tomahawk\base.h"
#include "classics\string_ios.h"

STARTWRAP
namespace tomahawk {


template <typename CharT>
TOMAHAWK_EXPORT std::basic_ostream<CharT>& operator<< (std::basic_ostream<CharT>&, const point&);


} // end of tomahawk
ENDWRAP


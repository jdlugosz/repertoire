// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\point_ios.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "tomahawk\base.h"
#include "classics\string_ios.h"

STARTWRAP
namespace tomahawk {


template <typename CharT>
TOMAHAWK_EXPORT std::basic_ostream<CharT>& operator<< (std::basic_ostream<CharT>&, const point&);


} // end of tomahawk
ENDWRAP


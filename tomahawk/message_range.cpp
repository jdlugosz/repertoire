// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_range.h"

namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range& message_range::operator<< (unsigned item)
 {
 if (item < low)  low= item;
 if (item > high)  high= item;
 return *this;
 }

}


// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

namespace tomahawk {

class message_range {
public:
   unsigned low;
   unsigned high;
   message_range() : low(~0), high(0) {}
   TOMAHAWK_EXPORT message_range& operator<< (unsigned item);
   bool contains (unsigned x) const { return x >= low && x <= high; }
   };

}



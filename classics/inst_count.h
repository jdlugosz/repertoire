// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\inst_count.h
// Revision: public build 6, shipped on 28-Nov-1999
#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\atomic_counter.h"

namespace classics {

CLASSICS_EXPORT void add_inst (const void*, int N, int newcount);
CLASSICS_EXPORT void remove_inst (const void*, int N, int newcount);

template <int N>
class inst_tracker {
protected:
   inst_tracker() { add_inst (this, N, ++inst_count); }
   inst_tracker (const inst_tracker&) { add_inst (this, N, ++inst_count); }
   ~inst_tracker() { remove_inst (this, N, --inst_count); }
public:
   static const char* name;
   CLASSICS_EXPORT static atomic_counter<int> inst_count;
   };

template <int N>
const char* inst_tracker<N>::name= 0;


}


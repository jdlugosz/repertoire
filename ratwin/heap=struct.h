// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\heap=struct.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\base.h"

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace heap {

using types::Heap;

enum alloc_flags_t {
   NO_SERIALIZE= 1,
   GENERATE_EXCEPTIONS= 4,
   ZERO_MEMORY= 8,
   CREATE_ENABLE_EXECUTE= 0x00040000
   };

}}
ENDWRAP


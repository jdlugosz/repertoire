// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\ChildidOrHMENU.h
// Revision: post - public build 5

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

class ChildidOrHMENU {
   arg::arg32 fourbytes;
public:
   ChildidOrHMENU() : fourbytes(0) {}
   ChildidOrHMENU (unsigned short Childid) : fourbytes( reinterpret_cast<arg::arg32>( unsigned (Childid) ) ) {}
   ChildidOrHMENU (types::HMENU hmenu) : fourbytes( reinterpret_cast<arg::arg32>( hmenu ) ) {}
   operator arg::arg32() { return fourbytes; }
   };
   
}


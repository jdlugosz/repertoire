// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\command_object.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#include "classics\common.h"

STARTWRAP
namespace classics {

class abstract_command_object {
public:
   virtual ~abstract_command_object() {}
   virtual void operator()() =0;
   };

} // end of classics
ENDWRAP


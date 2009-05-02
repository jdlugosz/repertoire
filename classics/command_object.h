// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\command_object.h
// Revision: public build 6, shipped on 28-Nov-1999

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


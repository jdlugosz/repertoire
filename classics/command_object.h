// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\command_object.h
// Revision: public build 4, shipped on 29-Aug-98

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


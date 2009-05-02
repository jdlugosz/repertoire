// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\command_object.h
// Revision: public build 8, shipped on 11-July-2006

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


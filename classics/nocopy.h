// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\nocopy.h
// Revision: fresh

#pragma once

#include "classics\common.h"


STARTWRAP
namespace classics {

class nocopy {
   // copy things are private and never defined.
   // In C++0x, you will be able to write "=delete" here.
   nocopy (nocopy&) /* = delete */ ;
   void operator= (nocopy&) /* = delete */ ;
public:
   nocopy() {}  // but this is OK.
   };

}  //end of namespace

ENDWRAP


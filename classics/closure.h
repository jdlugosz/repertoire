// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\closure.h
// Revision: public build 9, shipped on 18-Oct-2006

/*  Each compiler or platform may have different implementations of this template.  Instead of a maze of
   conditional compilation, each flavor has its own file.  This header just determines which one to use.
*/

#pragma once

#if defined(_MSC_VER) && defined(_M_IX86)
// Microsoft compiler on PC

   #if defined(_MANAGED)
      #error Closure class not supported in /clr mode at the moment.
   #endif

   #if (_MSC_VER < 1310)
      #include "closure-=-old.h"
   #else
      #include "closure-=-MSonPC.h"
   #endif

#elif 0
  // add more cases with #elif directives.

#else
  #error This module has not been prepared for this platform.
#endif


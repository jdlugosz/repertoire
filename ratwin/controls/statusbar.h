// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\statusbar.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if !defined RATWIN_Controls_STATUSBAR_INCLUDED
#define RATWIN_Controls_STATUSBAR_INCLUDED

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace controls {

const char STATUSCLASSNAME[]= "msctls_statusbar32";

enum messages {
   SB_SETPARTS=         0x404,
   SB_GETPARTS=         0x406,
   SB_GETBORDERS=       0x407,
   SB_SETMINHEIGHT=     0x408,
   SB_SIMPLE=           0x409,
   SB_GETRECT=          0x410,
   SB_ISSIMPLE=         0x414,
   SB_SETTEXT=          0x401,
   SB_GETTEXT=          0x402,
   SB_GETTEXTLENGTH=    0x403,
   };

enum styles {
   SBT_OWNERDRAW=       0x1000,
   SBT_NOBORDERS=       0x0100,
   SBT_POPOUT=          0x0200,
   SBT_RTLREADING=      0x0400,
   };

}

}
ENDWRAP
#endif


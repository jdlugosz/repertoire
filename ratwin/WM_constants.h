// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\WM_constants.h
// Revision: public build 6, shipped on 28-Nov-1999

// I'll make a complete list using an automated utility, AFTER I decide
// exactly how I'll package this.  One long list is contrary to RATWIN's
// general philosophy.  I should categorize them somehow.

#pragma once
#if !defined RATWIN_WM_constants_INCLUDED
#define RATWIN_WM_constants_INCLUDED

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

namespace WM_constants {

enum messages {
   WM_COMMAND=         0x0111,
   WM_CREATE=          0x0001,
   WM_DESTROY =        0x0002,
   WM_NCDESTROY=       0x0082,
   WM_DRAWITEM=        0x002B,
   WM_INITDIALOG=      0x0110,
   WM_MOVE=            0x0003,
   WM_PAINT=           0x000F,
   WM_SIZE=            0x0005,
   WM_QUERYENDSESSION= 0x0011,
   WM_QUERYOPEN=       0x0013,
   WM_MOUSEFIRST=      0x0200,     //for bracketing message range
   WM_MOUSEMOVE=       0x0200,
   WM_LBUTTONDOWN=     0x0201,
   WM_LBUTTONUP=       0x0202,
   WM_LBUTTONDBLCLK=   0x0203,
   WM_RBUTTONDOWN=     0x0204,
   WM_RBUTTONUP=       0x0205,
   WM_RBUTTONDBLCLK=   0x0206,
   WM_MBUTTONDOWN=     0x0207,
   WM_MBUTTONUP=       0x0208,
   WM_MBUTTONDBLCLK=   0x0209,
   WM_MOUSELAST=       0x0209,    //for bracketing message range
   WM_KEYFIRST=        0x0100,    //for bracketing message range
   WM_KEYDOWN=         0x0100,
   WM_KEYUP=           0x0101,
   WM_CHAR=            0x0102,
   WM_DEADCHAR=        0x0103,
   WM_SYSKEYDOWN=      0x0104,
   WM_SYSKEYUP=        0x0105,
   WM_SYSCHAR=         0x0106,
   WM_SYSDEADCHAR=     0x0107,
   WM_KEYLAST=         0x0108,    //for bracketing message range
   WM_ACTIVATE=        0x0006,
   WM_ENABLE=          0x000A,
   WM_CLOSE=           0x0010,
   WM_QUIT=            0x0012,
   WM_HSCROLL= 0x0114,
   WM_VSCROLL= 0x0115,
   WM_USER=            0x0400,
   WM_TIMER=           0x0113,
   WM_NCHITTEST= 0x0084,
   WM_SETCURSOR= 0x0020,
   WM_NOTIFY= 0x004E,
   };

struct NMHDR {   // associated with WM_NOTIFY
   types::HWND sender;
   unsigned sender_id;
   unsigned code;
   enum codes {
      TCN_FIRST= (0U-550U),  // tab control
      TCN_SELCHANGE= TCN_FIRST-1,
      TCN_SELCHANGING= TCN_FIRST-2,
      };
   };

} //end WM_constants

}
ENDWRAP

#endif


// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\WM_constants.h
// Revision: post PB6

// I'll make a complete list using an automated utility, AFTER I decide
// exactly how I'll package this.  One long list is contrary to RATWIN's
// general philosophy.  I should categorize them somehow.

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace WM_constants {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::WM_constants)
   WM_CREATE WM_DESTROY WM_MOVE WM_SIZE WM_ACTIVATE WM_ENABLE WM_PAINT WM_CLOSE
   WM_QUERYENDSESSION WM_QUIT WM_QUERYOPEN WM_SETCURSOR WM_DRAWITEM WM_NOTIFY
   WM_NCDESTROY WM_NCHITTEST WM_KEYFIRST WM_KEYDOWN WM_KEYUP WM_CHAR WM_DEADCHAR
   WM_SYSKEYDOWN WM_SYSKEYUP WM_SYSCHAR WM_SYSDEADCHAR WM_KEYLAST WM_INITDIALOG
   WM_COMMAND WM_TIMER WM_HSCROLL WM_VSCROLL WM_MOUSEFIRST WM_MOUSEMOVE
   WM_LBUTTONDOWN WM_LBUTTONUP WM_LBUTTONDBLCLK WM_RBUTTONDOWN WM_RBUTTONUP
   WM_RBUTTONDBLCLK WM_MBUTTONDOWN WM_MBUTTONUP WM_MBUTTONDBLCLK WM_MOUSELAST
   WM_USER WM_INITMENUPOPUP WM_INITMENU WM_ERASEBKGND WM_CTLCOLORSTATIC

*/
// ## BEGIN MacroCloak Generated Code
#if defined (WM_CREATE)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef WM_CREATE
#undef WM_DESTROY
#undef WM_MOVE
#undef WM_SIZE
#undef WM_ACTIVATE
#undef WM_ENABLE
#undef WM_PAINT
#undef WM_CLOSE
#undef WM_QUERYENDSESSION
#undef WM_QUIT
#undef WM_QUERYOPEN
#undef WM_SETCURSOR
#undef WM_DRAWITEM
#undef WM_NOTIFY
#undef WM_NCDESTROY
#undef WM_NCHITTEST
#undef WM_KEYFIRST
#undef WM_KEYDOWN
#undef WM_KEYUP
#undef WM_CHAR
#undef WM_DEADCHAR
#undef WM_SYSKEYDOWN
#undef WM_SYSKEYUP
#undef WM_SYSCHAR
#undef WM_SYSDEADCHAR
#undef WM_KEYLAST
#undef WM_INITDIALOG
#undef WM_COMMAND
#undef WM_TIMER
#undef WM_HSCROLL
#undef WM_VSCROLL
#undef WM_MOUSEFIRST
#undef WM_MOUSEMOVE
#undef WM_LBUTTONDOWN
#undef WM_LBUTTONUP
#undef WM_LBUTTONDBLCLK
#undef WM_RBUTTONDOWN
#undef WM_RBUTTONUP
#undef WM_RBUTTONDBLCLK
#undef WM_MBUTTONDOWN
#undef WM_MBUTTONUP
#undef WM_MBUTTONDBLCLK
#undef WM_MOUSELAST
#undef WM_USER
#endif
// ## END Generated Code

enum messages {
   WM_CREATE=              0x0001,
   WM_DESTROY=             0x0002,
   WM_MOVE=                0x0003,
   WM_SIZE=                0x0005,
   WM_ACTIVATE=            0x0006,
   WM_ENABLE=              0x000A,
   WM_PAINT=               0x000F,
   WM_CLOSE=               0x0010,
   WM_QUERYENDSESSION=     0x0011,
   WM_QUIT=                0x0012,
   WM_QUERYOPEN=           0x0013,
   WM_ERASEBKGND=          0x0014,
   WM_SETCURSOR=           0x0020,
   WM_DRAWITEM=            0x002B,
   WM_NOTIFY=              0x004E,
   WM_NCDESTROY=           0x0082,
   WM_NCHITTEST=           0x0084,
   WM_KEYFIRST=            0x0100,    //for bracketing message range
   WM_KEYDOWN=             0x0100,
   WM_KEYUP=               0x0101,
   WM_CHAR=                0x0102,
   WM_DEADCHAR=            0x0103,
   WM_SYSKEYDOWN=          0x0104,
   WM_SYSKEYUP=            0x0105,
   WM_SYSCHAR=             0x0106,
   WM_SYSDEADCHAR=         0x0107,
   WM_KEYLAST=             0x0108,    //for bracketing message range
   WM_INITDIALOG=          0x0110,
   WM_COMMAND=             0x0111,
   WM_TIMER=               0x0113,
   WM_HSCROLL=             0x0114,
   WM_VSCROLL=             0x0115,
   WM_INITMENU=            0x0116,
   WM_INITMENUPOPUP=       0x0117,
   WM_CTLCOLORSTATIC=      0x0138,
   WM_MOUSEFIRST=          0x0200,     //for bracketing message range
   WM_MOUSEMOVE=           0x0200,
   WM_LBUTTONDOWN=         0x0201,
   WM_LBUTTONUP=           0x0202,
   WM_LBUTTONDBLCLK=       0x0203,
   WM_RBUTTONDOWN=         0x0204,
   WM_RBUTTONUP=           0x0205,
   WM_RBUTTONDBLCLK=       0x0206,
   WM_MBUTTONDOWN=         0x0207,
   WM_MBUTTONUP=           0x0208,
   WM_MBUTTONDBLCLK=       0x0209,
   WM_MOUSELAST=           0x0209,    //for bracketing message range
   WM_USER=                0x0400,
   };

struct NMHDR {   // associated with WM_NOTIFY
   types::HWND sender;
   unsigned sender_id;
   unsigned code;
#if 0   // belongs with tab control file
   enum codes {
      TCN_FIRST= (0U-550U),  // tab control
      TCN_SELCHANGE= TCN_FIRST-1,
      TCN_SELCHANGING= TCN_FIRST-2,
      };
#endif
   };

} //end WM_constants
}
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::WM_constants::WM_CREATE;
using ratwin::WM_constants::WM_DESTROY;
using ratwin::WM_constants::WM_MOVE;
using ratwin::WM_constants::WM_SIZE;
using ratwin::WM_constants::WM_ACTIVATE;
using ratwin::WM_constants::WM_ENABLE;
using ratwin::WM_constants::WM_PAINT;
using ratwin::WM_constants::WM_CLOSE;
using ratwin::WM_constants::WM_QUERYENDSESSION;
using ratwin::WM_constants::WM_QUIT;
using ratwin::WM_constants::WM_QUERYOPEN;
using ratwin::WM_constants::WM_SETCURSOR;
using ratwin::WM_constants::WM_DRAWITEM;
using ratwin::WM_constants::WM_NOTIFY;
using ratwin::WM_constants::WM_NCDESTROY;
using ratwin::WM_constants::WM_NCHITTEST;
using ratwin::WM_constants::WM_KEYFIRST;
using ratwin::WM_constants::WM_KEYDOWN;
using ratwin::WM_constants::WM_KEYUP;
using ratwin::WM_constants::WM_CHAR;
using ratwin::WM_constants::WM_DEADCHAR;
using ratwin::WM_constants::WM_SYSKEYDOWN;
using ratwin::WM_constants::WM_SYSKEYUP;
using ratwin::WM_constants::WM_SYSCHAR;
using ratwin::WM_constants::WM_SYSDEADCHAR;
using ratwin::WM_constants::WM_KEYLAST;
using ratwin::WM_constants::WM_INITDIALOG;
using ratwin::WM_constants::WM_COMMAND;
using ratwin::WM_constants::WM_TIMER;
using ratwin::WM_constants::WM_HSCROLL;
using ratwin::WM_constants::WM_VSCROLL;
using ratwin::WM_constants::WM_MOUSEFIRST;
using ratwin::WM_constants::WM_MOUSEMOVE;
using ratwin::WM_constants::WM_LBUTTONDOWN;
using ratwin::WM_constants::WM_LBUTTONUP;
using ratwin::WM_constants::WM_LBUTTONDBLCLK;
using ratwin::WM_constants::WM_RBUTTONDOWN;
using ratwin::WM_constants::WM_RBUTTONUP;
using ratwin::WM_constants::WM_RBUTTONDBLCLK;
using ratwin::WM_constants::WM_MBUTTONDOWN;
using ratwin::WM_constants::WM_MBUTTONUP;
using ratwin::WM_constants::WM_MBUTTONDBLCLK;
using ratwin::WM_constants::WM_MOUSELAST;
using ratwin::WM_constants::WM_USER;
#endif
// ## END Generated Code


// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\dialog=struct.h
// Revision: 

#pragma once
#include "ratwin\base.h"
#include "ratwin\NumOrName.h"

STARTWRAP
namespace ratwin {
namespace dialog {

enum command_id {
   IDOK= 1, IDCANCEL, IDABORT, IDRETRY, IDIGNORE, IDYES, IDNO, IDCLOSE, IDHELP 
   };

enum user_button_notification_codes {
   BN_CLICKED= 0,
   BN_PAINT,
   BN_PUSHED,
   BN_HILITE= BN_PUSHED,
   BN_UNPUSHED,
   BN_UNHILITE= BN_UNPUSHED,
   BN_DISABLE,
   BN_DOUBLECLICKED,
   BN_DBLCLK= BN_DOUBLECLICKED,
   BN_SETFOCUS,
   BN_KILLFOCUS
   };

typedef int (__stdcall* DLGPROC) (types::HWND, unsigned, unsigned, ulong);

#pragma pack (push, 2)
struct DLGTEMPLATE {
   unsigned style;
   unsigned dwExtendedStyle;
   unsigned short cdit;
   short x;
   short y;
   short cx;
   short cy;
   };
#pragma pack (pop)

} //end dialog
}
ENDWRAP


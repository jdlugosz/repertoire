// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\dialog=struct.h
// Revision: 

#pragma once
#include "ratwin\base.h"
#include "ratwin\NumOrName.h"

STARTWRAP
namespace ratwin {
namespace dialog {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::dialog)
   IDOK IDCANCEL IDABORT IDRETRY IDIGNORE IDYES IDNO IDCLOSE IDHELP
   DWL_MSGRESULT  DWL_DLGPROC DWL_USER
   BN_CLICKED BN_PAINT BN_PUSHED  BN_HILITE BN_UNPUSHED BN_UNHILITE BN_DISABLE BN_DOUBLECLICKED BN_DBLCLK BN_SETFOCUS BN_KILLFOCUS
   
*/
// ## BEGIN MacroCloak Generated Code
#if defined (IDOK)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef IDOK
#undef IDCANCEL
#undef IDABORT
#undef IDRETRY
#undef IDIGNORE
#undef IDYES
#undef IDNO
#undef IDCLOSE
#undef IDHELP
#undef DWL_MSGRESULT
#undef DWL_DLGPROC
#undef DWL_USER
#undef BN_CLICKED
#undef BN_PAINT
#undef BN_PUSHED
#undef BN_HILITE
#undef BN_UNPUSHED
#undef BN_UNHILITE
#undef BN_DISABLE
#undef BN_DOUBLECLICKED
#undef BN_DBLCLK
#undef BN_SETFOCUS
#undef BN_KILLFOCUS
#endif
// ## END Generated Code
enum command_id {
   IDOK= 1, IDCANCEL, IDABORT, IDRETRY, IDIGNORE, IDYES, IDNO, IDCLOSE, IDHELP 
   };

enum DWL_offsets {
   DWL_MSGRESULT=   0,
   DWL_DLGPROC=     4,
   DWL_USER=        8
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
// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::dialog::IDOK;
using ratwin::dialog::IDCANCEL;
using ratwin::dialog::IDABORT;
using ratwin::dialog::IDRETRY;
using ratwin::dialog::IDIGNORE;
using ratwin::dialog::IDYES;
using ratwin::dialog::IDNO;
using ratwin::dialog::IDCLOSE;
using ratwin::dialog::IDHELP;
using ratwin::dialog::DWL_MSGRESULT;
using ratwin::dialog::DWL_DLGPROC;
using ratwin::dialog::DWL_USER;
using ratwin::dialog::BN_CLICKED;
using ratwin::dialog::BN_PAINT;
using ratwin::dialog::BN_PUSHED;
using ratwin::dialog::BN_HILITE;
using ratwin::dialog::BN_UNPUSHED;
using ratwin::dialog::BN_UNHILITE;
using ratwin::dialog::BN_DISABLE;
using ratwin::dialog::BN_DOUBLECLICKED;
using ratwin::dialog::BN_DBLCLK;
using ratwin::dialog::BN_SETFOCUS;
using ratwin::dialog::BN_KILLFOCUS;
#endif
// ## END Generated Code


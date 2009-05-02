// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\text.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_Controls_TEXT_INCLUDED
#define RATWIN_Controls_TEXT_INCLUDED
// covers both regular and rich text controls

#include "ratwin\controls\basic.h"

STARTWRAP
namespace ratwin {

namespace controls {


enum messages {
   EM_GETSEL= 0x00B0,
   EM_SETSEL,
   EM_GETRECT,
   EM_SETRECT,
   EM_SETRECTNP,
   EM_SCROLL,
   EM_LINESCROLL,
   EM_SCROLLCARET,
   EM_GETMODIFY,
   EM_SETMODIFY,
   EM_GETLINECOUNT,
   EM_LINEINDEX,
   EM_SETHANDLE,
   EM_GETHANDLE,
   EM_GETTHUMB,
   
   EM_LINELENGTH= 0x00C1,
   EM_REPLACESEL,
   EM_GETLINE= 0x00C4,
   EM_SETLIMITTEXT,
   EM_CANUNDO,
   EM_UNDO,
   EM_FMTLINES,
   EM_LINEFROMCHAR,
   
   EM_SETTABSTOPS= 0x00CB,
   EM_SETPASSWORDCHAR,
   EM_EMPTYUNDOBUFFER,
   EM_GETFIRSTVISIBLELINE,
   EM_SETREADONLY,
   EM_SETWORDBREAKPROC,
   EM_GETWORDBREAKPROC,
   EM_GETPASSWORDCHAR,
   EM_SETMARGINS,
   EM_GETMARGINS,
   EM_GETLIMITTEXT,
   EM_POSFROMCHAR,
   EM_CHARFROMPOS,
   WM_CONTEXTMENU= 0x007B,
   WM_PRINTCLIENT= 0x0318,
   EM_CANPASTE= 1074,
   EM_DISPLAYBAND,
   EM_EXGETSEL,
   EM_EXLIMITTEXT,
   EM_EXLINEFROMCHAR,
   EM_EXSETSEL,
   EM_FINDTEXT,
   EM_FORMATRANGE,
   EM_GETCHARFORMAT,
   EM_GETEVENTMASK,
   EM_GETOLEINTERFACE,
   EM_GETPARAFORMAT,
   EM_GETSELTEXT,
   EM_HIDESELECTION,
   EM_PASTESPECIAL,
   EM_REQUESTRESIZE,
   EM_SELECTIONTYPE,
   EM_SETBKGNDCOLOR,
   EM_SETCHARFORMAT,
   EM_SETEVENTMASK,
   EM_SETOLECALLBACK,
   EM_SETPARAFORMAT,
   EM_SETTARGETDEVICE,
   EM_STREAMIN,
   EM_STREAMOUT,
   EM_GETTEXTRANGE,
   EM_FINDWORDBREAK,
   EM_SETOPTIONS,
   EM_GETOPTIONS,
   EM_FINDTEXTEX,
   EM_GETWORDBREAKPROCEX,
   EM_SETWORDBREAKPROCEX,
   EM_SETUNDOLIMIT,
   
   EM_REDO= 0x400 + 84,
   EM_CANREDO,
   EM_GETUNDONAME,
   EM_GETREDONAME,
   EM_STOPGROUPTYPING,
   EM_SETTEXTMODE,
   EM_GETTEXTMODE
   };


struct CHARFORMAT {
   unsigned cbSize;
   ulong mask;
   ulong effects;
   long yHeight;
   long yOffset;
   ulong crTextColor;  //COLORREF
   byte bCharSet;
   byte bPitchAndFamily;
   char szFaceName [32];
   };


enum masks {
   CFM_BOLD= 0x00000001,
   CFM_ITALIC= 0x00000002,
   CFM_UNDERLINE= 0x00000004,
   CFM_STRIKEOUT= 0x00000008,
   CFM_PROTECTED= 0x00000010,
   CFM_LINK= 0x00000020,
   CFM_SIZE= 0x80000000,
   CFM_COLOR= 0x40000000,
   CFM_FACE= 0x20000000,
   CFM_OFFSET= 0x10000000,
   CFM_CHARSET= 0x08000000
   };

enum effects {
   CFE_BOLD= 0x0001,
   CFE_ITALIC= 0x0002,
   CFE_UNDERLINE= 0x0004,
   CFE_STRIKEOUT= 0x0008,
   CFE_PROTECTED= 0x0010,
   CFE_LINK= 0x0020,
   CFE_AUTOCOLOR= 0x40000000
   };
   
enum set_format_flags {
   SCF_SELECTION= 0x0001,
   SCF_WORD= 0x0002,
   SCF_DEFAULT= 0x0000,
   SCF_ALL= 0x0004,
   };

class char_format : public CHARFORMAT {
public:
   char_format() { cbSize= sizeof(CHARFORMAT); }
   };

}}
ENDWRAP
#endif


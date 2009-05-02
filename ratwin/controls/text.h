// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\text.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
// covers both regular and rich text controls

#include "ratwin\controls\basic=struct.h"
#include "ratwin\color=struct.h"

STARTWRAP
namespace ratwin {
namespace controls {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::controls)
   EM_GETSEL EM_SETSEL EM_GETRECT  EM_SETRECT EM_SETRECTNP  EM_SCROLL EM_LINESCROLL EM_SCROLLCARET
   EM_GETMODIFY EM_SETMODIFY EM_GETLINECOUNT EM_LINEINDEX EM_SETHANDLE EM_GETHANDLE EM_GETTHUMB
   EM_LINELENGTH EM_REPLACESEL EM_GETLINE EM_SETLIMITTEXT EM_CANUNDO EM_UNDO EM_FMTLINES EM_LINEFROMCHAR
   EM_SETTABSTOPS  EM_SETPASSWORDCHAR    EM_EMPTYUNDOBUFFER EM_GETFIRSTVISIBLELINE EM_SETREADONLY
   EM_SETWORDBREAKPROC EM_GETWORDBREAKPROC EM_GETPASSWORDCHAR EM_SETMARGINS EM_GETMARGINS
   EM_GETLIMITTEXT EM_POSFROMCHAR EM_CHARFROMPOS WM_CONTEXTMENU WM_PRINTCLIENT EM_CANPASTE
   EM_DISPLAYBAND EM_EXGETSEL EM_EXLIMITTEXT EM_EXLINEFROMCHAR EM_EXSETSEL EM_FINDTEXT EM_FORMATRANGE
   EM_GETCHARFORMAT EM_GETEVENTMASK EM_GETOLEINTERFACE EM_GETPARAFORMAT EM_GETSELTEXT EM_HIDESELECTION
   EM_PASTESPECIAL EM_REQUESTRESIZE EM_SELECTIONTYPE EM_SETBKGNDCOLOR EM_SETCHARFORMAT EM_SETEVENTMASK
   EM_SETOLECALLBACK EM_SETPARAFORMAT   EM_SETTARGETDEVICE  EM_STREAMIN EM_STREAMOUT EM_GETTEXTRANGE
   EM_FINDWORDBREAK EM_SETOPTIONS EM_GETOPTIONS EM_FINDTEXTEX EM_GETWORDBREAKPROCEX EM_SETWORDBREAKPROCEX
   EM_SETUNDOLIMIT EM_REDO  EM_CANREDO  EM_GETUNDONAME EM_GETREDONAME    EM_STOPGROUPTYPING EM_SETTEXTMODE
   EM_GETTEXTMODE CHARFORMAT
   CFM_BOLD CFM_ITALIC CFM_UNDERLINE CFM_STRIKEOUT CFM_PROTECTED CFM_LINK CFM_SIZE CFM_COLOR
   CFM_FACE CFM_OFFSET CFM_CHARSET
   CFE_BOLD CFE_ITALIC CFE_UNDERLINE CFE_STRIKEOUT CFE_PROTECTED CFE_LINK CFE_AUTOCOLOR
   SCF_SELECTION SCF_WORD SCF_DEFAULT SCF_ALL
   ES_LEFT ES_CENTER ES_RIGHT ES_MULTILINE ES_UPPERCASE ES_LOWERCASE ES_PASSWORD ES_AUTOVSCROLL  
   ES_AUTOHSCROLL ES_NOHIDESEL ES_OEMCONVERT    ES_READONLY ES_WANTRETURN ES_NUMBER
   ES_SAVESEL ES_SUNKEN ES_DISABLENOSCROLL ES_SELECTIONBAR ES_NOOLEDRAGDROP
   ENM_NONE ENM_CHANGE ENM_UPDATE ENM_SCROLL ENM_KEYEVENTS ENM_MOUSEEVENTS ENM_REQUESTRESIZE
   ENM_SELCHANGE ENM_DROPFILES ENM_PROTECTED ENM_CORRECTTEXT ENM_SCROLLEVENTS ENM_DRAGDROPDONE
   EN_MSGFILTER EN_REQUESTRESIZE  EN_SELCHANGE  EN_DROPFILES EN_PROTECTED EN_CORRECTTEXT
   EN_STOPNOUNDO EN_IMECHANGE EN_SAVECLIPBOARD EN_OLEOPFAILED EN_OBJECTPOSITIONS
   EN_LINK EN_DRAGDROPDONE
   */
// ## BEGIN MacroCloak Generated Code
#if defined (EM_GETSEL)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef EM_GETSEL
#undef EM_SETSEL
#undef EM_GETRECT
#undef EM_SETRECT
#undef EM_SETRECTNP
#undef EM_SCROLL
#undef EM_LINESCROLL
#undef EM_SCROLLCARET
#undef EM_GETMODIFY
#undef EM_SETMODIFY
#undef EM_GETLINECOUNT
#undef EM_LINEINDEX
#undef EM_SETHANDLE
#undef EM_GETHANDLE
#undef EM_GETTHUMB
#undef EM_LINELENGTH
#undef EM_REPLACESEL
#undef EM_GETLINE
#undef EM_SETLIMITTEXT
#undef EM_CANUNDO
#undef EM_UNDO
#undef EM_FMTLINES
#undef EM_LINEFROMCHAR
#undef EM_SETTABSTOPS
#undef EM_SETPASSWORDCHAR
#undef EM_EMPTYUNDOBUFFER
#undef EM_GETFIRSTVISIBLELINE
#undef EM_SETREADONLY
#undef EM_SETWORDBREAKPROC
#undef EM_GETWORDBREAKPROC
#undef EM_GETPASSWORDCHAR
#undef EM_SETMARGINS
#undef EM_GETMARGINS
#undef EM_GETLIMITTEXT
#undef EM_POSFROMCHAR
#undef EM_CHARFROMPOS
#undef WM_CONTEXTMENU
#undef WM_PRINTCLIENT
#undef EM_CANPASTE
#undef EM_DISPLAYBAND
#undef EM_EXGETSEL
#undef EM_EXLIMITTEXT
#undef EM_EXLINEFROMCHAR
#undef EM_EXSETSEL
#undef EM_FINDTEXT
#undef EM_FORMATRANGE
#undef EM_GETCHARFORMAT
#undef EM_GETEVENTMASK
#undef EM_GETOLEINTERFACE
#undef EM_GETPARAFORMAT
#undef EM_GETSELTEXT
#undef EM_HIDESELECTION
#undef EM_PASTESPECIAL
#undef EM_REQUESTRESIZE
#undef EM_SELECTIONTYPE
#undef EM_SETBKGNDCOLOR
#undef EM_SETCHARFORMAT
#undef EM_SETEVENTMASK
#undef EM_SETOLECALLBACK
#undef EM_SETPARAFORMAT
#undef EM_SETTARGETDEVICE
#undef EM_STREAMIN
#undef EM_STREAMOUT
#undef EM_GETTEXTRANGE
#undef EM_FINDWORDBREAK
#undef EM_SETOPTIONS
#undef EM_GETOPTIONS
#undef EM_FINDTEXTEX
#undef EM_GETWORDBREAKPROCEX
#undef EM_SETWORDBREAKPROCEX
#undef EM_SETUNDOLIMIT
#undef EM_REDO
#undef EM_CANREDO
#undef EM_GETUNDONAME
#undef EM_GETREDONAME
#undef EM_STOPGROUPTYPING
#undef EM_SETTEXTMODE
#undef EM_GETTEXTMODE
#undef CHARFORMAT
#undef CFM_BOLD
#undef CFM_ITALIC
#undef CFM_UNDERLINE
#undef CFM_STRIKEOUT
#undef CFM_PROTECTED
#undef CFM_LINK
#undef CFM_SIZE
#undef CFM_COLOR
#undef CFM_FACE
#undef CFM_OFFSET
#undef CFM_CHARSET
#undef CFE_BOLD
#undef CFE_ITALIC
#undef CFE_UNDERLINE
#undef CFE_STRIKEOUT
#undef CFE_PROTECTED
#undef CFE_LINK
#undef CFE_AUTOCOLOR
#undef SCF_SELECTION
#undef SCF_WORD
#undef SCF_DEFAULT
#undef SCF_ALL
#undef ES_LEFT
#undef ES_CENTER
#undef ES_RIGHT
#undef ES_MULTILINE
#undef ES_UPPERCASE
#undef ES_LOWERCASE
#undef ES_PASSWORD
#undef ES_AUTOVSCROLL
#undef ES_AUTOHSCROLL
#undef ES_NOHIDESEL
#undef ES_OEMCONVERT
#undef ES_READONLY
#undef ES_WANTRETURN
#undef ES_NUMBER
#undef ES_SAVESEL
#undef ES_SUNKEN
#undef ES_DISABLENOSCROLL
#undef ES_SELECTIONBAR
#undef ES_NOOLEDRAGDROP
#undef ENM_NONE
#undef ENM_CHANGE
#undef ENM_UPDATE
#undef ENM_SCROLL
#undef ENM_KEYEVENTS
#undef ENM_MOUSEEVENTS
#undef ENM_REQUESTRESIZE
#undef ENM_SELCHANGE
#undef ENM_DROPFILES
#undef ENM_PROTECTED
#undef ENM_CORRECTTEXT
#undef ENM_SCROLLEVENTS
#undef ENM_DRAGDROPDONE
#endif
// ## END Generated Code


enum ES_styles {
   ES_LEFT=           0x0000,
   ES_CENTER=         0x0001,
   ES_RIGHT=          0x0002,
   ES_MULTILINE=      0x0004,
   ES_UPPERCASE=      0x0008,
   ES_NOOLEDRAGDROP= 0x0008,
   ES_LOWERCASE=      0x0010,
   ES_PASSWORD=       0x0020,
   ES_AUTOVSCROLL=    0x0040,
   ES_AUTOHSCROLL=    0x0080,
   ES_NOHIDESEL=      0x0100,
   ES_OEMCONVERT=     0x0400,
   ES_READONLY=       0x0800,
   ES_WANTRETURN=     0x1000,
   ES_NUMBER=         0x2000,
   ES_SUNKEN=         0x4000,
   ES_SAVESEL=        0x8000,
   ES_SELECTIONBAR= 0x01000000,
   ES_DISABLENOSCROLL= 0x00002000,
   };

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


template <typename CharT>
struct CHARFORMAT {
   unsigned cbSize;
   ulong mask;
   ulong effects;
   long yHeight;
   long yOffset;
   color::COLORREF crTextColor;
   byte bCharSet;
   byte bPitchAndFamily;
   CharT szFaceName [32];
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

enum notification_mask {  // used with EM_SETEVENTMASK
   ENM_NONE=             0x00000000,
   ENM_CHANGE=           0x00000001,
   ENM_UPDATE=           0x00000002,
   ENM_SCROLL=           0x00000004,
   ENM_SCROLLEVENTS=     0x00000008,
   ENM_DRAGDROPDONE=     0x00000010,
   ENM_KEYEVENTS=        0x00010000,
   ENM_MOUSEEVENTS=      0x00020000,
   ENM_REQUESTRESIZE=    0x00040000,
   ENM_SELCHANGE=        0x00080000,
   ENM_DROPFILES=        0x00100000,
   ENM_PROTECTED=        0x00200000,
   ENM_CORRECTTEXT=      0x00400000, // PenWin specific
   };

enum edit_notification_codes {
   EN_MSGFILTER=         0x0700,
   EN_REQUESTRESIZE=     0x0701,
   EN_SELCHANGE=         0x0702,
   EN_DROPFILES=         0x0703,
   EN_PROTECTED=         0x0704,
   EN_CORRECTTEXT=       0x0705, // PenWin specific
   EN_STOPNOUNDO=        0x0706,
   EN_IMECHANGE=         0x0707, // Far East specific
   EN_SAVECLIPBOARD=     0x0708,
   EN_OLEOPFAILED=       0x0709,
   EN_OBJECTPOSITIONS=   0x070a,
   EN_LINK=              0x070b,
   EN_DRAGDROPDONE=      0x070c,
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

template <typename CharT>
class char_format : public CHARFORMAT<CharT> {
public:
   char_format() 
      {
      cbSize= sizeof(CHARFORMAT<CharT>);
      mask= 0;  // So crTextColor, bCharSet, szFaceName, yOffset, yHeight, and effects are not set.
      // TODO: Add set() functions that also turn on the proper mask bit.
      }
   };

struct REQRESIZE : public WM_constants::NMHDR {
   types::RECT rc;
   };

}}
ENDWRAP
// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::controls::EM_GETSEL;
using ratwin::controls::EM_SETSEL;
using ratwin::controls::EM_GETRECT;
using ratwin::controls::EM_SETRECT;
using ratwin::controls::EM_SETRECTNP;
using ratwin::controls::EM_SCROLL;
using ratwin::controls::EM_LINESCROLL;
using ratwin::controls::EM_SCROLLCARET;
using ratwin::controls::EM_GETMODIFY;
using ratwin::controls::EM_SETMODIFY;
using ratwin::controls::EM_GETLINECOUNT;
using ratwin::controls::EM_LINEINDEX;
using ratwin::controls::EM_SETHANDLE;
using ratwin::controls::EM_GETHANDLE;
using ratwin::controls::EM_GETTHUMB;
using ratwin::controls::EM_LINELENGTH;
using ratwin::controls::EM_REPLACESEL;
using ratwin::controls::EM_GETLINE;
using ratwin::controls::EM_SETLIMITTEXT;
using ratwin::controls::EM_CANUNDO;
using ratwin::controls::EM_UNDO;
using ratwin::controls::EM_FMTLINES;
using ratwin::controls::EM_LINEFROMCHAR;
using ratwin::controls::EM_SETTABSTOPS;
using ratwin::controls::EM_SETPASSWORDCHAR;
using ratwin::controls::EM_EMPTYUNDOBUFFER;
using ratwin::controls::EM_GETFIRSTVISIBLELINE;
using ratwin::controls::EM_SETREADONLY;
using ratwin::controls::EM_SETWORDBREAKPROC;
using ratwin::controls::EM_GETWORDBREAKPROC;
using ratwin::controls::EM_GETPASSWORDCHAR;
using ratwin::controls::EM_SETMARGINS;
using ratwin::controls::EM_GETMARGINS;
using ratwin::controls::EM_GETLIMITTEXT;
using ratwin::controls::EM_POSFROMCHAR;
using ratwin::controls::EM_CHARFROMPOS;
using ratwin::controls::WM_CONTEXTMENU;
using ratwin::controls::WM_PRINTCLIENT;
using ratwin::controls::EM_CANPASTE;
using ratwin::controls::EM_DISPLAYBAND;
using ratwin::controls::EM_EXGETSEL;
using ratwin::controls::EM_EXLIMITTEXT;
using ratwin::controls::EM_EXLINEFROMCHAR;
using ratwin::controls::EM_EXSETSEL;
using ratwin::controls::EM_FINDTEXT;
using ratwin::controls::EM_FORMATRANGE;
using ratwin::controls::EM_GETCHARFORMAT;
using ratwin::controls::EM_GETEVENTMASK;
using ratwin::controls::EM_GETOLEINTERFACE;
using ratwin::controls::EM_GETPARAFORMAT;
using ratwin::controls::EM_GETSELTEXT;
using ratwin::controls::EM_HIDESELECTION;
using ratwin::controls::EM_PASTESPECIAL;
using ratwin::controls::EM_REQUESTRESIZE;
using ratwin::controls::EM_SELECTIONTYPE;
using ratwin::controls::EM_SETBKGNDCOLOR;
using ratwin::controls::EM_SETCHARFORMAT;
using ratwin::controls::EM_SETEVENTMASK;
using ratwin::controls::EM_SETOLECALLBACK;
using ratwin::controls::EM_SETPARAFORMAT;
using ratwin::controls::EM_SETTARGETDEVICE;
using ratwin::controls::EM_STREAMIN;
using ratwin::controls::EM_STREAMOUT;
using ratwin::controls::EM_GETTEXTRANGE;
using ratwin::controls::EM_FINDWORDBREAK;
using ratwin::controls::EM_SETOPTIONS;
using ratwin::controls::EM_GETOPTIONS;
using ratwin::controls::EM_FINDTEXTEX;
using ratwin::controls::EM_GETWORDBREAKPROCEX;
using ratwin::controls::EM_SETWORDBREAKPROCEX;
using ratwin::controls::EM_SETUNDOLIMIT;
using ratwin::controls::EM_REDO;
using ratwin::controls::EM_CANREDO;
using ratwin::controls::EM_GETUNDONAME;
using ratwin::controls::EM_GETREDONAME;
using ratwin::controls::EM_STOPGROUPTYPING;
using ratwin::controls::EM_SETTEXTMODE;
using ratwin::controls::EM_GETTEXTMODE;
using ratwin::controls::CHARFORMAT;
using ratwin::controls::CFM_BOLD;
using ratwin::controls::CFM_ITALIC;
using ratwin::controls::CFM_UNDERLINE;
using ratwin::controls::CFM_STRIKEOUT;
using ratwin::controls::CFM_PROTECTED;
using ratwin::controls::CFM_LINK;
using ratwin::controls::CFM_SIZE;
using ratwin::controls::CFM_COLOR;
using ratwin::controls::CFM_FACE;
using ratwin::controls::CFM_OFFSET;
using ratwin::controls::CFM_CHARSET;
using ratwin::controls::CFE_BOLD;
using ratwin::controls::CFE_ITALIC;
using ratwin::controls::CFE_UNDERLINE;
using ratwin::controls::CFE_STRIKEOUT;
using ratwin::controls::CFE_PROTECTED;
using ratwin::controls::CFE_LINK;
using ratwin::controls::CFE_AUTOCOLOR;
using ratwin::controls::SCF_SELECTION;
using ratwin::controls::SCF_WORD;
using ratwin::controls::SCF_DEFAULT;
using ratwin::controls::SCF_ALL;
using ratwin::controls::ES_LEFT;
using ratwin::controls::ES_CENTER;
using ratwin::controls::ES_RIGHT;
using ratwin::controls::ES_MULTILINE;
using ratwin::controls::ES_UPPERCASE;
using ratwin::controls::ES_LOWERCASE;
using ratwin::controls::ES_PASSWORD;
using ratwin::controls::ES_AUTOVSCROLL;
using ratwin::controls::ES_AUTOHSCROLL;
using ratwin::controls::ES_NOHIDESEL;
using ratwin::controls::ES_OEMCONVERT;
using ratwin::controls::ES_READONLY;
using ratwin::controls::ES_WANTRETURN;
using ratwin::controls::ES_NUMBER;
using ratwin::controls::ES_SAVESEL;
using ratwin::controls::ES_SUNKEN;
using ratwin::controls::ES_DISABLENOSCROLL;
using ratwin::controls::ES_SELECTIONBAR;
using ratwin::controls::ES_NOOLEDRAGDROP;
using ratwin::controls::ENM_NONE;
using ratwin::controls::ENM_CHANGE;
using ratwin::controls::ENM_UPDATE;
using ratwin::controls::ENM_SCROLL;
using ratwin::controls::ENM_KEYEVENTS;
using ratwin::controls::ENM_MOUSEEVENTS;
using ratwin::controls::ENM_REQUESTRESIZE;
using ratwin::controls::ENM_SELCHANGE;
using ratwin::controls::ENM_DROPFILES;
using ratwin::controls::ENM_PROTECTED;
using ratwin::controls::ENM_CORRECTTEXT;
using ratwin::controls::ENM_SCROLLEVENTS;
using ratwin::controls::ENM_DRAGDROPDONE;
#endif
// ## END Generated Code


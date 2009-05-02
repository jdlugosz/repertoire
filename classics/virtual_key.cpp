// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\virtual_key.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\virtual_key.h"
#include "classics\string_ios.h"

STARTWRAP
namespace classics {
namespace VK {

static const char FNAME[]= __FILE__;

static const char* key_names[256]= {
   /* 00-07 */   0, "LBUTTON", "RBUTTON", "CANCEL", "MBUTTON", 0,0,0,
   /* 08-0f */    "BACK", "TAB", 0,0, "CLEAR", "RETURN", 0,0,
   /* 10-17 */   "SHIFT", "CONTROL", "MENU", "PAUSE", "CAPITAL", 0,0,0,
   /* 18-1F */   0,0,0, "ESCAPE", 0,0,0,0,
   /* 20-27 */   "SPACE", "PGUP", "PGDOWN", "END", "HOME", "LEFT", "UP", "RIGHT",
   /* 28-2F */   "DOWN", "SELECT", 0,0, "SNAPSHOT", "INSERT", "DELETE", "HELP",
   /* 30-37 */   "0", "1", "2", "3", "4", "5", "6", "7",
   /* 38-3F */   "8", "9", 0,0,0,0,0,0,
   /* 40-47 */   0, "A", "B", "C", "D", "E", "F", "G",
   /* 48-4F */   "H", "I", "J", "K", "L", "M", "N", "O",
   /* 50-57 */   "P", "Q", "R", "S", "T", "U", "V", "W",
   /* 58-5F */   "X", "Y", "Z",  0,0,0,0,0,
   /* 60-67 */   "NUMPAD0", "NUMPAD1", "NUMPAD2", "NUMPAD3", "NUMPAD4", "NUMPAD5", "NUMPAD6", "NUMPAD7",
   /* 68-6F */   "NUMPAD8", "NUMPAD9", "MULTIPLY", "ADD", 0, "SUBTRACT", "DECIMAL", "DEVIDE",
   /* 70-77 */   "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
   /* 78-7F */   "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16",
   /* 80-87 */   "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
   /* 88-8F */   0,0,0,0, 0,0,0,0,
   /* 90-97 */   "NUMLOCK", "SCROLL", 0,0,0,0,0,0,
   /* 98-9F */   0,0,0,0, 0,0,0,0,
   /* A0-A7 */   0,0,0,0, 0,0,0,0,
   /* A8-AF */   0,0,0,0, 0,0,0,0,
   /* B0-B7 */   0,0,0,0, 0,0,0,0,
   /* B8-BF */   0,0, "OEM_1", "OEM_PLUS", "OEM_COMMA", "OEM_MINUS", "OEM_PERIOD", "OEM_2",
   /* C0-C7 */   "OEM_3", 0,0,0, 0,0,0,0,
   /* C8-CF */   0,0,0,0, 0,0,0,0,
   /* D0-D7 */   0,0,0,0, 0,0,0,0,
   /* D8-DF */   0,0,0, "OEM_4", "OEM_5", "OEM_6", "OEM_7", "OEM_8",
   /* E0-E7 */   0,0, "OEM_102", 0,0,0, 0,0,
   /* E8-EF */   0,0,0,0, 0,0,0,0,
   /* F0-F7 */   0,0,0,0,0,0, "ATTN", "CRSEL"
   /* F8-FF */   "EXSEL", "EREOF", "PLAY", "ZOOM", "NONAME", "PA1", "OEM_CLEAR"
   };


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static string modifier_string (VK code)
 {
 int modifier= int(code)&0xffffff00;
 string result;
 if (modifier & ShiftKey)  result += "Shift+";
 if (modifier & ControlKey) {
    if (modifier & CtrlOnLeft)  result += "L";
    if (modifier & CtrlOnRight)  result += "R";
    result += "Ctrl+";
    }
 if (modifier & AltKey) {
    if (modifier & AltOnLeft)  result += "L";
    if (modifier & AltOnRight)  result += "R";
    result += "Alt+";
    }
 if (modifier & NumPadKey)  result += "NumPad+";
 if (modifier & ExtKey)  result += "Ext+";
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static string base_string (VK code)
 {
 int lowbyte= int(code) & 0xff;
 const char* name= key_names[lowbyte];
 if (name)  return name;
 // else figure something out
 string result;
 Fmt(result) << 'K' << lowbyte;
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring as_ustring (VK code)
 {
 return modifier_string(code) + base_string(code);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static int parse_prefixes (const char*& p)
 {
 int result= 0;
 for (;;) {
    if (!strnicmp(p,"shift+",6)) {
       result |= ShiftKey;
       p += 6;
       }
    else if (!strnicmp (p,"ctrl+",5)) {
       result |= ControlKey;
       p += 5;
       }
    else if (!strnicmp (p,"alt+",4)) {
       result |= AltKey;
       p += 4;
       }
    // >> need to handle "numpad+"
    else break;  //quit when I can't match a prefix
    }
 return result;  //and updated p goes out
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template<>
VK parse<VK> (const ustring& us)
 {
 string s= us;
 const char* p= s.c_str();
 int result= parse_prefixes (p);
 // is it a K-number?
 if ((p[0]=='K' || p[0]=='k') && p[1]>='0' && p[1]<='9') {
    int num= atoi (p+1);  // standard atoi is weak on error checking.
    if (num > 255)  goto error;
    result += num;
    return VK(result);
    }
 else {  //match the chart
    int loop;
    for (loop= 0;  loop < 256;  loop++) {
       // brute but simple, for now
       const char* name= key_names[loop];
       if (!name)  continue;
       if (!strcmpi (name, p))  return VK(result+loop);
       }
    }
 error:
    exception X ("Classics", "invalid VK name", FNAME, __LINE__);
    X.add_key ("text", p);
    throw X;
    return VK_invalid;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

VK VKencode (unsigned key, unsigned ks)
 {
 unsigned flags= 0;
 enum {
    RIGHT_ALT_PRESSED= 0x0001,
    LEFT_ALT_PRESSED=  0x0002,
    RIGHT_CTRL_PRESSED= 0x0004,
    LEFT_CTRL_PRESSED= 0x0008,
    SHIFT_PRESSED= 0x0010,
    NUMLOCK_ON= 0x0020,
    CAPSLOCK_ON= 0x0080,
    EXTENDED= 0x100
    };
 if (ks & RIGHT_ALT_PRESSED)  flags |= AltKey|AltOnRight;
 if (ks & LEFT_ALT_PRESSED)  flags |= AltKey|AltOnLeft;
 if (ks & RIGHT_CTRL_PRESSED)  flags |= ControlKey|CtrlOnRight;
 if (ks & LEFT_CTRL_PRESSED)  flags |= ControlKey|CtrlOnLeft;
 if (ks & SHIFT_PRESSED)  flags |= ShiftKey;
 if (ks & NUMLOCK_ON)  flags |= NumLockSet;
 if (ks & CAPSLOCK_ON)  flags |= CapLockSet;
 if ((key >= 0x21 && key <= 0x28) || key == 0x2d || key == 0x2e) {
    // distinguish Numpad (with numlock off) from center section
    if (ks & EXTENDED)  flags |= ExtKey;
    else flags |= NumPadKey;
    }
 return VK(key|flags);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}} // end classics
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\virtual_key_names.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\virtual_key.h"


STARTWRAP
namespace classics {
namespace VK {

static const VK VK_LBUTTON= VK(0x01);   //Left mouse button.  
static const VK VK_RBUTTON= VK(0x02);  //Right mouse button.  
static const VK VK_CANCEL= VK(0x03);  //Used for control-break processing.  
static const VK VK_MBUTTON= VK(0x04);  //Middle mouse button (3-button mouse).  
//    05h through 07h undefined.  
static const VK VK_BACK= VK(0x08);    
static const VK VK_TAB= VK(0x09);  
//    0Ah and 0Bh undefined.  
static const VK VK_CLEAR= VK(0x0C);    
static const VK VK_RETURN= VK(0x0D);  
//    0Eh and 0Fh undefined.  
static const VK VK_SHIFT= VK(0x10);    
static const VK VK_CONTROL= VK(0x11);  
static const VK VK_MENU= VK(0x12);  
static const VK VK_PAUSE= VK(0x13);  
static const VK VK_CAPITAL= VK(0x14);  
//    15h through 1Ah undefined.  
static const VK VK_ESCAPE= VK(0x1B);    
//    1Ch through 1Fh undefined.  
static const VK VK_SPACE= VK(0x20);    
static const VK /*VK_PRIOR*/ VK_PGUP= VK(0x21);  //Page up.  
static const VK /*VK_NEXT*/ VK_PGDOWN= VK(0x22);  //Page down.  
static const VK VK_END= VK(0x23);    
static const VK VK_HOME= VK(0x24);  
static const VK VK_LEFT= VK(0x25);  
static const VK VK_UP= VK(0x26);  
static const VK VK_RIGHT= VK(0x27);  
static const VK VK_DOWN= VK(0x28);  
static const VK VK_SELECT= VK(0x29);  
#if 0
static const VK VK_PRINT= VK(0x2A);  //Only used by Nokia.  
static const VK VK_EXECUTE= VK(0x2B);  //Never used.  
#endif
static const VK VK_SNAPSHOT= VK(0x2C);  //SYSREQ key starting with Windows 3.0.  
static const VK VK_INSERT= VK(0x2D);    
static const VK VK_DELETE= VK(0x2E);  
static const VK VK_HELP= VK(0x2F);  
static const VK VK_0= VK(0x30);  
static const VK VK_1= VK(0x31);  
static const VK VK_2= VK(0x32);  
static const VK VK_3= VK(0x33);  
static const VK VK_4= VK(0x34);  
static const VK VK_5= VK(0x35);  
static const VK VK_6= VK(0x36);  
static const VK VK_7= VK(0x37);  
static const VK VK_8= VK(0x38);  
static const VK VK_9= VK(0x39);  
//    3Ah though 40h undefined.
static const VK VK_A= VK(0x41);    
static const VK VK_B= VK(0x42);  
static const VK VK_C= VK(0x43);  
static const VK VK_D= VK(0x44);  
static const VK VK_E= VK(0x45);  
static const VK VK_F= VK(0x46);  
static const VK VK_G= VK(0x47);  
static const VK VK_H= VK(0x48);  
static const VK VK_I= VK(0x49);  
static const VK VK_J= VK(0x4A);  
static const VK VK_K= VK(0x4B);  
static const VK VK_L= VK(0x4C);  
static const VK VK_M= VK(0x4D);  
static const VK VK_N= VK(0x4E);  
static const VK VK_O= VK(0x4F);  
static const VK VK_P= VK(0x50);  
static const VK VK_Q= VK(0x51);  
static const VK VK_R= VK(0x52);  
static const VK VK_S= VK(0x53);  
static const VK VK_T= VK(0x54);  
static const VK VK_U= VK(0x55);  
static const VK VK_V= VK(0x56);  
static const VK VK_W= VK(0x57);  
static const VK VK_X= VK(0x58);  
static const VK VK_Y= VK(0x59);  
static const VK VK_Z= VK(0x5A);  
//    5Bh through 5Fh undefined.  
static const VK VK_NUMPAD0= VK(0x60);    
static const VK VK_NUMPAD1= VK(0x61);  
static const VK VK_NUMPAD2= VK(0x62);  
static const VK VK_NUMPAD3= VK(0x63);  
static const VK VK_NUMPAD4= VK(0x64);  
static const VK VK_NUMPAD5= VK(0x65);  
static const VK VK_NUMPAD6= VK(0x66);  
static const VK VK_NUMPAD7= VK(0x67);  
static const VK VK_NUMPAD8= VK(0x68);  
static const VK VK_NUMPAD9= VK(0x69);  
static const VK VK_MULTIPLY= VK(0x6A);  
static const VK VK_ADD= VK(0x6B);  
//VK VK_SEPARATER= VK(0x6C);  //Never generated by keyboard driver.  
static const VK VK_SUBTRACT= VK(0x6D);    
static const VK VK_DECIMAL= VK(0x6E);  
static const VK VK_DIVIDE= VK(0x6F);  
static const VK VK_F1= VK(0x70);  
static const VK VK_F2= VK(0x71);  
static const VK VK_F3= VK(0x72);  
static const VK VK_F4= VK(0x73);  
static const VK VK_F5= VK(0x74);  
static const VK VK_F6= VK(0x75);  
static const VK VK_F7= VK(0x76);  
static const VK VK_F8= VK(0x77);  
static const VK VK_F9= VK(0x78);  
static const VK VK_F10= VK(0x79);  
static const VK VK_F11= VK(0x7A);  
static const VK VK_F12= VK(0x7B);  
static const VK VK_F13= VK(0x7C);  
static const VK VK_F14= VK(0x7D);  
static const VK VK_F15= VK(0x7E);  
static const VK VK_F16= VK(0x7F);  
static const VK VK_F17= VK(0x80);  
static const VK VK_F18= VK(0x81);  
static const VK VK_F19= VK(0x82);  
static const VK VK_F20= VK(0x83);  
static const VK VK_F21= VK(0x84);  
static const VK VK_F22= VK(0x85);  
static const VK VK_F23= VK(0x86);  
static const VK VK_F24= VK(0x87);  
//    88h through 8Fh unassigned.  
static const VK VK_NUMLOCK= VK(0x90);  //NUMLOCK on all keyboards.  
static const VK VK_OEM_SCROLL= VK(0x91);  //SCROLL LOCK on all keyboards.  
//    92h through B9h unassigned.  
static const VK VK_OEM_1= VK(0x0BA);  //Punctuation.  
static const VK VK_OEM_PLUS= VK(0xBB); //Punctuation.  
static const VK VK_OEM_COMMA= VK(0xBC); //Punctuation.  
static const VK VK_OEM_MINUS= VK(0xBD); //Punctuation.  
static const VK VK_OEM_PERIOD= VK(0xBE);  //Punctuation.  
static const VK VK_OEM_2= VK(0xBF);  //Punctuation.  
static const VK VK_OEM_3= VK(0xC0);  //Punctuation.  
//    C1h through DAh unassigned.  
static const VK VK_OEM_4= VK(0xDB);  //Punctuation.  
static const VK VK_OEM_5= VK(0xDC);  //Punctuation.  
static const VK VK_OEM_6= VK(0xDD);  //Punctuation.  
static const VK VK_OEM_7= VK(0xDE);  //Punctuation.  
static const VK VK_OEM_8= VK(0xDF);  //Punctuation.  
//VK VK_F17= VK(0xE0);  //F17 key on Olivetti extended keyboard (internal use only).  
//VK VK_F18= VK(0xE1);  //F18 key on Olivetti extended keyboard (internal use only).  
static const VK VK_OEM_102= VK(0xE2);  // '<' or '|' on IBM-compatible 102 enhanced keyboard (non-U.S.).  
#if 0
static const VK VK_ICO_HELP= VK(0xE3);  //Help key on Olivetti extended keyboard (internal use only).  
static const VK VK_ICO_00= VK(0xE4);  //00 key on Olivetti extended keyboard (internal use only).  
//    E5h unassigned.  
static const VK VK_ICO_CLEAR= VK(0xE6);  //Olivetti extended keyboard (internal use only).  
//    E7h and E8h unassigned.  
static const VK VK_OEM_RESET= VK(0xE9);  //Only used by Nokia.  
static const VK VK_OEM_JUMP= VK(0xEA);  //Only used by Nokia.  
static const VK VK_OEM_PA1= VK(0xEB);  //Only used by Nokia.  
static const VK VK_OEM_PA2= VK(0xEC);  //Only used by Nokia.  
static const VK VK_OEM_PA3= VK(0xED);  //Only used by Nokia.  
static const VK VK_OEM_WSCTRL= VK(0xEE);  //Only used by Nokia.  
static const VK VK_OEM_CUSEL= VK(0xEF);  //Only used by Nokia.  
static const VK VK_OEM_ATTN= VK(0xF0);  //Only used by Nokia.  
static const VK VK_OEM_FINNISH= VK(0xF1);  //Only used by Nokia.  
static const VK VK_OEM_COPY= VK(0xF2);  //Only used by Nokia.  
static const VK VK_OEM_AUTO= VK(0xF3); //Only used by Nokia.  
static const VK VK_OEM_ENLW= VK(0xF4);  //Only used by Nokia.  
static const VK VK_OEM_BACKTAB= VK(0xF5);  //Only used by Nokia.  
#endif
static const VK VK_ATTN= VK(0xF6);    
static const VK VK_CRSEL= VK(0xF7);  
static const VK VK_EXSEL= VK(0xF8);  
static const VK VK_EREOF= VK(0xF9);  
static const VK VK_PLAY= VK(0xFA);  
static const VK VK_ZOOM= VK(0xFB);  
static const VK VK_NONAME= VK(0xFC);  
static const VK VK_PA1= VK(0xFD);  
static const VK VK_OEM_CLEAR= VK(0xFE);  

}}  //end of namespace
ENDWRAP



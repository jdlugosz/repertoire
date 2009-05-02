// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\console=struct.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#include "ratwin\base.h"
#include "classics\2D_point.h"

STARTWRAP
namespace ratwin {
namespace io {

template <typename CharType>
struct KEY_EVENT_RECORD {
   int /* bool */ KeyDown;
   ushort RepeatCount;
   ushort VirtualKeyCode;
   ushort VirtualScanCode;
   CharType Char;
   // trust that an extra padding byte will follow when Char is 8-bit
   ulong ControlKeyState;
   };

enum {  // use with EventType member of INPUT_RECORD
   KEY_EVENT= 0x0001, // Event contains key event record
   MOUSE_EVENT= 0x0002, // Event contains mouse event record
   WINDOW_BUFFER_SIZE_EVENT= 0x0004, // Event contains window change event record
   MENU_EVENT= 0x0008, // Event contains menu event record
   FOCUS_EVENT= 0x0010 // event contains focus change
   };
   
template<typename CharType>
struct INPUT_RECORD {
   ushort EventType;
   union {  // a free-union
      KEY_EVENT_RECORD<CharType> KeyEvent;
#if 0
      MOUSE_EVENT_RECORD MouseEvent;
      WINDOW_BUFFER_SIZE_RECORD WindowBufferSizeEvent;
      MENU_EVENT_RECORD MenuEvent;
      FOCUS_EVENT_RECORD FocusEvent;
#endif
      };
   };

typedef classics::generic_2D_point<short> COORD;

struct SMALL_RECT {
   short Left;
   short Top;
   short Right;
   short Bottom;
   };

struct CONSOLE_SCREEN_BUFFER_INFO {
   COORD Size;
   COORD CursorPosition;
   ushort Attributes;
   SMALL_RECT Window;
   COORD MaximumWindowSize;
   };


struct CONSOLE_CURSOR_INFO {
   ulong  dwSize;
   int   bVisible;
   };



} //end io
}
ENDWRAP



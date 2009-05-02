// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\console.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\console.h contains globals.  Include console=struct.h instead.
#endif

#include "ratwin\io\console=struct.h"

extern "C" {
__declspec(dllimport) int __stdcall ReadConsoleInputA (Dlugosz::ratwin::arg::arg32, void*, int, int*);
__declspec(dllimport) int __stdcall ReadConsoleInputW (Dlugosz::ratwin::arg::arg32, void*, int, int*);
__declspec(dllimport) int __stdcall WriteConsoleW (Dlugosz::ratwin::arg::arg32, const void*, int, int*, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall WriteConsoleA (Dlugosz::ratwin::arg::arg32, const void*, int, int*, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall SetConsoleMode (Dlugosz::ratwin::arg::arg32, unsigned);
__declspec(dllimport) int __stdcall GetConsoleCursorInfo (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall GetConsoleScreenBufferInfo (Dlugosz::ratwin::arg::arg32, void*);
__declspec(dllimport) int __stdcall SetConsoleCursorPosition (Dlugosz::ratwin::arg::arg32, ratwin::io::COORD);
}

///////////////// end of "cloaked" imports


STARTWRAP
namespace ratwin {
namespace io {

inline
bool ReadConsoleInput (types::HANDLE console, INPUT_RECORD<char>* array, int length, int* lengthout)
 {
 return ::ReadConsoleInputA (reinterpret_cast<arg::arg32>(console), array, length, lengthout);
 }

inline
bool ReadConsoleInput (types::HANDLE console, INPUT_RECORD<wchar_t>* array, int length, int* lengthout)
 {
 return ::ReadConsoleInputW (reinterpret_cast<arg::arg32>(console), array, length, lengthout);
 }


inline
bool WriteConsole (types::HANDLE console, const wchar_t* src, int count, int& count_out)
 {
 return ::WriteConsoleW (reinterpret_cast<arg::arg32>(console), src, count, &count_out, 0);
 }
 
inline
bool WriteConsole (types::HANDLE console, const char* src, int count, int& count_out)
 {
 return ::WriteConsoleA (reinterpret_cast<arg::arg32>(console), src, count, &count_out, 0);
 }


enum ConsoleMode_t {
   ENABLE_PROCESSED_INPUT= 0x0001,
   ENABLE_LINE_INPUT=      0x0002,
   ENABLE_ECHO_INPUT=      0x0004,
   ENABLE_WINDOW_INPUT=    0x0008,
   ENABLE_MOUSE_INPUT=     0x0010,
   ENABLE_PROCESSED_OUTPUT=    0x0001,
   ENABLE_WRAP_AT_EOL_OUTPUT=  0x0002
   };

inline
bool SetConsoleMode (types::HANDLE console, ConsoleMode_t mode)
 {
 return ::SetConsoleMode (reinterpret_cast<arg::arg32>(console), mode);
 }
 
inline
bool GetConsoleCursorInfo (types::HANDLE console, CONSOLE_CURSOR_INFO& result)
 {
 return ::GetConsoleCursorInfo (reinterpret_cast<arg::arg32>(console), &result);
 }
 
inline
bool GetConsoleScreenBufferInfo (types::HANDLE console, CONSOLE_SCREEN_BUFFER_INFO& result)
 {
 return ::GetConsoleScreenBufferInfo (reinterpret_cast<arg::arg32>(console), &result);
 }

inline
bool SetConsoleCursorPosition (types::HANDLE console, COORD pos)
 {
 return ::SetConsoleCursorPosition (reinterpret_cast<arg::arg32>(console), pos);
 }

} //end io
}
ENDWRAP




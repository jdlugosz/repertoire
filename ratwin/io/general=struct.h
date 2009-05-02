// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\general=struct.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace io {

#if !defined STD_INPUT_HANDLE
  // skip these if #define symbols are already present.
  
enum StdHandle {
   STD_INPUT_HANDLE= -10,
   STD_OUTPUT_HANDLE= -11,
   STD_ERROR_HANDLE= -12,
   };

enum errors {
   ERROR_HANDLE_EOF= 38,
   ERROR_BROKEN_PIPE= 109,
   ERROR_PIPE_CONNECTED= 535,
   ERROR_IO_PENDING= 997,
   };

#endif

struct OVERLAPPED {
   ulong   Internal;
   ulong   InternalHigh;
   ulong   Offset;
   ulong   OffsetHigh;
   types::HANDLE  hEvent;
   };

struct overlapped : public OVERLAPPED {
   overlapped() {hEvent=0;}
   void offset (ulong x) { Offset= x; OffsetHigh= 0; }
   };

typedef void (__stdcall *COMPLETION_ROUTINE) (ulong error, ulong bytes_transferred, OVERLAPPED*);



} //end io
}
ENDWRAP


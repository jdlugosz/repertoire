// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\general=struct.h
// Revision: 

#pragma once
#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace io {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::io)
   STD_INPUT_HANDLE STD_OUTPUT_HANDLE STD_ERROR_HANDLE ERROR_HANDLE_EOF ERROR_BROKEN_PIPE ERROR_PIPE_CONNECTED
   ERROR_IO_PENDING
*/
// ## BEGIN MacroCloak Generated Code
#if defined (STD_INPUT_HANDLE)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef STD_INPUT_HANDLE
#undef STD_OUTPUT_HANDLE
#undef STD_ERROR_HANDLE
#undef ERROR_HANDLE_EOF
#undef ERROR_BROKEN_PIPE
#undef ERROR_PIPE_CONNECTED
#undef ERROR_IO_PENDING
#endif
// ## END Generated Code
  
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
// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::io::STD_INPUT_HANDLE;
using ratwin::io::STD_OUTPUT_HANDLE;
using ratwin::io::STD_ERROR_HANDLE;
using ratwin::io::ERROR_HANDLE_EOF;
using ratwin::io::ERROR_BROKEN_PIPE;
using ratwin::io::ERROR_PIPE_CONNECTED;
using ratwin::io::ERROR_IO_PENDING;
#endif
// ## END Generated Code


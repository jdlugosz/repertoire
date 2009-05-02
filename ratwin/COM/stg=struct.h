// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\stg=struct.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin)
   STGM_DIRECT STGM_TRANSACTED STGM_SIMPLE STGM_READ STGM_WRITE STGM_READWRITE STGM_SHARE_DENY_NONE
   STGM_SHARE_DENY_READ STGM_SHARE_DENY_WRITE STGM_SHARE_EXCLUSIVE STGM_CREATE STGM_CONVERT
   STGM_FAILIFTHERE STGM_PRIORITY STGM_DELETEONRELEASE STGM_NOSCRATCH STGM_NOSNAPSHOT
*/
// ## BEGIN MacroCloak Generated Code
#if defined (STGM_DIRECT)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef STGM_DIRECT
#undef STGM_TRANSACTED
#undef STGM_SIMPLE
#undef STGM_READ
#undef STGM_WRITE
#undef STGM_READWRITE
#undef STGM_SHARE_DENY_NONE
#undef STGM_SHARE_DENY_READ
#undef STGM_SHARE_DENY_WRITE
#undef STGM_SHARE_EXCLUSIVE
#undef STGM_CREATE
#undef STGM_CONVERT
#undef STGM_FAILIFTHERE
#undef STGM_PRIORITY
#undef STGM_DELETEONRELEASE
#undef STGM_NOSCRATCH
#undef STGM_NOSNAPSHOT
#endif
// ## END Generated Code

enum STGM {
   // group 1
   STGM_DIRECT=             0x00000000L,
   STGM_TRANSACTED=         0x00010000L,
   STGM_SIMPLE=             0x08000000L,
   // group 2
   STGM_READ=               0x00000000L,
   STGM_WRITE=              0x00000001L,
   STGM_READWRITE=          0x00000002L,
   // group 3
   STGM_SHARE_DENY_NONE=    0x00000040L,
   STGM_SHARE_DENY_READ=    0x00000030L,
   STGM_SHARE_DENY_WRITE=   0x00000020L,
   STGM_SHARE_EXCLUSIVE=    0x00000010L,
   // group 4
   STGM_CREATE=             0x00001000L,
   STGM_CONVERT=            0x00020000L,
      // note: always converts, even if underlying file was already a docfile.
   STGM_FAILIFTHERE=        0x00000000L,
   // single items (not grouped)
   STGM_PRIORITY=           0x00040000L,
   STGM_DELETEONRELEASE=    0x04000000L,
   STGM_NOSCRATCH=          0x00100000L,
   STGM_NOSNAPSHOT=         0x00200000L,
   };


} // end of namespace
ENDWRAP
// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::STGM_DIRECT;
using ratwin::STGM_TRANSACTED;
using ratwin::STGM_SIMPLE;
using ratwin::STGM_READ;
using ratwin::STGM_WRITE;
using ratwin::STGM_READWRITE;
using ratwin::STGM_SHARE_DENY_NONE;
using ratwin::STGM_SHARE_DENY_READ;
using ratwin::STGM_SHARE_DENY_WRITE;
using ratwin::STGM_SHARE_EXCLUSIVE;
using ratwin::STGM_CREATE;
using ratwin::STGM_CONVERT;
using ratwin::STGM_FAILIFTHERE;
using ratwin::STGM_PRIORITY;
using ratwin::STGM_DELETEONRELEASE;
using ratwin::STGM_NOSCRATCH;
using ratwin::STGM_NOSNAPSHOT;
#endif
// ## END Generated Code



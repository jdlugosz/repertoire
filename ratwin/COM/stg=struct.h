// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\stg=struct.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

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



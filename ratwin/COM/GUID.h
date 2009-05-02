// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#include "ratwin\base.h"

// GLOBAL because the compiler has built-in awareness.
// specifically, the intrinsic __guid operator returns a ::_GUID value.
#ifndef GUID_DEFINED
#define GUID_DEFINED
struct _GUID {
    unsigned __int32      time_low;
    unsigned __int16      time_mid;
    unsigned __int16      time_hi : 12;  //low bits
    unsigned __int16      version : 4;  //high bits
    unsigned __int8       clock_seq_hi : 6;  //low bits
    unsigned __int8       reserved : 2; // 2 or 3, depending
    unsigned __int8       clock_seq_low;
    unsigned __int8       node[6];
   };

#endif /* GUID_DEFINED */

STARTWRAP
namespace ratwin {

typedef _GUID GUID;
typedef GUID IID;
typedef GUID CLSID;


} // end ratwin namespace
ENDWRAP



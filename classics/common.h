// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\common.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#include "classics\portability.h"

STARTWRAP
namespace classics {

typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char byte;

#ifdef _WIN64
typedef __int64 address_t;
#else
typedef unsigned int address_t;
#endif

}  //end of namespace

ENDWRAP


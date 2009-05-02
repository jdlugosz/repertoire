// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\schedule_t.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined CLASSICS_SCHEDULE_INCLUDED
#define CLASSICS_SCHEDULE_INCLUDED

#include "classics\common.h"

STARTWRAP
namespace classics {

enum schedule_t { Never=0, Early=16*1024, Late=48*1024, schedule_t_dummy_=0xffffffff };
const schedule_t Normal= schedule_t (32*1024);

inline
schedule_t low (schedule_t x)
 {
 return schedule_t ( x - 4*1024);
 }
 
inline
schedule_t high (schedule_t x)
 {
 return schedule_t ( x + 4*1024);
 }

inline
schedule_t always (schedule_t x)
 {
 return schedule_t ( x | 0x00010000);
 }


} // end of classics
ENDWRAP

#endif



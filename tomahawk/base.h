// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\base.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "classics\2D_point.h"

STARTWRAP
namespace tomahawk {
using classics::ulong;
using classics::ushort;
using classics::byte;

typedef classics::generic_2D_point<int> point;

}
ENDWRAP


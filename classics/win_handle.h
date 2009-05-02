// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\win_handle.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "ratwin\base.h"  //need meaning of HANDLE

STARTWRAP
namespace classics {

// various things you can do to a Windows HANDLE, with the following features:
//   A)  full error checking
//   B)  no global functions in this header.

CLASSICS_EXPORT bool wait (ratwin::types::HANDLE h, unsigned timeout=-1);

}

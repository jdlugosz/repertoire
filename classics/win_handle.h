// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\win_handle.h
// Revision: public build 8, shipped on 11-July-2006

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

CLASSICS_EXPORT bool wait (ratwin::types::Kernel_HANDLE h, unsigned timeout=-1);
}

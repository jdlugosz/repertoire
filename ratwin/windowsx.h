// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\windowsx.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_WINDOWSX_INCLUDED
#define RATWIN_WINDOWSX_INCLUDED

#include "ratwin\utilities.h"
#include "ratwin\controls\basic.h"

STARTWRAP
namespace ratwin {
namespace windowsx {

typedef window::CREATESTRUCT* LPCREATESTRUCT;
typedef long LRESULT;
typedef unsigned UINT;
typedef ulong DWORD;
typedef int BOOL;
using controls::DRAWITEMSTRUCT;
using util::LOWORD;
using util::HIWORD;
using window::DefWindowProc;

}}
ENDWRAP
#endif

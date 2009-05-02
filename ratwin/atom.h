// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\atom.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_ATOM_INCLUDED
#define RATWIN_ATOM_INCLUDED

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) unsigned short __stdcall GlobalFindAtomA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned short __stdcall FindAtomA (Dlugosz::ratwin::arg::carg32);
}


STARTWRAP
namespace ratwin {

namespace atom {


inline
types::ATOM GlobalFindAtom (const char* name)
  { return ::GlobalFindAtomA (reinterpret_cast<arg::carg32>(name)); }

inline
types::ATOM FindAtom (const char* name)
  { return ::FindAtomA (reinterpret_cast<arg::carg32>(name)); }

}}
ENDWRAP
#endif


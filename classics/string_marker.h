// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string_marker.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\string.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace string_marker {

static const wchar_t ESC= L'\x001b';
static const wchar_t Split4= L'\x001c';
static const wchar_t Split3= L'\x001d';
static const wchar_t Split2= L'\x001e';
static const wchar_t Split1= L'\x001f';
static const wchar_t Open1= L'\x0011';
static const wchar_t Close1= L'\x0012';
static const wchar_t Open2= L'\x0013';
static const wchar_t Close2= L'\x0014';

CLASSICS_EXPORT int scan_for (wstring value, wchar_t target, int startpos, int maxpos=-1);
CLASSICS_EXPORT int scan_for_match (const wstring& value, int startpos, int maxpos=-1);
bool is_open (wchar_t c);
bool is_close (wchar_t c);
bool is_split (wchar_t c);

} //end of string_marker

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP


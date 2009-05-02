// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\UTF-8.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\portability.h"
STARTWRAP
namespace classics {

CLASSICS_EXPORT __int32 __stdcall UCS2_to_UTF8 (const wchar_t* input, int chars, int* chars_processed, char* output, int bufsize);


} //end namespace classics
ENDWRAP


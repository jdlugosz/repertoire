// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\UTF-8.h
// Revision: public build 8, shipped on 11-July-2006

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


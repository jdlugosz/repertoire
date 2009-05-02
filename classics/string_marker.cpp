// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string_marker.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\string_marker.h"


STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int string_marker::scan_for (wstring value, wchar_t target, int startpos, int maxpos)
 {
 // >> not complete:  doesn't ignore ballanced pairs.
 const wchar_t* p= value.get_buffer();
 const int len= maxpos==-1 ? value.elcount() : maxpos;
 for (;;) {
    if (startpos >= len)  return -1;  //not found
    if (p[startpos] == target)  return startpos;
    ++startpos;
    }
 return -1;  //stupid compiler
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int string_marker::scan_for_match (const wstring& value, int startpos, int maxpos)
 {
 // >> not complete:  doesn't ignore ballanced pairs.
 const wchar_t ch= value.get_at(startpos);
 return scan_for (value, ch+1, startpos, maxpos);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP


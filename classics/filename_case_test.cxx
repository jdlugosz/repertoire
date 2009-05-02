// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\filename_case_test.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include <iostream>
#include <cstdio>
#include "classics\filename_t.h"
#include "classics\string_ios.h"
using std::cout;
using std::endl;
using classics::filename_t;
using classics::string;
using classics::ustring;
using classics::wstring;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const char* uni (wchar_t c)
 {
 static char buf[]= "U+0000";
 sprintf (buf+2, "%04X", c);
 return buf;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool filter (wchar_t c)
 {
 cout << uni(c) << " skipped because xxx\n";
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void domap (wchar_t c)
 {
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 // I have to do the mapping one at a time, because the result of case
 // folding may be a different character length than in the source string.
 for (wchar_t c= L'\0';  c != L'\xffff';  ++c) {
    if (filter(c))  continue;
    domap (c);
    }
 filter (L'\xffff');  //just for completeness.
 return 0;
 }
 

// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\trug_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006

#if _MSC_VER == 1310
   #pragma warning( disable : 4348 )  // Microsoft's std headers don't clean compile!
#endif

#include "classics/trug.h"
#include <iostream>

using std::cout;
using std::endl;
using classics::trug;

int errorcount= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 trug<int*> pt1;
 trug<int*> pt2 (new int);
 pt1.set (new int);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 test1();
 }
 

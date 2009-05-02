// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\crc32_UT.cxx
// Revision: public build 6, shipped on 28-Nov-1999
#include "classics\crc32.h"
#include <iostream>
using std::cout;
using std::endl;
using std::hex;

int errorcount= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 cout << "Test 1 -- basic sanity test" << endl;
 static const char s1[]= "this is a test";
 static unsigned correct= 0xd1ee7ea;  //what a Zipfile shows
 unsigned crc1= classics::crc32 (s1, sizeof s1 -1);
 cout << "asm version crc32 of test string is " << hex << crc1 << endl;
 unsigned crc2= classics::crc32_alternate (s1, sizeof s1 -1);
 cout << "C++ version crc32 of test string is " << hex << crc2 << endl;
 if (crc1==crc2 && crc1==correct)  cout << "They match." << endl;
 else {
    cout << "They don't match -- problem!" << endl;
    ++errorcount;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 cout << "crc32 Unit Test" << endl;
 try {
    test1();
    return 0;
    }
 catch (...) {
    cout << "unknown error caught" << endl;
    ++errorcount;
    }
 if (errorcount)  {
    cout << errorcount << " tests failed." << endl;
    return 3;
    }
 else {
    cout << "all tests passed." << endl;
    return 0;
    }
 }
 

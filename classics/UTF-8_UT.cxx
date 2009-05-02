// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\UTF-8_UT.cxx
// Revision: public build 8, shipped on 11-July-2006
#include <iostream>
#include "classics\UTF-8.h"

using std::cout;
using std::endl;
using classics::UCS2_to_UTF8;

int errorcount= 0;

// =============================================

void testtrack (const wchar_t* input, int inlen, const char* result, int reslen, const char* id)
 {
 char dest[1024];
 int charsout, charsin;
 // destination is exact fit
 charsout= UCS2_to_UTF8 (input, inlen, &charsin, dest, reslen);
 if (charsout != reslen) {
    cout << "* failed " << id << ".1" << endl;
    ++errorcount;
    }
 if (charsin != inlen) {
    cout << "* failed " << id << ".2" << endl;
    cout << "\tgot " << charsin << ", expected " << inlen << " for input chars consumed" << endl;
    ++errorcount;
    }
 if (memcmp (dest, result, charsout)) {
    cout << "* failed " << id << ".3" << endl;
    ++errorcount;
    }
 // destination is more than enough room
 charsout= UCS2_to_UTF8 (input, inlen, &charsin, dest, 1024);
 if (charsout != reslen) {
    cout << "* failed " << id << ".4" << endl;
    ++errorcount;
    }
 if (charsin != inlen) {
    cout << "* failed " << id << ".5" << endl;
    cout << "\tgot " << charsin << ", expected " << inlen << " for input chars consumed" << endl;
    ++errorcount;
    }
 if (memcmp (dest, result, charsout)) {
    cout << "* failed " << id << ".6" << endl;
    ++errorcount;
    }
 // destination is too small
 int available_space= reslen/2;
 charsout= UCS2_to_UTF8 (input, inlen, &charsin, dest, available_space);
 if (charsout > available_space) {
    cout << "* failed " << id << ".7" << endl;
    ++errorcount;
    }
 // and do the rest of the string
 int charsin2;
 charsout += UCS2_to_UTF8 (input+charsin, inlen-charsin, &charsin2, dest+charsout, 1024-charsout);
 if (charsout != reslen) {
    cout << "* failed " << id << ".8" << endl;
    cout << "\tgot " << charsout << ", expected " << reslen << " bytes output." << endl;
    ++errorcount;
    }
 if (charsin+charsin2 != inlen) {
    cout << "* failed " << id << ".9" << endl;
    cout << "\tgot " << charsin << "+" << charsin2 << "=" << charsin+charsin2 << ", expected " << inlen << " for input chars consumed" << endl;
    ++errorcount;
    }
 if (memcmp (dest, result, charsout)) {
    cout << "* failed " << id << ".10" << endl;
    ++errorcount;
    }
 }
 
// =============================================

void test1()
 {
 cout << "test 1 - basic ASCII only" << endl;
 wchar_t input[127];
 char output[127];
 for (int loop= 0;  loop < 127;  loop++) {
    input[loop]= loop;
    output[loop]= loop;
    }
 testtrack (input, 127, output, 127, "1.1");
 wchar_t sample2_w[]= L"The quick brown fox jumps over the lazy dog.\n";
 char sample2_8[]= "The quick brown fox jumps over the lazy dog.\n";
 testtrack (sample2_w, (sizeof sample2_w)/2, sample2_8, sizeof sample2_8, "1.22");
 }
 
// =============================================

void test2()
 {
 cout << "test 2 - 2-byte encoding forms" << endl;
 wchar_t sample1_w[]= L"The result is ز, �\x39e\x6de";
 char sample1_8[]= "The result is \xc3\x98\xc2\xb2, \xc2\xa9\xce\x9e\xdb\x9e";
 testtrack (sample1_w, (sizeof sample1_w)/2, sample1_8, sizeof sample1_8, "2.1");
 }
 
// =============================================

void test3()
 {
 cout << "test 3 - 3-byte encoding forms" << endl;
 wchar_t sample1_w[]= L"ز=\x2132.";
 char sample1_8[]= "\xc3\x98\xc2\xb2=\xe2\x84\xb2.";
 testtrack (sample1_w, (sizeof sample1_w)/2, sample1_8, sizeof sample1_8, "3.1");
 wchar_t sample2_w[]= L"\xd55c\xad6d\xc5b4";  // "hangugo" example from RTF2279
 char sample2_8[]= "\xed\x95\x9c\xea\xb5\xad\xec\x96\xb4";
 testtrack (sample2_w, (sizeof sample2_w)/2-1, sample2_8, (sizeof sample2_8) -1, "3.2");
 wchar_t sample3_w[]= L"A\x2262\x0391.";  // A<NOT IDENTICAL TO><ALPHA> example from RTF2279
 char sample3_8[]= "A\xe2\x89\xa2\xce\x91\x2e";
 testtrack (sample3_w, (sizeof sample3_w)/2-1, sample3_8, (sizeof sample3_8) -1, "3.3");
 }
 
// =============================================

int main()
 {
 cout << "Testing UTF-8 / Unicode conversion routines." << endl;
 try {
    test1();
    test2();
    test3();
    }
 catch (...) {
    cout << "unexpected exception caught" << endl;
    ++errorcount;
    }
 if (errorcount)
    cout << errorcount << " tests failed." << endl;
 else  cout << "All tests passed." << endl;
 return 0;
 }
 

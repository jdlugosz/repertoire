// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\ustring_CString_UT.cxx
// Revision: public build 4, shipped on 29-Aug-98
// one of these two should be specified as a command-line option:
//   #define _UNICODE  // CString built with Unicode support
//   #define _MBCS  // CString built with multibyte-character support

#include <afx.h>  //for CString
#include "classics\ustring.h"
#include "classics\string_ios.h"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::endl;
using classics::ustring;
using classics::wFmt;

CString startmessage=
#if defined _UNICODE
   L"Testing Unicode configuration";
#elif defined _MBCS
   "Testing 8-bit configuration";
#else
   #error Configuration not specified.
#endif
int errors= 0;

////////////////////////////

std::ostream& operator<< (std::ostream& o, const CString& s)
 {
#if defined _UNICODE
 const int max= s.GetLength();
 for (int loop= 0;  loop < max;  loop++)  o<<char(s[loop]);
 return o;
#else
 return o << LPCTSTR(s);
#endif
 }

#define literal "this is a test"
#define LL(x) L##x
#define L(x) LL(x)

////////////////////////////

void test1()
 {
 cout << "test 1 -- CString converted to other types" << endl;
 CString s1 (_T(literal));
 ustring u1= s1;
 std::string s2= u1;   //convert CString to std::string
 if (s2 != literal)  {
    cout << "failed 1.1" << endl;
    errors++;
    }
 classics::string s3= u1;  //convert CString to classics::string
 if (s3 != classics::string(literal))  {
    cout << "failed 1.2" << endl;
    errors++;
    }
 std::wstring w2= u1;   //convert CString to std::wstring
 if (w2 != std::wstring(L(literal)))  {
    cout << "failed 1.3" << endl;
    errors++;
    }
 classics::wstring w3= u1;   //convert CString to classics::wstring
 if (w3 != classics::wstring(L(literal)))  {
    cout << "failed 1.4" << endl;
    errors++;
    }
 }
 
////////////////////////////

void test2()
 {
 cout << "test 2 -- other types converted to CString" << endl;
 classics::string s1 (literal);
 ustring u1= s1;
 CString cs1= u1;    //classics::string to CString
 if (cs1 != _T(literal)) {
    cout << "failed 2.1" << endl;
    ++errors;
    }
 classics::wstring w2 (L(literal));
 ustring u2= w2;
 CString cs2= u2;  //classics::wstring to CString
 if (cs2 != _T(literal)) {
    cout << "failed 2.2" << endl;
    ++errors;
    }
 std::string s3 (literal);
 ustring u3= s3;
 CString cs3= u3;    //std::string to CString
 if (cs3 != _T(literal)) {
    cout << "failed 2.3" << endl;
    ++errors;
    }
 std::wstring w4 (L(literal));
 ustring u4= w4;
 CString cs4= u4;  //std::wstring to CString
 if (cs4 != _T(literal)) {
    cout << "failed 2.4" << endl;
    ++errors;
    }
 }
 
////////////////////////////

int main()
 {
 try {
    cout << startmessage << endl;
    test1();
    test2();
    }
 catch (classics::exception& X) {
    X.show();
    ++errors;
    }
 catch (std::exception& X) {
    cout << "Exception caught: " << X.what() << endl;
    ++errors;
    }
 catch (...) {
    cout << "Unknown exception caught." << endl;
    ++errors;
    }
 if (errors)  {
    cout << "** there were " << errors << " failed cases." << endl;
    return 3;
    }
 else {
    cout << "All tests passed." << endl;
    return 0;
    }
 }


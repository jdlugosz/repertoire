// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\DocfileTest.cxx
// Revision: public build 5, shipped on 8-April-1999
#include <iostream>
#include "ratwin\COM\IStream.h"
#include "ratwin\COM\IStorage.h"
#include "classics\exception.h"
#include "classics\string_ios.h"
#include "ratwin\COM\stg.h"
#include "classics\auto_COM_ptr.h"

using ratwin::HRESULT;
using std::cout;
using std::endl;
using std::hex;
using classics::wFmt;
using ratwin::IStorage;
using ratwin::IStream;
using classics::ulong;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void show (HRESULT hr)
 {
 cout << "HRESULT is { severity:" << hr->severity_code
    << ", reserved:" << hr->reserved
    << ", facility:" << hr->facility_code
    << ", info:" << hr->information_code
    << " }" << endl;
 if (hr->information_code != 0) {
    classics::win_exception X ("testing", __FILE__, __LINE__, hr->as_number());
    X.show();
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void validate (HRESULT hr, int line)
 {
 if (hr->failed()) {
    classics::win_exception X ("testing", __FILE__, line, hr->as_number());
    wFmt(X) << L"HRESULT is { severity:" << hr->severity_code
    << L", reserved:" << hr->reserved
    << L", facility:" << hr->facility_code
    << L", info:" << hr->information_code
    << L" }" << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_file()
 {
 classics::flagword<ratwin::STGM> flags= 
    classics::flagword<ratwin::STGM>(ratwin::STGM_DIRECT) | 
    ratwin::STGM_READWRITE | ratwin::STGM_SHARE_EXCLUSIVE;
 classics::auto_COM_ptr<IStorage> root;
 HRESULT hr= ratwin::StgOpenStorage (L"foo.docfile", flags, root);
 validate (hr, __LINE__);
 classics::auto_COM_ptr<IStream> contents;
 flags= classics::flagword<ratwin::STGM>(ratwin::STGM_DIRECT) | ratwin::STGM_READWRITE | ratwin::STGM_SHARE_EXCLUSIVE;
 hr= root->OpenStream (L"CONTENTS", flags, contents);
 validate (hr, __LINE__);
 const int buflen= 80;
 char buffer[1+buflen];
 ulong actual_read;
 hr= contents->Read (buffer, buflen, &actual_read);
 validate (hr, __LINE__);
 buffer[actual_read]= '\0';
 cout << "Read:" << buffer << endl;
 hr= contents->Seek (5);
 validate (hr, __LINE__);
 hr= contents->Write ("[Testing...]", 12);
 validate (hr, __LINE__);
 
 /**/show (hr);
 // ...
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void scratchwork()
 {
 ratwin::GUID guid = __uuidof (ratwin::IStorage);
 
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 try {
    validate (ratwin::CoInitialize (ratwin::COINIT_MULTITHREADED), __LINE__);
    scratchwork();
    test_file();
    }
 catch (classics::exception& X) {
    cout << "exception caught:" << endl;
    X.show();
    }
 catch (...) {
    cout << "unknown exception caught" << endl;
    }
 ratwin::CoUninitialize();  //no way to check for errors!
 return 0;
 }


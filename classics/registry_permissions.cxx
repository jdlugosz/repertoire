// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\registry_permissions.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include "classics\registry.h"
#include "classics\exception.h"
#include "classics\ustring.h"
#include "classics\string_ios.h"
#include "ratwin\utilities.h"
using std::cout;
using std::endl;
using classics::registry_key;
using classics::ustring;
using classics::string;
using classics::wstring;
using classics::ulong;

classics::registry_key_init cleave_hive_name (const wchar_t*&s)
 {
 wchar_t* p= wcschr (s, L'\\');
 if (!p) {
    cout << "Input error:  no backslash in parameter." << endl;
    exit (2);
    }
 *p= L'\0';  // so much for const!
 const wchar_t* prefix= s;
 s= p+1;  // first char after the delimiter
 if (!_wcsicmp (prefix, L"hklm")) return classics::HKEY_LOCAL_MACHINE;
 // ...others go here...
 cout << "Input error:  do not recognise hive name " << wstring(prefix) << endl;
 exit (2);
 }



static ulong FormatMessage (void* Source, ulong errorcode, wchar_t* wbuffer, ulong maxsize)
 {
 int length;
 __try {
    length= ratwin::util::FormatMessage (0, errorcode, wbuffer, maxsize);
    while (length > 0 && iswspace(wbuffer[length-1]))  --length;
    }
 __except (1) {
     const wchar_t metaerror[]= L"<<<error looking up message>>>";
     const int messlen= (sizeof(metaerror)-1)/2;
     wcsncpy (wbuffer, metaerror, length=messlen);
    }
 wbuffer[length]= L'\0';  //??
 return length;
 }


static ustring format_message (int errorcode)
 {
 const int maxsize= 1024;
 wchar_t wbuffer[maxsize];
 int retval= FormatMessage (0, errorcode, wbuffer, maxsize);
 wstring s (wbuffer);
 return s;    //OK, got a result
 }


long test_open (registry_key& hive, const wchar_t* s, ratwin::types::HKEY& result, ratwin::registry::Rights rights)
 {
 long status= ratwin::registry::RegOpenKey (hive.get_HKEY(), s, result, rights);
 return status;
 }

long test_create (registry_key& hive, const wchar_t* s, ratwin::types::HKEY& result, ratwin::registry::Rights rights)
 {
 bool created;
 long status= ratwin::registry::RegCreateKey (hive.get_HKEY(), s, result, rights, &created);
 return status;
 }

void test_rights (registry_key& hive, const wchar_t* s, long(*func)(registry_key&, const wchar_t*, ratwin::types::HKEY&, ratwin::registry::Rights))
 {
 // ...... try each flag bit at a time, report on them.
 unsigned flag= 1;
 for (;;) {
    cout << "access rights == 0x" << std::hex << std::setw(8) << std::setfill('0') << flag << std::dec << "  ";
    try {
       ratwin::types::HKEY result;
       ratwin::registry::Rights rights= static_cast<ratwin::registry::Rights>(flag);
       long status= func (hive, s, result, rights);
       if (status == 0) {
          cout << "OK.";
          ratwin::registry::RegCloseKey(result);
          }
       else {
          cout << std::hex << status << std::dec << "  " << string(format_message (status));
          }
       }
    catch (...) {
       cout << "throws C++ exception.";
       }
    cout << endl;
    if (flag == 0)  break;
    flag <<= 1;
    }
 }


void test1 (registry_key& hive, const wchar_t* s)
 {
 try {
    cout << "exists test: ";
    cout << (hive.key_exists(s) ? "true" : "false") << endl;
    }
 catch (...) {
    cout << "throws exception." << endl;
    }
 try {
    cout << "open: ";
    registry_key k= hive.open (s);
    cout << "OK." << endl;
    }
 catch (...) {
    cout << "throws exception." << endl;
    }
 try {
    cout << "create: ";
    registry_key k= hive.create (s);
    cout << "OK." << endl;
    }
 catch (...) {
    cout << "throws exception." << endl;
    }

 }

int wmain (int argc, const wchar_t*argv[])
 {
 cout << "registry key access check" << endl;
 const wchar_t* full_keyname= argv[1];
 registry_key hive= cleave_hive_name (full_keyname);
 cout << wstring(full_keyname) << endl;
 cout << "Exploring rights for RegOpenKey" << endl;
 test_rights (hive, full_keyname, &test_open);
 cout << "Exploring rights for RegCreateKey" << endl;
 test_rights (hive, full_keyname, &test_create);
 test1 (hive, full_keyname);
 }


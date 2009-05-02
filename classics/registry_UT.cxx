// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\registry_UT.cxx
// Revision: public build 8, shipped on 11-July-2006
#include <iostream>
#include "classics\registry.h"
#include "classics\exception.h"
#include "classics\ustring.h"
#include "classics\string_ios.h"
using std::cout;
using std::endl;
using classics::registry_key;
using classics::ustring;
using classics::string;
using classics::wstring;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1()
 {
 cout << "test 1 -- simple sanity test" << endl;
 registry_key K1= classics::HKEY_CURRENT_USER.create (L"testing");
 K1.set_value ("this is a test string");
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void verify_key_creation (registry_key& Key, const ustring& subkey_name)
 {
 const int subkey_count= Key.subkey_count();
 wstring target_name= subkey_name;
 wstring name;
 for (int loop= subkey_count-1;  loop >= 0;  loop--) {
    name= Key.subkey(loop);
    if (name[0] == target_name[0])  break;  //stop when first character matches
    }
 if (loop < 0) {
    cout << "Failure: no matching key identified for " << target_name << endl;
    }
 else if (name != target_name) {
    cout << "No Match:  set \"" << target_name << "\", read \"" << name << "\"." << endl;
    }
 else
    cout << "OK" << endl;
 }
 
// =========================================================

void try_key (registry_key& Key, const ustring& subkey_name, const char* caption)
 {
 cout << caption << ' ';
 try {
    Key.create (subkey_name);
    verify_key_creation (Key, subkey_name);
    }
 catch (classics::exception& X) {
    cout << "throws exception" << endl;
    X.show();
    }
 }
 
// =========================================================

void test2()
 {
 cout << "test 2 -- subkey capabilities test" << endl;
 // >> delete old contents here
 registry_key K1= classics::HKEY_CURRENT_USER.create ("testing");
 try_key (K1, "1foobar", "normal key (control)");
 try_key (K1, "2foo bar", "key with space");
 try_key (K1, "3foo*bar", "key with * character");
 try_key (K1, "4foo?bar", "key with ? character");
 try_key (K1, "5foo\rbar", "key with control character");
 try_key (K1, "6foo" "\xe6" "bar", "key with char > 127");
 try_key (K1, "7foo" "\xC1" "bar", "key with ANSI char > 127 mapping to composite character");
 try_key (K1, "8foo" "\x83" "bar", "key with char > 127 and < 160");
 try_key (K1, L"9foo" L"\x039e" L"bar", "key with char > 256");
 cout << "functions are using " <<
    (registry_key::is_Unicode() ? "Unicode" : "ANSI")
    << " versions of API functions" << endl;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test3()
 {
 cout << "test 3 -- value test" << endl;
 registry_key K1= classics::HKEY_CURRENT_USER.create ("testing");
 const int x= 42;
 K1.set_value ("val1", ratwin::registry::REG_DWORD, &x, sizeof x);  //write the value
 ratwin::registry::value_type type;
 int y;
 int sizeread= sizeof y;  // on input: size of buffer.  on output: actual size
 K1.get_value ("val1", type, &y, sizeread);
 if (type != ratwin::registry::REG_DWORD || x!=y)
    cout << "Error verifying value val1" << endl;
 wstring string_value= L"This is a test string.";
 K1.set_value ("val2", string_value);
 wstring sout= K1.get_value_string ("val2", type);
 if (type != ratwin::registry::REG_SZ || string_value != sout) {
    cout << "Error verifying value val2:" << endl;
    cout << "\ttype is " << type << ", expected " << ratwin::registry::REG_SZ << endl;
    cout << "\tcontent is \"" << sout << "\", expected \"" << string_value << "\"." << endl;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int main()
 {
 cout << "registry Unit Test" << endl;
 try {
    test1();
    test2();
    test3();
    }
 catch (classics::exception& X) {
    cout << "caught an exception in main()" << endl;
    X.show();
    }
 catch (...) {
    cout << "unknown exception caught in main()" << endl;
    }
 return 0;
 }
 

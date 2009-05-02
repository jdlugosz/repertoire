// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\registry.cpp
// Revision: post-public build 6

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\registry.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"
#include <iostream>  //for debugging
using ratwin::types::HKEY;

STARTWRAP
namespace classics {

const char FNAME[]= __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tristate registry_key::uses_Unicode= Maybe;

registry_key HKEY_CLASSES_ROOT (ratwin::registry::HKEY_CLASSES_ROOT, false);
registry_key HKEY_CURRENT_USER (ratwin::registry::HKEY_CURRENT_USER, false);
registry_key HKEY_LOCAL_MACHINE (ratwin::registry::HKEY_LOCAL_MACHINE, false);
registry_key HKEY_USERS (ratwin::registry::HKEY_USERS, false);
registry_key HKEY_PERFORMANCE_DATA (ratwin::registry::HKEY_PERFORMANCE_DATA, false);
registry_key HKEY_CURRENT_CONFIG (ratwin::registry::HKEY_CURRENT_CONFIG, false);
registry_key HKEY_DYN_DATA (ratwin::registry::HKEY_DYN_DATA, false);

const long more_data_available= 234;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::close()
 {
 if (own) {
    long retval= ratwin::registry::RegCloseKey(key);
    if (retval) {
       win_exception X ("Classics", FNAME, __LINE__, retval);
       X += "Error closing registry key";
       throw X;
       }
    }
 own= false;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool registry_key::is_Unicode()
 {
 if (uses_Unicode == Maybe) {
    // find out for sure.
    HKEY_CLASSES_ROOT.subkey(0);  //side effect finds out.
    }
 return uses_Unicode == Yes;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int registry_key::subkey_count()
 {
 unsigned long count;
 long retval= ratwin::registry::RegQueryInfoKey (key, (char*)0, 0, &count);
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X += "Error obtaining subkey count via RegQueryInfoKey";
    throw X;
    }
 return count;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

vararray_g<wstring> registry_key::all_subkeys()
 {
 const int count= subkey_count();
 vararray_g<wstring> retval (count);
 for (int loop= 0;  loop < count;  loop++)
    retval.put_at (subkey(loop), loop);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

registry_key_init registry_key::create (const ustring& subkey)
 {
 HKEY out;
 long result;
 switch (uses_Unicode) {
    case Yes: {
       wstring s= subkey;  //16-bit string
       result= ratwin::registry::RegCreateKey (key, s.c_str(), out);
       } break;
    case Maybe: {
       //work-around for improper implementation of Unicode stub in Win95
       ratwin::util::SetLastError (0);
       wstring s= subkey;  //16-bit string
       result= ratwin::registry::RegCreateKey (key, s.c_str(), out);
       if (result==win_exception::call_not_implemented_error || (result==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          // detected lack of Unicode support
          uses_Unicode= No;
          // drop through to "No" case.
          }
       else {
          //satisfied that any result or problem is not "call not implemented".
          uses_Unicode= Yes;
          break;
          }
       } // no break here!
    case No: {
       string s= subkey;  //8-bit string
       result= ratwin::registry::RegCreateKey (key, s.c_str(), out);
       } break;
    }
 if (result) {
    win_exception X ("Classics", FNAME, __LINE__, result);
    X.add_key ("name", subkey);
    X += "Error creating a registry key";
    throw X;
    }
 return out;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

registry_key_init registry_key::open (const ustring& subkey)
 {
 // >> note: not minimizing the desired rights yet.
 HKEY out;
 long result;
 switch (uses_Unicode) {
    case Yes: {
       wstring s= subkey;  //16-bit string
       result= ratwin::registry::RegOpenKey (key, s.c_str(), out);
       } break;
    case Maybe: {
       //work-around for improper implementation of Unicode stub in Win95
       ratwin::util::SetLastError (0);
       wstring s= subkey;  //16-bit string
       result= ratwin::registry::RegOpenKey (key, s.c_str(), out);
       if (result==win_exception::call_not_implemented_error || (result==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          // detected lack of Unicode support
          uses_Unicode= No;
          // drop through to "No" case.
          }
       else {
          //satisfied that any result or problem is not "call not implemented".
          uses_Unicode= Yes;
          break;
          }
       } // no break here!
    case No: {
       string s= subkey;  //8-bit string
       result= ratwin::registry::RegOpenKey (key, s.c_str(), out);
       } break;
    }
 if (result) {
    win_exception X ("Classics", FNAME, __LINE__, result);
    X += "Error opening a registry key";
    throw X;
    }
 return out;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool registry_key::key_exists (const ustring& keyname) const
 {
 HKEY out;
 long result;
 switch (uses_Unicode) {
    case Yes: {
       wstring s= keyname;  //16-bit string
       result= ratwin::registry::RegOpenKey (key, s.c_str(), out, ratwin::registry::KEY_QUERY_VALUE);
       } break;
    case Maybe: {
       //work-around for improper implementation of Unicode stub in Win95
       ratwin::util::SetLastError (0);
       wstring s= keyname;  //16-bit string
       result= ratwin::registry::RegOpenKey (out, s.c_str(), out, ratwin::registry::KEY_QUERY_VALUE);
       if (result==win_exception::call_not_implemented_error || (result==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          // detected lack of Unicode support
          uses_Unicode= No;
          // drop through to "No" case.
          }
       else {
          //satisfied that any result or problem is not "call not implemented".
          uses_Unicode= Yes;
          break;
          }
       } // no break here!
    case No: {
       string s= keyname;  //8-bit string
       result= ratwin::registry::RegOpenKey (key, s.c_str(), out, ratwin::registry::KEY_QUERY_VALUE);
       } break;
    }
 if (result) return false;  //could not open the key, so it doesn't exist (or I can't read it)
 else {
    ratwin::registry::RegCloseKey(out);
    return true;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool registry_key::value_exists (const ustring& valname) const
 {
 long result;
 ratwin::registry::value_type type;
 switch (uses_Unicode) {
    case Yes: {
       wstring s= valname;  //16-bit string
       result= ratwin::registry::RegQueryValue (key, s.c_str(), type, 0, 0);
       } break;
    case Maybe: {
       //work-around for improper implementation of Unicode stub in Win95
       ratwin::util::SetLastError (0);
       wstring s= valname;  //16-bit string
       result= ratwin::registry::RegQueryValue (key, s.c_str(), type, 0, 0);
       if (result==win_exception::call_not_implemented_error || (result==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          // detected lack of Unicode support
          uses_Unicode= No;
          // drop through to "No" case.
          }
       else {
          //satisfied that any result or problem is not "call not implemented".
          uses_Unicode= Yes;
          break;
          }
       } // no break here!
    case No: {
       string s= valname;  //8-bit string
       result= ratwin::registry::RegQueryValue (key, s.c_str(), type, 0, 0);
       } break;
    }
 return result==0;  //false if I didn't successfully read it.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
generic_string<T> subkey_helper (ratwin::types::HKEY key, int index)
 {
 // RegEnumKey will complain if the buffer is not long enough, but it does not tell me
 // how long it needs to be!
 int bufsize= 512;
 retry:
 int destsize=bufsize;  //in:actual buffer size, out:required size not including terminating nul.
 generic_string<T> result (destsize);
 T* dest= result.get_buffer();
 long retval= ratwin::registry::RegEnumKey (key, index, dest, destsize);
 if (retval == more_data_available) {
    bufsize *= 2;  //make the buffer larger
    goto retry;  //and start over
    }
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X += "Error obtaining subkey name with RegEnumKey";
    throw X;
    }
 result.truncate(destsize);
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring registry_key::subkey (int index)
 {
 switch (uses_Unicode) {
    case Yes:
       return subkey_helper<wchar_t> (key, index);
    case No:
       return subkey_helper<char> (key, index);
    default:
    case Maybe: {
       int destsize=512;
       wstring result (destsize);
       wchar_t* dest= result.get_buffer();
       ratwin::util::SetLastError (0);       
       long retval= ratwin::registry::RegEnumKey (key, index, dest, destsize);
       if (retval==win_exception::call_not_implemented_error || (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          uses_Unicode= No;
          return subkey_helper<char>(key, index);
          }
       uses_Unicode= Yes;
       if (retval != 0)  return subkey_helper<wchar_t>(key, index);
       result.truncate(destsize);
       return result;
       }       
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::set_value (const ustring& valname_u, ratwin::registry::value_type type, const void* data, int datasize)
 {
 long retval;
 switch (uses_Unicode) {
    case Maybe: {
       ratwin::util::SetLastError(0);
       wstring valname= valname_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data, datasize);
       if (retval==win_exception::call_not_implemented_error || (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          uses_Unicode= No;
          // fall through to No case
          }
       else {
          uses_Unicode= Yes;
          break;
          }
       }
    case No: {
       string valname= valname_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data, datasize);
       } break;
    case Yes: {
       wstring valname= valname_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data, datasize);
       } break;
    }
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X += "Error setting value with RegSetValue";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::set_value (const ustring& valname_u, const ustring& data_u, ratwin::registry::value_type type)
 {
 long retval;
 switch (uses_Unicode) {
    case Maybe: {
       ratwin::util::SetLastError(0);
       wstring valname= valname_u;
       const wstring data= data_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data.get_buffer(), 2*data.elcount());
       if (retval==win_exception::call_not_implemented_error || (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          uses_Unicode= No;
          // fall through to No case
          }
       else {
          uses_Unicode= Yes;
          break;
          }
       }
    case No: {
       string valname= valname_u;
       const string data= data_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data.c_str(), data.elcount());
       // note:  Win95 appears to delimit the string by a terminating '\0' and ignores the length argument.
       } break;
    case Yes: {
       wstring valname= valname_u;
       const wstring data= data_u;
       retval= ratwin::registry::RegSetValue (key, valname.c_str(), type, data.get_buffer(), 2*data.elcount());
       } break;
    }
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X += "Error setting value with RegSetValue";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::set_value (const ustring& value_u)
 {
 set_value ("", value_u);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

registry_key_init registry_key::set_subkey_and_value (const ustring& subkey, const ustring& value, ratwin::registry::value_type type)
 {
 registry_key K2= create (subkey);
 K2.set_value ("", value, type);
 return K2.pass_off();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
int remove_key_helper (registry_key& key, const ustring& subkey_u)
 {
 int errorcount= 0;
 generic_string<T> subkey= subkey_u;
 // first delete subkeys, recursively
 {  //contain scope of K2
 registry_key K2= key.open (subkey);
 for (int child= K2.subkey_count()-1;  child >= 0;  --child) {
    errorcount += remove_key_helper<T> (K2, K2.subkey(child));
    }
 }
 long retval= ratwin::registry::RegDeleteKey (key.get_HKEY(), subkey.c_str());
 if (retval)  ++errorcount;
 return errorcount;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int registry_key::remove (const ustring& subkey)
 {
 return is_Unicode() ?
    remove_key_helper<wchar_t> (*this, subkey)
   : remove_key_helper<char> (*this, subkey);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::remove_value (const ustring& valname)
 {
 long retval;
 switch (uses_Unicode) {
    case Maybe: {
       ratwin::util::SetLastError(0);
       wstring name= valname;
       retval= ratwin::registry::RegDeleteValue (key, name.c_str());
       if (retval==win_exception::call_not_implemented_error || (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          uses_Unicode= No;
          // fall through to No case
          }
       else {
          uses_Unicode= Yes;
          break;
          }
       }
    case No: {
       string name= valname;
       retval= ratwin::registry::RegDeleteValue (key, name.c_str());
       } break;
    case Yes: {
       wstring name= valname;
       retval= ratwin::registry::RegDeleteValue (key, name.c_str());
       } break;
    }
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X += "Error removing registry value";
    throw X;
    }
 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void registry_key::get_value (const ustring& valname, ratwin::registry::value_type& type, void* data, int& datasize) const
 {
 long retval;
 switch (uses_Unicode) {
    case Maybe: {
       ratwin::util::SetLastError(0);
       wstring name= valname;
       retval= ratwin::registry::RegQueryValue (key, name.c_str(), type, data, &datasize);
       if (retval==win_exception::call_not_implemented_error || (retval==0 && ratwin::util::GetLastError()==win_exception::call_not_implemented_error)) {
          uses_Unicode= No;
          // fall through to No case
          }
       else {
          uses_Unicode= Yes;
          break;
          }
       }
    case No: {
       const string name= valname;
       retval= ratwin::registry::RegQueryValue (key, name.c_str(), type, data, &datasize);
       } break;
    case Yes: {
       const wstring name= valname;
       retval= ratwin::registry::RegQueryValue (key, name.c_str(), type, data, &datasize);
       } break;
    }
 if (retval) {
    win_exception X ("Classics", FNAME, __LINE__, retval);
    X.add_key ("name", valname);
    X += "Error accessing registry value";
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int registry_key::get_value_int (const ustring& valname) const
 {
 ratwin::registry::value_type type;
 int value;
 int size= sizeof value;
 get_value (valname, type, &value, size);
 if (type != ratwin::registry::REG_DWORD || size != sizeof value) {
    classics::exception X ("Classics", "Error reading int from registry", FNAME, __LINE__);
    X.add_key ("name", valname);
    X += "Not a REG_DWORD or incorrect length.";
    throw X;
    }
 return value;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring registry_key::get_value_string (const ustring& valname, ratwin::registry::value_type& type) const
 {
 int size;
 get_value (valname, type, 0, size);
 if (type != ratwin::registry::REG_SZ && type != ratwin::registry::REG_EXPAND_SZ && type != ratwin::registry::REG_MULTI_SZ) {
    classics::exception X ("Classics", "Bad value type in registry", FNAME, __LINE__);
    X.add_key ("name", valname);
    X += "Not a string type";
    throw X;
    }
 if (uses_Unicode == Yes) {
    wstring s (size/2);  //size is in bytes, parameter is in characters
    wchar_t* buf= s.get_buffer();
    get_value (valname, type, buf, size);
    size/=2;  //now working in chars.
    while (size>0 && buf[size-1]==L'\0')  --size;  //strip off any trailing nul's.
    s.truncate (size);
    return s;
    }
 else { // must be ANSI
    string s (size);
    char* buf= s.get_buffer();
    get_value (valname, type, buf, size);
    while (size>0 && buf[size-1]=='\0')  --size;  //strip off any trailing nul's.
    s.truncate (size);
    return s;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}  //end of namespace
ENDWRAP


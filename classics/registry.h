// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\registry.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "classics\ustring.h"
#include "ratwin\registry.h"
#include "classics\misc_types.h"

STARTWRAP
namespace classics {

class registry_key_init {
protected:
   bool own;
   bool fresh;
   ratwin::types::HKEY key;
public:
   registry_key_init (ratwin::types::HKEY key, bool own=true) : key(key), own(own), fresh(false) {}
   void zap() { own=false; }
   ratwin::types::HKEY get_HKEY() const { return key; }
   };

class registry_key : public registry_key_init {
   CLASSICS_EXPORT static tristate uses_Unicode;
   registry_key (const registry_key&);  //not defined
   void operator= (const registry_key&);  //not defined
public:
   registry_key() : registry_key_init(0,false) {}
   registry_key (ratwin::types::HKEY key, bool own) : registry_key_init(key,own) {}
   registry_key (registry_key_init& other) : registry_key_init(other) { other.zap(); }
   void operator= (registry_key_init& other)
      { registry_key_init::operator=(other);  other.zap();  }
   ~registry_key()  { close(); }
   CLASSICS_EXPORT void close();
   registry_key_init pass_off() { registry_key_init retval(*this); zap(); return retval; }
   CLASSICS_EXPORT registry_key_init open (const ustring& subkey);
   CLASSICS_EXPORT bool key_exists (const ustring& keyname) const;
   CLASSICS_EXPORT registry_key_init create (const ustring& subkey);
   CLASSICS_EXPORT int remove (const ustring& subkey);  //returns number of errors
   CLASSICS_EXPORT bool value_exists (const ustring& valname) const;
   CLASSICS_EXPORT void set_value (const ustring& value);  //unnamed value
   CLASSICS_EXPORT void set_value (const ustring& valname, ratwin::registry::value_type, const void* data, int datasize);  //general form
   CLASSICS_EXPORT void set_value (const ustring& valname, const ustring& data, ratwin::registry::value_type=ratwin::registry::REG_SZ);  //strings only
   void set_value (const ustring& valname, int value)
    {  set_value (valname, ratwin::registry::REG_DWORD, &value, sizeof value);  }
   CLASSICS_EXPORT void get_value (const ustring& valname, ratwin::registry::value_type&, void* data, int& datasize) const;  //general form
   CLASSICS_EXPORT ustring get_value_string (const ustring& valname, ratwin::registry::value_type&) const;
   CLASSICS_EXPORT int get_value_int (const ustring& valname) const;
   CLASSICS_EXPORT void remove_value (const ustring& valname);
   CLASSICS_EXPORT void remove_value(); //unnamed value
   CLASSICS_EXPORT registry_key_init set_subkey_and_value (const ustring& subkey, const ustring& value, ratwin::registry::value_type= ratwin::registry::REG_SZ);
   CLASSICS_EXPORT ustring subkey (int index);  //simple enumeration
   CLASSICS_EXPORT int subkey_count();
   CLASSICS_EXPORT vararray_g<wstring> all_subkeys();
   CLASSICS_EXPORT static bool is_Unicode();
   };

// >> need to set Unicode flag back to unknown for testing autoswitch code

extern registry_key CLASSICS_EXPORT HKEY_CLASSES_ROOT;
extern registry_key CLASSICS_EXPORT HKEY_CURRENT_USER;
extern registry_key CLASSICS_EXPORT HKEY_LOCAL_MACHINE;
extern registry_key CLASSICS_EXPORT HKEY_USERS;
extern registry_key CLASSICS_EXPORT HKEY_PERFORMANCE_DATA;
extern registry_key CLASSICS_EXPORT HKEY_CURRENT_CONFIG;
extern registry_key CLASSICS_EXPORT HKEY_DYN_DATA;


}  //end of namespace
ENDWRAP


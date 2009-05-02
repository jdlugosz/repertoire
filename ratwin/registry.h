// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\registry.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\registry.h contains globals.
#endif


#include "ratwin\base.h"
#include "classics\flagword.h"

// DLL imports "cloaked" for overloading
extern "C" {

__declspec(dllimport) long __stdcall RegOpenKeyExA (Dlugosz::ratwin::arg::arg32, const char*, unsigned long, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall RegOpenKeyExW (Dlugosz::ratwin::arg::arg32, const wchar_t*, unsigned long, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall RegEnumKeyExA (Dlugosz::ratwin::arg::arg32, unsigned long, const char*, int*, void*, const char*, int*, void*);
__declspec(dllimport) long __stdcall RegEnumKeyExW (Dlugosz::ratwin::arg::arg32, unsigned long, const wchar_t*, int*, void*, const wchar_t*, int*, void*);
__declspec(dllimport) long __stdcall RegCloseKey (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall RegDeleteKeyA (Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) long __stdcall RegDeleteKeyW (Dlugosz::ratwin::arg::arg32, const wchar_t*);
__declspec(dllimport) long __stdcall RegDeleteValueA (Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) long __stdcall RegDeleteValueW (Dlugosz::ratwin::arg::arg32, const wchar_t*);
__declspec(dllimport) long __stdcall RegCreateKeyExA (Dlugosz::ratwin::arg::arg32, const char*, int, const char*, unsigned long, unsigned long, void*, Dlugosz::ratwin::arg::arg32, unsigned long*);
__declspec(dllimport) long __stdcall RegCreateKeyExW (Dlugosz::ratwin::arg::arg32, const wchar_t*, int, const wchar_t*, unsigned long, unsigned long, void*, Dlugosz::ratwin::arg::arg32, unsigned long*);
__declspec(dllimport) long __stdcall RegSetValueExA (Dlugosz::ratwin::arg::arg32, const char*, int, unsigned long, const void*, unsigned long);
__declspec(dllimport) long __stdcall RegSetValueExW (Dlugosz::ratwin::arg::arg32, const wchar_t*, int, unsigned long, const void*, unsigned long);
__declspec(dllimport) long __stdcall RegQueryInfoKeyA (Dlugosz::ratwin::arg::arg32 hKey, char* lpClass, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, __int64*);
__declspec(dllimport) long __stdcall RegQueryInfoKeyW (Dlugosz::ratwin::arg::arg32 hKey, wchar_t* lpClass, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, unsigned long*, __int64*);
__declspec(dllimport) long __stdcall RegQueryValueExA (Dlugosz::ratwin::arg::arg32 hKey, const char*, void*, int*, void*, int*);
__declspec(dllimport) long __stdcall RegQueryValueExW (Dlugosz::ratwin::arg::arg32 hKey, const wchar_t*, void*, int*, void*, int*);
}


STARTWRAP
namespace ratwin {
namespace registry {

const types::HKEY HKEY_CLASSES_ROOT= reinterpret_cast<types::HKEY>(0x80000000);
const types::HKEY HKEY_CURRENT_USER= reinterpret_cast<types::HKEY>(0x80000001);
const types::HKEY HKEY_LOCAL_MACHINE= reinterpret_cast<types::HKEY>(0x80000002);
const types::HKEY HKEY_USERS= reinterpret_cast<types::HKEY>(0x80000003);
const types::HKEY HKEY_PERFORMANCE_DATA= reinterpret_cast<types::HKEY>(0x80000004);
const types::HKEY HKEY_CURRENT_CONFIG= reinterpret_cast<types::HKEY>(0x80000005);
const types::HKEY HKEY_DYN_DATA= reinterpret_cast<types::HKEY>(0x80000006);

enum Rights {
   KEY_QUERY_VALUE= 0x0001,
   KEY_SET_VALUE= 0x0002,
   KEY_CREATE_SUB_KEY= 0x0004,
   KEY_ENUMERATE_SUB_KEYS= 0x0008,
   KEY_NOTIFY= 0x0010,
   KEY_CREATE_LINK= 0x0020,
   // pre-made composites
   KEY_ALL_ACCESS= 0x000F003F   //note: "enumerate subkeys" included, not in Windows.h though documented in SDK.
   };

inline
long RegOpenKey (types::HKEY parent, const char* subkey, types::HKEY& result)
 {
 return ::RegOpenKeyExA (reinterpret_cast<arg::arg32>(parent), subkey, 0, KEY_ALL_ACCESS, reinterpret_cast<arg::arg32>(&result));
 }
 
inline
long RegOpenKey (types::HKEY parent, const wchar_t* subkey, types::HKEY& result)
 {
 return ::RegOpenKeyExW (reinterpret_cast<arg::arg32>(parent), subkey, 0, KEY_ALL_ACCESS, reinterpret_cast<arg::arg32>(&result));
 }

inline
long RegOpenKey (types::HKEY parent, const char* subkey, types::HKEY& result, classics::flagword<Rights> rights)
 {
 return ::RegOpenKeyExA (reinterpret_cast<arg::arg32>(parent), subkey, 0, rights.validdata(), reinterpret_cast<arg::arg32>(&result));
 }
 
inline
long RegOpenKey (types::HKEY parent, const wchar_t* subkey, types::HKEY& result, classics::flagword<Rights> rights)
 {
 return ::RegOpenKeyExW (reinterpret_cast<arg::arg32>(parent), subkey, 0, rights.validdata(), reinterpret_cast<arg::arg32>(&result));
 }

inline
long RegCloseKey (types::HKEY key)
 {
 return ::RegCloseKey (reinterpret_cast<arg::arg32>(key));
 }

inline 
long RegEnumKey (types::HKEY parent, int index, char* dest, int& destsize)
 {
 __int64 time;
 return ::RegEnumKeyExA (reinterpret_cast<arg::arg32>(parent), index, dest, &destsize, 0,0,0,&time);
 }

inline 
long RegEnumKey (types::HKEY parent, int index, wchar_t* dest, int& destsize)
 {
 __int64 time;
 return ::RegEnumKeyExW (reinterpret_cast<arg::arg32>(parent), index, dest, &destsize, 0,0,0,&time);
 }

inline long RegDeleteKey (types::HKEY parent, const char* subkey)
 {
 return ::RegDeleteKeyA (reinterpret_cast<arg::arg32>(parent), subkey);
 }

inline long RegDeleteKey (types::HKEY parent, const wchar_t* subkey)
 {
 return ::RegDeleteKeyW (reinterpret_cast<arg::arg32>(parent), subkey);
 }

inline long RegDeleteValue (types::HKEY parent, const char* subValue)
 {
 return ::RegDeleteValueA (reinterpret_cast<arg::arg32>(parent), subValue);
 }

inline long RegDeleteValue (types::HKEY parent, const wchar_t* subValue)
 {
 return ::RegDeleteValueW (reinterpret_cast<arg::arg32>(parent), subValue);
 }

inline long RegCreateKey (types::HKEY parent, const char* subkey, types::HKEY& /*out*/ result, bool* created= 0)
 {
 unsigned long disposition; 
 long retval= ::RegCreateKeyExA (reinterpret_cast<arg::arg32>(parent), subkey,
    0, //reserved, is always zero
    0, //class name, default to zero for unused
    0, //REG_OPTION_NON_VOLATILE by default (and only one available under Win98)
    KEY_ALL_ACCESS,  //desired rights
    0, //security absent
    reinterpret_cast<arg::arg32>(&result),
    &disposition);
 if (created)  *created= 1==disposition;  //1:created, 2:opened existing
 return retval;
 }
 
inline long RegCreateKey (types::HKEY parent, const wchar_t* subkey, types::HKEY& /*out*/ result, bool* created= 0)
 {
 unsigned long disposition; 
 long retval= ::RegCreateKeyExW (reinterpret_cast<arg::arg32>(parent), subkey,
    0, //reserved, is always zero
    0, //class name, default to zero for unused
    0, //REG_OPTION_NON_VOLATILE by default (and only one available under Win98)
    KEY_ALL_ACCESS,  //desired rights
    0, //security absent
    reinterpret_cast<arg::arg32>(&result),
    &disposition);
 if (created)  *created= 1==disposition;  // 1:created, 2:opened existing
 return retval;
 }

enum value_type {
   REG_NONE= 0,  // No value type
   REG_SZ= 1,  // Unicode nul terminated string
   REG_EXPAND_SZ= 2,  // Unicode nul terminated string (with environment variable references)
   REG_BINARY= 3,  // Free form binary
   REG_DWORD= 4,  // 32-bit number
   REG_DWORD_LITTLE_ENDIAN= 4,  // 32-bit number (same as REG_DWORD)
   REG_DWORD_BIG_ENDIAN= 5,  // 32-bit number
   REG_LINK= 6,  // Symbolic Link (unicode)
   REG_MULTI_SZ= 7,  // Multiple Unicode strings
   REG_RESOURCE_LIST= 8,  // Resource list in the resource map
   REG_FULL_RESOURCE_DESCRIPTOR= 9,  // Resource list in the hardware description
   REG_RESOURCE_REQUIREMENTS_LIST= 10,
   };

inline long RegSetValue (types::HKEY parent, const char* valname, value_type valtype, const void* data, int size)
 {
 return ::RegSetValueExA (reinterpret_cast<arg::arg32>(parent), valname, 0, valtype, data, size);
 }
 
inline long RegSetValue (types::HKEY parent, const wchar_t* valname, value_type valtype, const void* data, int size)
 {
 return ::RegSetValueExW (reinterpret_cast<arg::arg32>(parent), valname, 0, valtype, data, size);
 }

inline long RegQueryInfoKey (
   types::HKEY hKey,
   char* lpClass,
   unsigned long* lpcbClass=0,
   unsigned long* lpcSubKeys=0,
   unsigned long* lpcbMaxSubKeyLen=0,
   unsigned long* lpcbMaxClassLen=0,
   unsigned long* lpcValues=0,
   unsigned long* lpcbMaxValueNameLen=0,
   unsigned long* lpcbMaxValueLen=0,
   unsigned long* lpcbSecurityDescriptor=0,
   __int64* lpftLastWriteTime=0)
 {
 return ::RegQueryInfoKeyA (reinterpret_cast<arg::arg32>(hKey), lpClass, lpcbClass, 0/*reserved*/,
 lpcSubKeys,lpcbMaxSubKeyLen,lpcbMaxClassLen,lpcValues,
 lpcbMaxValueNameLen,lpcbMaxValueLen,lpcbSecurityDescriptor,lpftLastWriteTime);
 }

inline long RegQueryInfoKey (
   types::HKEY hKey,
   wchar_t* lpClass,
   unsigned long* lpcbClass=0,
   unsigned long* lpcSubKeys=0,
   unsigned long* lpcbMaxSubKeyLen=0,
   unsigned long* lpcbMaxClassLen=0,
   unsigned long* lpcValues=0,
   unsigned long* lpcbMaxValueNameLen=0,
   unsigned long* lpcbMaxValueLen=0,
   unsigned long* lpcbSecurityDescriptor=0,
   __int64* lpftLastWriteTime=0)
 {
 return ::RegQueryInfoKeyW (reinterpret_cast<arg::arg32>(hKey), lpClass, lpcbClass, 0/*reserved*/,lpcSubKeys,lpcbMaxSubKeyLen,lpcbMaxClassLen,lpcValues,lpcbMaxValueNameLen,lpcbMaxValueLen,lpcbSecurityDescriptor,lpftLastWriteTime);
 }

inline
long RegQueryValue (
   types::HKEY hKey,
   const char* name,
   value_type& type,
   void* buffer,
   int* bufsize)
 {
 int valtype;
 long retval= ::RegQueryValueExA (reinterpret_cast<arg::arg32>(hKey), name, 0, &valtype, buffer, bufsize);
 type= value_type(valtype);
 return retval;
 }


inline
long RegQueryValue (
   types::HKEY hKey,
   const wchar_t* name,
   value_type& type,
   void* buffer,
   int* bufsize)
 {
 int valtype;
 long retval= ::RegQueryValueExW (reinterpret_cast<arg::arg32>(hKey), name, 0, &valtype, buffer, bufsize);
 type= value_type(valtype);
 return retval;
 }

}} // end namespace
ENDWRAP


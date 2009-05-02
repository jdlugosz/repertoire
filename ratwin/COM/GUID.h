// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) int __stdcall StringFromGUID2 (Dlugosz::ratwin::arg::carg32, wchar_t*, int);
__declspec(dllimport) unsigned __stdcall CoCreateGuid (Dlugosz::ratwin::arg::arg32);
}

// GLOBAL because the compiler has built-in awareness.
// specifically, the intrinsic __guid operator returns a ::_GUID value.
#ifndef GUID_DEFINED
#define GUID_DEFINED
struct _GUID {
   unsigned __int32      time_low;
   unsigned __int16      time_mid;
   unsigned __int16      time_hi : 12;  //low bits
   unsigned __int16      version : 4;  //high bits
   unsigned __int8       clock_seq_hi : 6;  //low bits
   unsigned __int8       reserved : 2; // 2 or 3, depending
   unsigned __int8       clock_seq_low;
   unsigned __int8       node[6];
   inline int to_string (wchar_t* dest, int destsize) const;  //returns chars used including terminating NUL.
   inline void generate();
   };

inline
void _GUID::generate()
 {
 CoCreateGuid (reinterpret_cast<Dlugosz::ratwin::arg::arg32>(this));
 }

inline bool inline_eq (const _GUID& left, const _GUID& right)
 {
 struct S { __int64 a,b; };
 const S* L= reinterpret_cast<const S*>(&left);
 const S* R= reinterpret_cast<const S*>(&right);
 return L->a == R->a && L->b == R->b;
 }

RATWIN_EXPORT bool operator== (const _GUID& left, const _GUID& right);  //not inline

inline bool operator!= (const _GUID& left, const _GUID& right)
 {
 return !(left==right);
 }


inline int _GUID::to_string (wchar_t* dest, int destsize) const
// needs 32 chars for digits, 6 for punctuation, and 1 for terminating NUL.  39 Total.
 {
 return ::StringFromGUID2 (reinterpret_cast<Dlugosz::ratwin::arg::carg32>(this), dest, destsize);
 }

#endif /* GUID_DEFINED */

STARTWRAP
namespace ratwin {

typedef _GUID GUID;
typedef GUID IID;
typedef GUID CLSID;


} // end ratwin namespace
ENDWRAP



// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#include "ratwin\base.h"



// GLOBAL because the compiler has built-in awareness.
// specifically, the intrinsic __guid operator returns a ::_GUID value.
#ifndef GUID_DEFINED
#define GUID_DEFINED
#if 0
// This is the REAL structure of a GUID.  MS changed it, not showing
// the bit-fields.  Because ATL and other code also uses aggregate
// initializers rather than a MK_GUID macro or the compiler intrinsic,
// I'm using MS's definition.  The original one is preserved here for
// those who really want to know the details.
struct _GUID {
   unsigned __int32      time_low;
   unsigned __int16      time_mid;
   unsigned __int16      time_hi : 12;  //low bits
   unsigned __int16      version : 4;  //high bits
   unsigned __int8       clock_seq_hi : 6;  //low bits
   unsigned __int8       reserved : 2; // 2 or 3, depending
   unsigned __int8       clock_seq_low;
   unsigned __int8       node[6];
};
#else
// changed to this form May 2002, will be in PB7.
struct _GUID {
   unsigned __int32      time_low;
   unsigned __int16      time_mid;
   unsigned __int16      time_hi_and_version;
   unsigned __int8       clock_seq_hi_and_reserved;
   unsigned __int8       clock_seq_low;
   unsigned __int8       node[6];
};
#endif

#endif /* GUID_DEFINED */


STARTWRAP
namespace ratwin {

namespace Win32API {
int __stdcall StringFromGUID2 (const _GUID*, wchar_t*, int);
unsigned __stdcall CoCreateGuid (_GUID*);
}  // end namespace Win32API


class GUID : public _GUID {
public:
   GUID() {}  // does nothing.
   GUID (const _GUID& x) : _GUID(x) {}  // implicit conversion
   inline int to_string (wchar_t* dest, int destsize) const;  //returns chars used including terminating NUL.
   inline void generate();
   inline bool inline_eq (const GUID& right) const {
      struct S { __int64 a,b; };
      const S* L= reinterpret_cast<const S*>(this);
      const S* R= reinterpret_cast<const S*>(&right);
      return L->a == R->a && L->b == R->b;
      }

   };

RATWIN_EXPORT bool operator== (const GUID& left, const GUID& right);  //not inline

inline bool operator!= (const GUID& left, const GUID& right)
 {
 return !(left==right);
 }

inline
void GUID::generate()
 {
 Win32API::CoCreateGuid (this);
 }

inline int GUID::to_string (wchar_t* dest, int destsize) const
// needs 32 chars for digits, 6 for punctuation, and 1 for terminating NUL.  39 Total.
 {
 return Win32API::StringFromGUID2 (this, dest, destsize);
 }


typedef GUID IID;
typedef GUID CLSID;


} // end ratwin namespace
ENDWRAP

typedef _GUID GUID;
   // note this is the primitive one, without functions.
   // This is global for compatibility with <WINDOWS.H>
   

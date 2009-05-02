// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\charset.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined RATWIN_CHARSET_INCLUDED
#define RATWIN_CHARSET_INCLUDED

#include "ratwin\base.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) int __stdcall CharToOemBuffW (Dlugosz::ratwin::arg::carg32, char*, unsigned long);
__declspec(dllimport) int __stdcall MultiByteToWideChar (unsigned, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) int __stdcall GetStringTypeW (unsigned long, Dlugosz::ratwin::arg::carg32, int, unsigned short*);
__declspec(dllimport) int __stdcall WideCharToMultiByte (unsigned, unsigned long, Dlugosz::ratwin::arg::carg32, int, char*, int, const char*, int*);
__declspec(dllimport) unsigned long __stdcall LCMapStringW (unsigned long, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) unsigned long __stdcall LCMapStringA (unsigned long, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) unsigned long __stdcall GetThreadLocale();
}


STARTWRAP
namespace ratwin {

inline
void CharToOemBuff (const wchar_t* src, char* dest, int len)
 {
 // As documented, return value is meaningless.
 ::CharToOemBuffW (reinterpret_cast<arg::carg32>(src), dest, len);
 }

enum CodePage_t {
   CP_ACP= 0,  // ANSI code page
   CP_OEMCP= 1,  //OEM code page
   CP_MACCP= 2,  //MAC code page
   CP_SYMBOL= 42,  // Docs say 42, WINNLS.H says Czech Republic for this value.  I don't know.
   CP_THREAD_ACP= 3,  //Thread's ANSI code page
   CP_UTF7= 65000,  //UTF-7 translation
   CP_UTF8= 65001  //UTF-8 translation
   // can also use the value of any installed code page here.
   };

enum WideCharFlags_t {
   MB_PRECOMPOSED= 1,
   MB_COMPOSITE= 2,
   MB_USEGLYPHCHARS= 4,
   MB_ERR_INVALID_CHARS= 8,
   WC_COMPOSITECHECK= 0x200,     // convert composite to precomposed
      // these three valid only in combination with the previous.
      WC_DISCARDNS= 0x010,     // discard non-spacing chars
      WC_SEPCHARS= 0x020,     // generate separate chars
      WC_DEFAULTCHAR= 0x040,     // replace w/ default char
   };

inline
int MultiByteToWideChar (CodePage_t cp, unsigned flags, const char* src, int srclen, wchar_t* dest, int destsize/*in chars*/)
 {
 return ::MultiByteToWideChar (cp, flags, reinterpret_cast<arg::carg32>(src), srclen, reinterpret_cast<arg::arg32>(dest), destsize);
 }

inline
int MultiByteToWideChar (const char* src, int srclen, wchar_t* dest, int destlen)
 {
 return ::MultiByteToWideChar (/*CP_THREAD_ACP*/CP_ACP, MB_COMPOSITE, reinterpret_cast<arg::carg32>(src), srclen, reinterpret_cast<arg::arg32>(dest), destlen);
 }

inline
int WideCharToMultiByte (const wchar_t* src, int srclen, char* dest, int destlen)
 {
 return ::WideCharToMultiByte (/*CP_THREAD_ACP*/CP_ACP, WC_COMPOSITECHECK, reinterpret_cast<arg::carg32>(src), srclen, dest, destlen, 0,0);
 }
 
enum string_info_t {
   CT_CTYPE1= 1,
   CT_CTYPE2= 2,
   CT_CTYPE3= 4
   };

enum string_type_result_t {
   C1_UPPER= 0x0001,
   C1_LOWER= 0x0002,
   C1_DIGIT= 0x0004,
   C1_SPACE= 0x0008,
   C1_PUNCT= 0x0010,
   C1_CNTRL= 0x0020,
   C1_BLANK= 0x0040,
   C1_XDIGIT= 0x0080,
   C1_ALPHA= 0x0100
   };

inline
bool GetStringType (string_info_t string_info, const wchar_t* src, int len, ushort* dest)
 {
 return ::GetStringTypeW (string_info, reinterpret_cast<arg::carg32>(src), len, dest);
 }

enum LCMAP_flags {
   NORM_IGNORECASE=         0x00000001,  // ignore case
   NORM_IGNORENONSPACE=     0x00000002,  // ignore nonspacing chars
   NORM_IGNORESYMBOLS=      0x00000004,  // ignore symbols
   LCMAP_LOWERCASE=         0x00000100,  // lower case letters
   LCMAP_UPPERCASE=         0x00000200,  // upper case letters
   LCMAP_SORTKEY=           0x00000400,  // WC sort key (normalize)
   LCMAP_BYTEREV=           0x00000800,  // byte reversal
   SORT_STRINGSORT=         0x00001000,  // use string sort method (as opposed to word-sort method)
   NORM_IGNOREKANATYPE=     0x00010000,  // ignore kanatype
   NORM_IGNOREWIDTH=        0x00020000,  // ignore width
   LCMAP_HIRAGANA=          0x00100000,  // map katakana to hiragana
   LCMAP_KATAKANA=          0x00200000,  // map hiragana to katakana
   LCMAP_HALFWIDTH=         0x00400000,  // map double byte to single byte
   LCMAP_FULLWIDTH=         0x00800000,  // map single byte to double byte
   LCMAP_LINGUISTIC_CASING=    0x01000000,  // use linguistic rules for casing
   LCMAP_SIMPLIFIED_CHINESE=   0x02000000,  // map traditional chinese to simplified chinese
   LCMAP_TRADITIONAL_CHINESE=  0x04000000,  // map simplified chinese to traditional chinese
   };
   
inline
int LCMapString (ulong locale, classics::flagword<LCMAP_flags> flags, const wchar_t* input, int inlen, wchar_t* output, int outlen)
 {
 return ::LCMapStringW (locale, flags.validdata(), reinterpret_cast<arg::carg32>(input), inlen, reinterpret_cast<arg::arg32>(output), outlen);
 }

inline
int LCMapString (classics::flagword<LCMAP_flags> flags, const wchar_t* input, int inlen, wchar_t* output, int outlen)
 {
 return ::LCMapStringW (GetThreadLocale(), flags.validdata(), reinterpret_cast<arg::carg32>(input), inlen, reinterpret_cast<arg::arg32>(output), outlen);
 }

inline
int LCMapString (ulong locale, classics::flagword<LCMAP_flags> flags, const char* input, int inlen, char* output, int outlen)
 {
 return ::LCMapStringA (locale, flags.validdata(), reinterpret_cast<arg::carg32>(input), inlen, reinterpret_cast<arg::arg32>(output), outlen);
 }

inline
int LCMapString (classics::flagword<LCMAP_flags> flags, const char* input, int inlen, char* output, int outlen)
 {
 return ::LCMapStringA (GetThreadLocale(), flags.validdata(), reinterpret_cast<arg::carg32>(input), inlen, reinterpret_cast<arg::arg32>(output), outlen);
 }

} // end of ratwin
ENDWRAP

#endif










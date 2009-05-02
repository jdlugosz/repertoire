// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\charset.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\atom.h contains globals.
#endif

#include "ratwin\base.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) int __stdcall CharToOemBuffW (Dlugosz::ratwin::arg::carg32, char*, unsigned long);
__declspec(dllimport) int __stdcall MultiByteToWideChar (unsigned, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) int __stdcall GetStringTypeW (unsigned long, Dlugosz::ratwin::arg::carg32, int, unsigned short*);
__declspec(dllimport) int __stdcall WideCharToMultiByte (unsigned, unsigned long, Dlugosz::ratwin::arg::carg32, int, char*, int, const char*, int*);
__declspec(dllimport) int __stdcall FoldStringW (unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) unsigned long __stdcall LCMapStringW (unsigned long, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) unsigned long __stdcall LCMapStringA (unsigned long, unsigned long, Dlugosz::ratwin::arg::carg32, int, Dlugosz::ratwin::arg::arg32, int);
__declspec(dllimport) unsigned long __stdcall GetThreadLocale();
__declspec(dllimport) int __stdcall GetLocaleInfoW (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, void*, int);
__declspec(dllimport) int __stdcall GetLocaleInfoA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, void*, int);
__declspec(dllimport) int __stdcall SetLocaleInfoA (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, const char*);
__declspec(dllimport) int __stdcall SetLocaleInfoW (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, const wchar_t*);
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
 
inline
int WideCharToMultiByte (CodePage_t cp, unsigned flags, const wchar_t* src, int srclen, char* dest, int destlen)
 {
 return ::WideCharToMultiByte (cp, flags, reinterpret_cast<arg::carg32>(src), srclen, dest, destlen, 0,0);
 }
 
enum MapFlag_t {
   MAP_FOLDCZONE= 0x0010,  // fold compatibility zone chars
   MAP_PRECOMPOSED= 0x0020,  // convert to precomposed chars
   MAP_COMPOSITE= 0x0040,  // convert to composite chars
   MAP_FOLDDIGITS= 0x0080,  // all digits to ASCII 0-9

#if(WINVER >= 0x0500)
   MAP_EXPAND_LIGATURES= 0x2000  // expand all ligatures
#endif /* WINVER >= 0x0500 */
   };

inline
int FoldString (classics::flagword<MapFlag_t> flags, const wchar_t* src, int srclen, wchar_t* dest, int destlen)
 {
 return ::FoldStringW (flags.validdata(), reinterpret_cast<arg::carg32>(src), srclen, reinterpret_cast<arg::arg32>(dest), destlen);
 }
 
inline
int FoldString (MapFlag_t flag, const wchar_t* src, int srclen, wchar_t* dest, int destlen)
 {
 return ::FoldStringW (flag, reinterpret_cast<arg::carg32>(src), srclen, reinterpret_cast<arg::arg32>(dest), destlen);
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

enum LCTYPE {
   LOCALE_ILANGUAGE= 0x00000001,   // language id
   LOCALE_SLANGUAGE= 0x00000002,   // localized name of language
   LOCALE_SENGLANGUAGE= 0x00001001,   // English name of language  
   LOCALE_SABBREVLANGNAME= 0x00000003,   // abbreviated language name
   LOCALE_SNATIVELANGNAME= 0x00000004,   // native name of language
   LOCALE_ICOUNTRY= 0x00000005,   // country code
   LOCALE_SCOUNTRY= 0x00000006,   // localized name of country
   LOCALE_SENGCOUNTRY= 0x00001002,   // English name of country
   LOCALE_SABBREVCTRYNAME= 0x00000007,   // abbreviated country name
   LOCALE_SNATIVECTRYNAME= 0x00000008,   // native name of country
   LOCALE_IDEFAULTLANGUAGE= 0x00000009,   // default language id
   LOCALE_IDEFAULTCOUNTRY= 0x0000000A,   // default country code
   LOCALE_IDEFAULTCODEPAGE= 0x0000000B,   // default oem code page
   LOCALE_IDEFAULTANSICODEPAGE= 0x00001004,   // default ansi code page
   LOCALE_IDEFAULTMACCODEPAGE= 0x00001011,   // default mac code page
   LOCALE_SLIST= 0x0000000C,   // list item separator
   LOCALE_IMEASURE= 0x0000000D,   // 0 = metric, 1 = US
   LOCALE_SDECIMAL= 0x0000000E,   // decimal separator
   LOCALE_STHOUSAND= 0x0000000F,   // thousand separator
   LOCALE_SGROUPING= 0x00000010,   // digit grouping
   LOCALE_IDIGITS= 0x00000011,   // number of fractional digits
   LOCALE_ILZERO= 0x00000012,   // leading zeros for decimal
   LOCALE_INEGNUMBER= 0x00001010,   // negative number mode
   LOCALE_SNATIVEDIGITS= 0x00000013,   // native ascii 0-9
   LOCALE_SCURRENCY= 0x00000014,   // local monetary symbol
   LOCALE_SINTLSYMBOL= 0x00000015,   // intl monetary symbol
   LOCALE_SMONDECIMALSEP= 0x00000016,   // monetary decimal separator
   LOCALE_SMONTHOUSANDSEP= 0x00000017,   // monetary thousand separator
   LOCALE_SMONGROUPING= 0x00000018,   // monetary grouping
   LOCALE_ICURRDIGITS= 0x00000019,   // # local monetary digits
   LOCALE_IINTLCURRDIGITS= 0x0000001A,   // # intl monetary digits
   LOCALE_ICURRENCY= 0x0000001B,   // positive currency mode
   LOCALE_INEGCURR= 0x0000001C,   // negative currency mode
   LOCALE_SDATE= 0x0000001D,   // date separator
   LOCALE_STIME= 0x0000001E,   // time separator
   LOCALE_SSHORTDATE= 0x0000001F,   // short date format string
   LOCALE_SLONGDATE= 0x00000020,   // long date format string
   LOCALE_STIMEFORMAT= 0x00001003,   // time format string
   LOCALE_IDATE= 0x00000021,   // short date format ordering
   LOCALE_ILDATE= 0x00000022,   // long date format ordering
   LOCALE_ITIME= 0x00000023,   // time format specifier
   LOCALE_ITIMEMARKPOSN= 0x00001005,   // time marker position
   LOCALE_ICENTURY= 0x00000024,   // century format specifier (short date)
   LOCALE_ITLZERO= 0x00000025,   // leading zeros in time field
   LOCALE_IDAYLZERO= 0x00000026,   // leading zeros in day field (short date)
   LOCALE_IMONLZERO= 0x00000027,   // leading zeros in month field (short date)
   LOCALE_S1159= 0x00000028,   // AM designator
   LOCALE_S2359= 0x00000029,   // PM designator
   LOCALE_ICALENDARTYPE= 0x00001009,   // type of calendar specifier
   LOCALE_IOPTIONALCALENDAR= 0x0000100B,   // additional calendar types specifier
   LOCALE_IFIRSTDAYOFWEEK= 0x0000100C,   // first day of week specifier
   LOCALE_IFIRSTWEEKOFYEAR= 0x0000100D,   // first week of year specifier
   LOCALE_SDAYNAME1= 0x0000002A,   // long name for Monday
   LOCALE_SDAYNAME2= 0x0000002B,   // long name for Tuesday
   LOCALE_SDAYNAME3= 0x0000002C,   // long name for Wednesday
   LOCALE_SDAYNAME4= 0x0000002D,   // long name for Thursday
   LOCALE_SDAYNAME5= 0x0000002E,   // long name for Friday
   LOCALE_SDAYNAME6= 0x0000002F,   // long name for Saturday
   LOCALE_SDAYNAME7= 0x00000030,   // long name for Sunday
   LOCALE_SABBREVDAYNAME1= 0x00000031,   // abbreviated name for Monday
   LOCALE_SABBREVDAYNAME2= 0x00000032,   // abbreviated name for Tuesday
   LOCALE_SABBREVDAYNAME3= 0x00000033,   // abbreviated name for Wednesday
   LOCALE_SABBREVDAYNAME4= 0x00000034,   // abbreviated name for Thursday
   LOCALE_SABBREVDAYNAME5= 0x00000035,   // abbreviated name for Friday
   LOCALE_SABBREVDAYNAME6= 0x00000036,   // abbreviated name for Saturday
   LOCALE_SABBREVDAYNAME7= 0x00000037,   // abbreviated name for Sunday
   LOCALE_SMONTHNAME1= 0x00000038,   // long name for January
   LOCALE_SMONTHNAME2= 0x00000039,   // long name for February
   LOCALE_SMONTHNAME3= 0x0000003A,   // long name for March
   LOCALE_SMONTHNAME4= 0x0000003B,   // long name for April
   LOCALE_SMONTHNAME5= 0x0000003C,   // long name for May
   LOCALE_SMONTHNAME6= 0x0000003D,   // long name for June
   LOCALE_SMONTHNAME7= 0x0000003E,   // long name for July
   LOCALE_SMONTHNAME8= 0x0000003F,   // long name for August
   LOCALE_SMONTHNAME9= 0x00000040,   // long name for September
   LOCALE_SMONTHNAME10= 0x00000041,   // long name for October
   LOCALE_SMONTHNAME11= 0x00000042,   // long name for November
   LOCALE_SMONTHNAME12= 0x00000043,   // long name for December
   LOCALE_SMONTHNAME13= 0x0000100E,   // long name for 13th month (if exists)
   LOCALE_SABBREVMONTHNAME1= 0x00000044,   // abbreviated name for January
   LOCALE_SABBREVMONTHNAME2= 0x00000045,   // abbreviated name for February
   LOCALE_SABBREVMONTHNAME3= 0x00000046,   // abbreviated name for March
   LOCALE_SABBREVMONTHNAME4= 0x00000047,   // abbreviated name for April
   LOCALE_SABBREVMONTHNAME5= 0x00000048,   // abbreviated name for May
   LOCALE_SABBREVMONTHNAME6= 0x00000049,   // abbreviated name for June
   LOCALE_SABBREVMONTHNAME7= 0x0000004A,   // abbreviated name for July
   LOCALE_SABBREVMONTHNAME8= 0x0000004B,   // abbreviated name for August
   LOCALE_SABBREVMONTHNAME9= 0x0000004C,   // abbreviated name for September
   LOCALE_SABBREVMONTHNAME10= 0x0000004D,   // abbreviated name for October
   LOCALE_SABBREVMONTHNAME11= 0x0000004E,   // abbreviated name for November
   LOCALE_SABBREVMONTHNAME12= 0x0000004F,   // abbreviated name for December
   LOCALE_SABBREVMONTHNAME13= 0x0000100F,   // abbreviated name for 13th month (if exists)
   LOCALE_SPOSITIVESIGN= 0x00000050,   // positive sign
   LOCALE_SNEGATIVESIGN= 0x00000051,   // negative sign
   LOCALE_IPOSSIGNPOSN= 0x00000052,   // positive sign position
   LOCALE_INEGSIGNPOSN= 0x00000053,   // negative sign position
   LOCALE_IPOSSYMPRECEDES= 0x00000054,   // mon sym precedes pos amt
   LOCALE_IPOSSEPBYSPACE= 0x00000055,   // mon sym sep by space from pos amt
   LOCALE_INEGSYMPRECEDES= 0x00000056,   // mon sym precedes neg amt
   LOCALE_INEGSEPBYSPACE= 0x00000057,   // mon sym sep by space from neg amt
   LOCALE_FONTSIGNATURE= 0x00000058,   // font signature
   LOCALE_SISO639LANGNAME= 0x00000059,   // ISO abbreviated language name
   LOCALE_SISO3166CTRYNAME= 0x0000005A,   // ISO abbreviated country name
   LOCALE_IDEFAULTEBCDICCODEPAGE= 0x00001012,   // default ebcdic code page
   LOCALE_IPAPERSIZE= 0x0000100A,   // 0 = letter, 1 = a4, 2 = legal, 3 = a3
   LOCALE_SENGCURRNAME= 0x00001007,   // english name of currency
   LOCALE_SNATIVECURRNAME= 0x00001008,   // native name of currency
   LOCALE_SYEARMONTH= 0x00001006,   // year month format string
   LOCALE_SSORTNAME= 0x00001013,   // sort name
   LOCALE_IDIGITSUBSTITUTION= 0x00001014,   // 0 = none, 1 = context, 2 = native digit
   };

inline LCTYPE no_user_override (LCTYPE x)     // do not use user overrides
 { return static_cast<LCTYPE> (x | 0x80000000); }

inline LCTYPE use_cp_acp (LCTYPE x)   // use the system ACP
 { return static_cast<LCTYPE> (x | 0x40000000); }

inline LCTYPE return_number (LCTYPE x)  // return number instead of string
 { return static_cast<LCTYPE> (x | 0x20000000); }


inline
int GetLocaleInfo (ulong Locale, LCTYPE LCType, wchar_t* buffer, int buflen)
 {
 return ::GetLocaleInfoW (reinterpret_cast<arg::arg32>(Locale), reinterpret_cast<arg::arg32>(LCType), buffer, buflen);
 }

inline
int GetLocaleInfo (ulong Locale, LCTYPE LCType, char* buffer, int buflen)
 {
 return ::GetLocaleInfoA (reinterpret_cast<arg::arg32>(Locale), reinterpret_cast<arg::arg32>(LCType), buffer, buflen);
 }

inline
bool SetLocaleInfo (ulong Locale, LCTYPE LCType, const wchar_t* buffer)
 {
 return ::SetLocaleInfoW (reinterpret_cast<arg::arg32>(Locale), reinterpret_cast<arg::arg32>(LCType), buffer);
 }

inline
bool SetLocaleInfo (ulong Locale, LCTYPE LCType, const char* buffer)
 {
 return ::SetLocaleInfoA (reinterpret_cast<arg::arg32>(Locale), reinterpret_cast<arg::arg32>(LCType), buffer);
 }


} // end of ratwin
ENDWRAP


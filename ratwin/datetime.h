// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\datetime.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\datetime.h contains globals.
#endif

#include "ratwin\base.h"


// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall GetTimeZoneInformation (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall GetLocalTime (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall GetSystemTime (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall FileTimeToSystemTime (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall GetSystemTimeAsFileTime (Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

enum timezone_ID {
   TIME_ZONE_ID_INVALID= -1,
   TIME_ZONE_ID_UNKNOWN= 0,
   TIME_ZONE_ID_STANDARD= 1,
   TIME_ZONE_ID_DAYLIGHT= 2,
   };


struct SYSTEMTIME {
   ushort wYear;
   ushort wMonth;
   ushort wDayOfWeek;
   ushort wDay;
   ushort wHour;
   ushort wMinute;
   ushort wSecond;
   ushort wMilliseconds;
   };

struct TIME_ZONE_INFORMATION {
   long Bias;
   wchar_t StandardName [32];
   SYSTEMTIME StandardDate;
   long StandardBias;
   wchar_t DaylightName [32];
   SYSTEMTIME DaylightDate;
   long DaylightBias;
   };

inline timezone_ID GetTimeZoneInformation (TIME_ZONE_INFORMATION& out)
 {   return static_cast<timezone_ID>( ::GetTimeZoneInformation (reinterpret_cast<arg::arg32>(&out)) );  }

inline void GetLocalTime (SYSTEMTIME& out)
 {   ::GetLocalTime (reinterpret_cast<arg::arg32>(&out)); }

inline void GetSystemTime (SYSTEMTIME& out)
 {   ::GetSystemTime (reinterpret_cast<arg::arg32>(&out)); }

inline bool FileTimeToSystemTime (__int64 filetime, SYSTEMTIME& out)
 {   return ::FileTimeToSystemTime (reinterpret_cast<arg::carg32>(&filetime), reinterpret_cast<arg::arg32>(&out)); }

inline __int64 GetSystemTimeAsFileTime()
 {
 __int64 result;
 ::GetSystemTimeAsFileTime (reinterpret_cast<arg::arg32>(&result));
 return result;
 }

// note: GetThreadLocale is found in ratwin\charset.h



} // end of ratwin
ENDWRAP



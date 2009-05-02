// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\sysinfo=struct.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "ratwin\base.h"
STARTWRAP
namespace ratwin {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin)
   VER_PLATFORM_WIN32s VER_PLATFORM_WIN32_WINDOWS VER_PLATFORM_WIN32_NT
*/
// ## BEGIN MacroCloak Generated Code
#if defined (VER_PLATFORM_WIN32s)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef VER_PLATFORM_WIN32s
#undef VER_PLATFORM_WIN32_WINDOWS
#undef VER_PLATFORM_WIN32_NT
#endif
// ## END Generated Code

struct SYSTEM_INFO {
   unsigned short wProcessorArchitecture;
   unsigned short wReserved;
   unsigned long dwPageSize;
   void* lpMinimumApplicationAddress;
   void* lpMaximumApplicationAddress;
   unsigned long dwActiveProcessorMask;
   unsigned long dwNumberOfProcessors;
   unsigned long dwProcessorType;
   unsigned long dwAllocationGranularity;
   unsigned short wProcessorLevel;
   unsigned short wProcessorRevision;
   };

struct OSVERSIONINFO {
   unsigned long dwOSVersionInfoSize;
   unsigned long dwMajorVersion;
   unsigned long dwMinorVersion;
   unsigned long dwBuildNumber;
   unsigned long dwPlatformId;
   char szCSDVersion[ 128 ];     // contains something like "Service Pack 3", a string to suffix the OS name with.
   };

enum {
   VER_PLATFORM_WIN32s= 0,
   VER_PLATFORM_WIN32_WINDOWS= 1,
   VER_PLATFORM_WIN32_NT= 2,
   };
   

} // end of ratwin
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::VER_PLATFORM_WIN32s;
using ratwin::VER_PLATFORM_WIN32_WINDOWS;
using ratwin::VER_PLATFORM_WIN32_NT;
#endif
// ## END Generated Code


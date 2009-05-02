// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\process.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_TASKING_PROCESS_INCLUDED
#define RATWIN_TASKING_PROCESS_INCLUDED

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetCurrentProcess();
__declspec(dllimport) unsigned long __stdcall GetModuleFileNameA (Dlugosz::ratwin::arg::arg32, char*, unsigned long);
__declspec(dllimport) unsigned long __stdcall GetModuleFileNameW (Dlugosz::ratwin::arg::arg32, wchar_t*, unsigned long);
__declspec(dllimport) int __stdcall CreateProcessA (
    const char* lpApplicationName,
    char* lpCommandLine,
    Dlugosz::ratwin::arg::arg32 lpProcessAttributes,
    Dlugosz::ratwin::arg::arg32 lpThreadAttributes,
    int bInheritHandles,
    unsigned long dwCreationFlags,
    void* lpEnvironment,
    const char* lpCurrentDirectory,
    Dlugosz::ratwin::arg::arg32 lpStartupInfo,
    void* lpProcessInformation
    );
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace tasking {

enum dll_entry_reason {
   DLL_PROCESS_DETACH=0,
   DLL_PROCESS_ATTACH,
   DLL_THREAD_ATTACH,
   DLL_THREAD_DETACH,
   };

enum startup_info_flags {
   STARTF_USESHOWWINDOW=    0x00000001,
   STARTF_USESIZE=          0x00000002,
   STARTF_USEPOSITION=      0x00000004,
   STARTF_USECOUNTCHARS=    0x00000008,
   STARTF_USEFILLATTRIBUTE= 0x00000010,
   STARTF_RUNFULLSCREEN=    0x00000020,
   STARTF_FORCEONFEEDBACK=  0x00000040,
   STARTF_FORCEOFFFEEDBACK= 0x00000080,
   STARTF_USESTDHANDLES=    0x00000100,
   STARTF_USEHOTKEY=        0x00000200,
   };
   
struct PROCESS_INFORMATION {
   types::HANDLE hProcess;
   types::HANDLE hThread;
   unsigned dwProcessId;
   unsigned dwThreadId;
   };

struct STARTUPINFO {
   ulong cb;
   const char* lpReserved;
   const char* lpDesktop;
   const char* lpTitle;
   ulong dwX;
   ulong dwY;
   ulong dwXSize;
   ulong dwYSize;
   ulong dwXCountChars;
   ulong dwYCountChars;
   ulong dwFillAttribute;
   ulong dwFlags;
   ushort wShowWindow;
   ushort cbReserved2;
   void* lpReserved2;
   types::HANDLE hStdInput;
   types::HANDLE hStdOutput;
   types::HANDLE hStdError;
   };

inline
types::HANDLE GetCurrentProcess()
 { return reinterpret_cast<types::HANDLE>(::GetCurrentProcess()); }

inline
ulong GetModuleFileName (types::HMODULE module, char* outbuf, ulong outbufsize)
 { return ::GetModuleFileNameA (reinterpret_cast<arg::arg32>(module), outbuf, outbufsize); }

inline
ulong GetModuleFileName (types::HMODULE module, wchar_t* outbuf, ulong outbufsize)
 { return ::GetModuleFileNameW (reinterpret_cast<arg::arg32>(module), outbuf, outbufsize); }

inline
bool CreateProcess (
   const char* ApplicationName,
   char* CommandLine,
   types::SECURITY_ATTRIBUTES* ProcessAttributes,
   types::SECURITY_ATTRIBUTES* ThreadAttributes,
   bool InheritHandles,
   unsigned long CreationFlags,
   void* Environment,
   const char* CurrentDirectory,
   STARTUPINFO& StartupInfo,
   PROCESS_INFORMATION& ProcessInformation
   )
 { return ::CreateProcessA (
      ApplicationName, CommandLine, reinterpret_cast<arg::arg32>(ProcessAttributes),
      reinterpret_cast<arg::arg32>(ThreadAttributes), InheritHandles, CreationFlags,
      Environment, CurrentDirectory, reinterpret_cast<arg::arg32>(&StartupInfo),
      &ProcessInformation); }
 
}

}
ENDWRAP
#endif


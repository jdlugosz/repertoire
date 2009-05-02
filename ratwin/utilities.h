// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_utilities_INCLUDED
#define RATWIN_utilities_INCLUDED

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) int __stdcall MessageBoxA (Dlugosz::ratwin::arg::arg32 hWnd, const char* lpText, const char* lpCaption, unsigned uType);
__declspec(dllimport) int __stdcall MessageBoxW (Dlugosz::ratwin::arg::arg32 hWnd, const wchar_t* lpText, const wchar_t* lpCaption, unsigned uType);
__declspec(dllimport) int __cdecl wsprintfA (char* dest, const char* format ...);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall GetModuleHandleA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned long __stdcall GetLastError();
__declspec(dllimport) void __stdcall SetLastError (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall Sleep (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall SleepEx (Dlugosz::ratwin::arg::arg32, bool alertable);
__declspec(dllimport) unsigned long __stdcall FormatMessageA (unsigned long, const void* lpSource, unsigned long, unsigned long, char*, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall FormatMessageW (unsigned long, const void* lpSource, unsigned long, unsigned long, wchar_t*, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall DebugActiveProcess (unsigned long dwProcessId);
__declspec(dllimport) unsigned long __stdcall GetTickCount();   //not cloaked!
__declspec(dllimport) int __stdcall MessageBeep (Dlugosz::ratwin::arg::arg32);


// put these in with system info, later
__declspec(dllimport) void __stdcall  GetSystemInfo (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall GetVersionExA (Dlugosz::ratwin::arg::arg32);

// file these elsewhere, later
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall LoadLibraryExA (const char* lpLibFileName, Dlugosz::ratwin::arg::arg32 hFile, unsigned long dwFlags);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall LoadLibraryExA (const char* lpLibFileName, Dlugosz::ratwin::arg::arg32 hFile, unsigned long dwFlags);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall LoadLibraryA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) void* __stdcall GetProcAddress (Dlugosz::ratwin::arg::arg32, const char* name);
__declspec(dllimport) int __stdcall FreeLibrary (Dlugosz::ratwin::arg::arg32);


}


STARTWRAP
namespace ratwin {

namespace util {

inline ushort LOWORD (int x) { return x; }
inline ushort HIWORD (ulong x) { return ushort(x >> 16); }

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
   char szCSDVersion[ 128 ];     // Maintenance string for PSS usage
   };

enum {
   VER_PLATFORM_WIN32s= 0,
   VER_PLATFORM_WIN32_WINDOWS= 1,
   VER_PLATFORM_WIN32_NT= 2,
   };
   
inline
void GetSystemInfo (SYSTEM_INFO& info)
 {
 ::GetSystemInfo (reinterpret_cast<arg::arg32>(&info));
 // future notes: make a whole module to encapsulate these attributes.
 }


inline
bool GetVersionEx (OSVERSIONINFO& info)
 {
 return ::GetVersionExA (reinterpret_cast<arg::arg32>(&info));
 }

inline
int MessageBox (types::HWND parent, const char* text, const char* caption, unsigned options=0)
 { return ::MessageBoxA (reinterpret_cast<arg::arg32>(parent), text, caption, options); }
 
inline
int MessageBox (const char* text, const char* caption, unsigned options=0)
 { return ::MessageBoxA (0, text, caption, options); }

inline
int MessageBox (types::HWND parent, const wchar_t* text, const wchar_t* caption, unsigned options=0)
 { return ::MessageBoxW (reinterpret_cast<arg::arg32>(parent), text, caption, options); }
 
inline
int MessageBox (const wchar_t* text, const wchar_t* caption, unsigned options=0)
 { return ::MessageBoxW (0, text, caption, options); }

inline
bool MessageBeep (unsigned options=0)
 { return ::MessageBeep (reinterpret_cast<arg::arg32>(options)); }
 
inline 
types::HINSTANCE GetModuleHandle (const char* module_name= 0)
 { return reinterpret_cast<types::HINSTANCE>(::GetModuleHandleA(reinterpret_cast<arg::carg32>(module_name))); }

RATWIN_EXPORT
types::HINSTANCE get_Instance();

inline
void Sleep (ulong time)
 { ::Sleep (reinterpret_cast<arg::arg32>(time)); }

inline
int Sleep (ulong time, bool alertable)
 { return ::SleepEx (reinterpret_cast<arg::arg32>(time), alertable); }

inline
ulong FormatMessage (void* Source, ulong MessageId, char* Buffer, ulong size)
 { const int flags= 0x1200;  //format from system and ignore inserts.
 return ::FormatMessageA (flags, Source, MessageId, 0, Buffer, size, 0); }

inline
ulong FormatMessage (void* Source, ulong MessageId, wchar_t* Buffer, ulong size)
 { const int flags= 0x1200;  //format from system and ignore inserts.
 return ::FormatMessageW (flags, Source, MessageId, 0, Buffer, size, 0); }

 /////////////

inline
types::HINSTANCE LoadLibraryEx (const char* lpLibFileName, types::HANDLE hFile, ulong dwFlags)
 {  return reinterpret_cast<types::HINSTANCE>(::LoadLibraryExA(lpLibFileName, reinterpret_cast<arg::arg32>(hFile), dwFlags)); }

inline
types::HINSTANCE LoadLibrary (const char* lpLibFileName)
 {  return reinterpret_cast<types::HINSTANCE>(::LoadLibraryA(reinterpret_cast<arg::carg32>(lpLibFileName))); }

inline
void* GetProcAddress (types::HINSTANCE module, const char* name)
 {
 return ::GetProcAddress (reinterpret_cast<arg::arg32>(module), name);
 }

inline
bool FreeLibrary (types::HINSTANCE module)
 {
 return ::FreeLibrary (reinterpret_cast<arg::arg32>(module));
 }

inline
ulong GetLastError()
 { return ::GetLastError(); }

inline
void SetLastError (unsigned val)
 { ::SetLastError (reinterpret_cast<arg::arg32>(val) ); }

inline
ulong GetTickCount()
 { return ::GetTickCount(); }

} //end of util

}
ENDWRAP

#endif


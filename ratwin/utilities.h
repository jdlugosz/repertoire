// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\utilities.h contains globals.
#endif

#include "ratwin\base.h"

extern "C" {
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
// __declspec(dllimport) int __stdcall MessageBeep (Dlugosz::ratwin::arg::arg32);
// MessageBeep moved to sound.h
__declspec(dllimport) void __stdcall OutputDebugStringA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) void __stdcall OutputDebugStringW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall GetWindowsDirectoryA (void*, int);
__declspec(dllimport) int __stdcall GetWindowsDirectoryW (void*, int);
__declspec(dllimport) int __stdcall GetSystemDirectoryA (void*, int);
__declspec(dllimport) int __stdcall GetSystemDirectoryW (void*, int);


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
inline ulong MAKELONG (ushort H, ushort L) { return L | (H<<16); }


// note: SYSTEM_INFO, OSVERSIONINFO, GetSystemInfo, GetVersionEx moved from here to sysinfo.h

inline
void OutputDebugString (const char* string)
 { ::OutputDebugStringA (reinterpret_cast<arg::carg32>(string)); }

inline
void OutputDebugString (const wchar_t* string)
 { ::OutputDebugStringW (reinterpret_cast<arg::carg32>(string)); }

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

inline ulong
GetWindowsDirectory (char* result, int bufsize)
 {
 return ::GetWindowsDirectoryA (result, bufsize);
 }
 
inline ulong
GetWindowsDirectory (wchar_t* result, int bufsize)
 {
 return ::GetWindowsDirectoryW (result, bufsize);
 }

inline ulong
GetSystemDirectory (char* result, int bufsize)
 {
 return ::GetSystemDirectoryA (result, bufsize);
 }
 
inline ulong
GetSystemDirectory (wchar_t* result, int bufsize)
 {
 return ::GetSystemDirectoryW (result, bufsize);
 }

} //end of util

}
ENDWRAP



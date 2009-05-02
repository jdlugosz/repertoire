// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\file.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined Iaac0f2b0_2fec_11d3_aacf_0020af6bccd6
#define Iaac0f2b0_2fec_11d3_aacf_0020af6bccd6


#include "ratwin\io\general.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateFileA (
   Dlugosz::ratwin::arg::carg32, unsigned long, unsigned long, void*, unsigned long, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall CreateFileW (
   Dlugosz::ratwin::arg::carg32, unsigned long, unsigned long, void*, unsigned long, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall GetFullPathNameW (Dlugosz::ratwin::arg::carg32, unsigned long, wchar_t*, wchar_t**);
__declspec(dllimport) unsigned long __stdcall GetFullPathNameA (Dlugosz::ratwin::arg::carg32, unsigned long, char*, char**);
__declspec(dllimport) int __stdcall CopyFileA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int);
__declspec(dllimport) int __stdcall CopyFileW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int);
__declspec(dllimport) int __stdcall CreateDirectoryExA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int);
__declspec(dllimport) int __stdcall CreateDirectoryExW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int);
__declspec(dllimport) int __stdcall SetCurrentDirectoryA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall SetCurrentDirectoryW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned long __stdcall GetFileAttributesA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned long __stdcall GetFileAttributesW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned long __stdcall GetFileSize (Dlugosz::ratwin::arg::carg32, unsigned long*);
__declspec(dllimport) int __stdcall GetFileTime (Dlugosz::ratwin::arg::arg32, __int64*, __int64*, __int64*);
__declspec(dllimport) int __stdcall CreateDirectoryA (Dlugosz::ratwin::arg::carg32, void*);
__declspec(dllimport) int __stdcall CreateDirectoryW (Dlugosz::ratwin::arg::carg32, void*);
__declspec(dllimport) int __stdcall RemoveDirectoryA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall RemoveDirectoryW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall GetShortPathNameA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllimport) int __stdcall GetShortPathNameW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall FindFirstFileW (Dlugosz::ratwin::arg::carg32, void*);
__declspec(dllimport) Dlugosz::ratwin::arg::arg32 __stdcall FindFirstFileA (Dlugosz::ratwin::arg::carg32, void*);
__declspec(dllimport) int __stdcall FindClose (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall GetTempPathW (unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall GetTempPathA (unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall DeleteFileA (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall DeleteFileW (Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned long __stdcall GetTempFileNameW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall GetTempFileNameA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned long, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned int __stdcall MoveFileW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned int __stdcall MoveFileA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) unsigned int __stdcall MoveFileExW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned);
__declspec(dllimport) unsigned int __stdcall MoveFileExA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned);
}


STARTWRAP
namespace ratwin {
namespace io {

static const int MAX_PATH= 260;

enum access_t {
   ACCESS_ONLY = 0, 
   FILE_LIST_DIRECTORY = 1,
   FILE_READ_ATTRIBUTES= 0x80,
   GENERIC_READ = 0x80000000, 
   GENERIC_WRITE = 0x40000000, 
   GENERIC_READWRITE= GENERIC_READ|GENERIC_WRITE
   };

enum sharing_t {
   FILE_SHARE_EXCLUSIVE = 0,
   FILE_SHARE_DELETE = 4,
   FILE_SHARE_READ = 1,
   FILE_SHARE_WRITE = 2,
   FILE_SHARE_READWRITE = 3,
   FILE_SHARE_WIDEOPEN = 7
   };

enum creation_t {
   CREATE_NEW = 1,	  // error if file already exists.
   CREATE_ALWAYS = 2,  // blows away any existing file.
   OPEN_EXISTING = 3,  // error if file doesn't already exist.
   OPEN_ALWAYS = 4,  // open or create if needed.
   TRUNCATE_EXISTING = 5  // destroys existing file, error if doesn't already exist.
   };

enum attribute_flags {
   FILE_ATTRIBUTE_READONLY=         0x00000001,
   FILE_ATTRIBUTE_HIDDEN=           0x00000002,
   FILE_ATTRIBUTE_SYSTEM=           0x00000004,
   FILE_ATTRIBUTE_DIRECTORY=        0x00000010,
   FILE_ATTRIBUTE_ARCHIVE=          0x00000020,
   FILE_ATTRIBUTE_NORMAL=           0x00000080,
   FILE_ATTRIBUTE_TEMPORARY=        0x00000100,
   FILE_FLAG_WRITE_THROUGH=     0x80000000,
   FILE_FLAG_RANDOM_ACCESS=     0x10000000,
   FILE_FLAG_OVERLAPPED=            0x40000000,
   FILE_FLAG_NO_BUFFERING=          0x20000000,
   FILE_FLAG_SEQUENTIAL_SCAN=       0x08000000,
   FILE_FLAG_DELETE_ON_CLOSE=       0x04000000,
   FILE_FLAG_BACKUP_SEMANTICS=      0x02000000,
   FILE_FLAG_POSIX_SEMANTICS=       0x01000000
   };

enum move_flags {
   MOVEFILE_REPLACE_EXISTING= 0x00000001,
   MOVEFILE_COPY_ALLOWED= 0x00000002,
   MOVEFILE_DELAY_UNTIL_REBOOT= 0x00000004,
   MOVEFILE_WRITE_THROUGH= 0x00000008,
   // following are new for Windows 2000
   MOVEFILE_CREATE_HARDLINK= 0x00000010,
   MOVEFILE_FAIL_IF_NOT_TRACKABLE= 0x00000020
   };

const types::HANDLE INVALID_FILE= reinterpret_cast<types::HANDLE> (0xffffffff);

inline
types::HANDLE CreateFile (const char* name, access_t access, sharing_t share, creation_t how, ulong even_more_flags)
 {
 return reinterpret_cast<types::HANDLE> (::CreateFileA (reinterpret_cast<arg::carg32>(name), access, share, 0, how, even_more_flags, 0));
 }

inline
types::HANDLE CreateFile (const wchar_t* name, access_t access, sharing_t share, creation_t how, ulong even_more_flags)
 {
 return reinterpret_cast<types::HANDLE> (::CreateFileW (reinterpret_cast<arg::carg32>(name), access, share, 0, how, even_more_flags, 0));
 }

inline
ulong GetFullPathName (const wchar_t* name, int destlen, wchar_t* dest)
 {
 return ::GetFullPathNameW (reinterpret_cast<arg::carg32>(name), destlen, dest, 0);
 }

inline
ulong GetFullPathName (const char* name, int destlen, char* dest)
 {
 return ::GetFullPathNameA (reinterpret_cast<arg::carg32>(name), destlen, dest, 0);
 }

inline
bool CopyFile (const char* source, const char* dest, bool fail_if_exists= false)
 {
 return ::CopyFileA (reinterpret_cast<arg::carg32>(source), reinterpret_cast<arg::carg32>(dest), fail_if_exists);
 }

inline
bool CopyFile (const wchar_t* source, const wchar_t* dest, bool fail_if_exists= false)
 {
 return ::CopyFileW (reinterpret_cast<arg::carg32>(source), reinterpret_cast<arg::carg32>(dest), fail_if_exists);
 }
 
inline
bool CreateDirectoryEx (const char* proto, const char* newdir)
 {
 return ::CreateDirectoryExA (reinterpret_cast<arg::carg32>(proto), reinterpret_cast<arg::carg32>(newdir), 0);
 }

inline
bool CreateDirectoryEx (const wchar_t* proto, const wchar_t* newdir)
 {
 return ::CreateDirectoryExW (reinterpret_cast<arg::carg32>(proto), reinterpret_cast<arg::carg32>(newdir), 0);
 }

inline
ulong GetFileAttributes (const wchar_t* name)
// returns members of attribute_flags |'ed together
 {
 return ::GetFileAttributesW (reinterpret_cast<arg::carg32>(name));
 }
 
inline
ulong GetFileAttributes (const char* name)
// returns members of attribute_flags |'ed together
 {
 return ::GetFileAttributesA (reinterpret_cast<arg::carg32>(name));
 }

inline
__int64 GetFileSize (types::HANDLE h)
 {
 union {
    __int64 result;
    ulong part[2];
    };
 part[0]= ::GetFileSize (reinterpret_cast<arg::arg32>(h), part+1);
 return result;
 }

inline
bool GetFileTime (types::HANDLE h, __int64* create_time, __int64* access_time, __int64* write_time)
 {
 return ::GetFileTime (reinterpret_cast<arg::arg32>(h), create_time, access_time, write_time);
 }

inline
bool CreateDirectory (const char* name)
 {
 return ::CreateDirectoryA (reinterpret_cast<arg::carg32>(name), 0);
 }
 
 
inline
bool CreateDirectory (const wchar_t* name)
 {
 return ::CreateDirectoryW (reinterpret_cast<arg::carg32>(name), 0);
 }


inline
bool SetCurrentDirectory (const wchar_t* name)
 {
 return ::SetCurrentDirectoryW (reinterpret_cast<arg::carg32>(name));
 }


inline
bool SetCurrentDirectory (const char* name)
 {
 return ::SetCurrentDirectoryA (reinterpret_cast<arg::carg32>(name));
 }


inline
ulong GetShortPathName (const char* input, char* output, ulong buflen)
 {
 return ::GetShortPathNameA (reinterpret_cast<arg::carg32>(input), reinterpret_cast<arg::arg32>(output), buflen);
 }
 
inline
ulong GetShortPathName (const wchar_t* input, wchar_t* output, ulong buflen)
 {
 return ::GetShortPathNameW (reinterpret_cast<arg::carg32>(input), reinterpret_cast<arg::arg32>(output), buflen);
 }

#pragma pack (push, 1)
template <typename CharType>
struct WIN32_FIND_DATA {
   ulong FileAttributes;
   __int64 ftCreationTime;
   __int64 ftLastAccessTime;
   __int64 ftLastWriteTime;
   ulong FileSizeHigh;
   ulong FileSizeLow;
   ulong dwReserved0;
   ulong dwReserved1;
   CharType FileName [MAX_PATH];
   CharType AlternateFileName [14];
   };
#pragma pack (pop)

inline
types::HANDLE FindFirstFile (const wchar_t* name, WIN32_FIND_DATA<wchar_t>& result)
 {
 return reinterpret_cast<types::HANDLE>( ::FindFirstFileW (reinterpret_cast<arg::carg32>(name), &result) );
 }

inline
types::HANDLE FindFirstFile (const char* name, WIN32_FIND_DATA<char>& result)
 {
 return reinterpret_cast<types::HANDLE>( ::FindFirstFileA (reinterpret_cast<arg::carg32>(name), &result) );
 }

inline
bool FindClose (types::HANDLE h)
 {
 return ::FindClose (reinterpret_cast<arg::arg32>(h));
 }

inline
ulong GetTempPath (ulong buflen, char* buffer)
 {
 return ::GetTempPathA (buflen, reinterpret_cast<arg::arg32>(buffer));
 }
 
inline
ulong GetTempPath (ulong buflen, wchar_t* buffer)
 {
 return ::GetTempPathW (buflen, reinterpret_cast<arg::arg32>(buffer));
 }

inline
bool DeleteFile (const char* s)
 {
 return ::DeleteFileA (reinterpret_cast<arg::carg32>(s));
 }
 
inline
bool DeleteFile (const wchar_t* s)
 {
 return ::DeleteFileW (reinterpret_cast<arg::carg32>(s));
 }

inline
bool RemoveDirectory (const char* s)
 {
 return ::RemoveDirectoryA (reinterpret_cast<arg::carg32>(s));
 }
 
inline
bool RemoveDirectory (const wchar_t* s)
 {
 return ::RemoveDirectoryW (reinterpret_cast<arg::carg32>(s));
 }
 
inline
unsigned int GetTempFileName(const char* lpPathName, const char* lpPrefixString, unsigned int uUnique, char* lpTempFileName)
 {
 return ::GetTempFileNameA(reinterpret_cast<arg::carg32>(lpPathName),
                           reinterpret_cast<arg::carg32>(lpPrefixString),
                           uUnique,
                           reinterpret_cast<arg::arg32>(lpTempFileName));
 }

inline
unsigned int GetTempFileName(const wchar_t* lpPathName, const wchar_t* lpPrefixString, unsigned int uUnique, wchar_t* lpTempFileName)
 {
 return ::GetTempFileNameW(reinterpret_cast<arg::carg32>(lpPathName),
                           reinterpret_cast<arg::carg32>(lpPrefixString),
                           uUnique,
                           reinterpret_cast<arg::arg32>(lpTempFileName));
 }

inline
int MoveFile(const char* lpExistingFileName, const char* lpNewFileName)
 {
 return ::MoveFileA(reinterpret_cast<arg::carg32>(lpExistingFileName),
                    reinterpret_cast<arg::carg32>(lpNewFileName));
 }

inline
int MoveFile(const wchar_t* lpExistingFileName, const wchar_t* lpNewFileName)
 {
 return ::MoveFileW(reinterpret_cast<arg::carg32>(lpExistingFileName),
                    reinterpret_cast<arg::carg32>(lpNewFileName));
 }
 
inline
int MoveFile(const char* lpExistingFileName, const char* lpNewFileName, classics::flagword<move_flags> flags)
 {
 return ::MoveFileExA(reinterpret_cast<arg::carg32>(lpExistingFileName),
                    reinterpret_cast<arg::carg32>(lpNewFileName),
                    flags.validdata());
 }

inline
int MoveFile(const wchar_t* lpExistingFileName, const wchar_t* lpNewFileName, classics::flagword<move_flags> flags)
 {
 return ::MoveFileExW(reinterpret_cast<arg::carg32>(lpExistingFileName),
                    reinterpret_cast<arg::carg32>(lpNewFileName),
                    flags.validdata());
 }

} //end io
}
ENDWRAP
#endif


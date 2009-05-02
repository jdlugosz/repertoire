// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\DirNotification.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\DirNotification.h contains globals.
#endif

#include "ratwin\io\general.h"

extern "C" {
__declspec(dllimport) int __stdcall ReadDirectoryChangesW (Dlugosz::ratwin::arg::arg32 dirhandle, void*, unsigned long, int, unsigned long, unsigned long*, void*, void*);
}

STARTWRAP
namespace ratwin {
namespace io {

struct FILE_NOTIFY_INFORMATION {
   enum action_codes { ADDED=1,REMOVED,MODIFIED,RENAMED_OLD_NAME,RENAMED_NEW_NAME };
   ulong next_offset;
   ulong action;
   ulong name_length;  //in bytes
   ulong len() const  {  return name_length/2; }  //in characters
   wchar_t* name() { return (wchar_t*)(this+1); }
   action_codes get_action() const  { return static_cast<action_codes>(action); }
   FILE_NOTIFY_INFORMATION* next()  { return (FILE_NOTIFY_INFORMATION*) (next_offset ? next_offset+(byte*)(this) : 0); }
   };


enum DirectoryChangeFilterBits {
   FILE_NOTIFY_CHANGE_FILE_NAME= 0x00000001,
   FILE_NOTIFY_CHANGE_DIR_NAME= 0x00000002,
   FILE_NOTIFY_CHANGE_ATTRIBUTES= 0x00000004,
   FILE_NOTIFY_CHANGE_SIZE= 0x00000008,
   FILE_NOTIFY_CHANGE_LAST_WRITE= 0x00000010,
   FILE_NOTIFY_CHANGE_LAST_ACCESS= 0x00000020,
   FILE_NOTIFY_CHANGE_CREATION= 0x00000040,
   FILE_NOTIFY_CHANGE_SECURITY= 0x00000100   
   };

inline bool ReadDirectoryChanges (types::HANDLE dirhandle, void* buffer, ulong buflen, bool subtree, ulong filter, OVERLAPPED& ov, COMPLETION_ROUTINE callback)
// asynchronous callback form
 {
 return ::ReadDirectoryChangesW (reinterpret_cast<arg::arg32>(dirhandle), buffer, buflen, subtree, filter, 0, &ov, callback);
 }


}} // end of ratwin
ENDWRAP


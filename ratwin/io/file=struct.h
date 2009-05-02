// The Repertoire Project copyright 2000 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\file=struct.h
// Revision: post - public build 5


#pragma once
#if !defined I682b3e70_eee3_11d3_8de9_0006296222ef
#define I682b3e70_eee3_11d3_8de9_0006296222ef

#include "ratwin\io\general=struct.h"

STARTWRAP
namespace ratwin {
namespace io {

// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin::io)
   MAX_PATH FILE_LIST_DIRECTORY FILE_READ_ATTRIBUTES GENERIC_READ GENERIC_WRITE
   FILE_READ_DATA FILE_WRITE_DATA FILE_ADD_FILE FILE_APPEND_DATA FILE_ADD_SUBDIRECTORY FILE_CREATE_PIPE_INSTANCE
   FILE_SHARE_DELETE FILE_SHARE_READ FILE_SHARE_WRITE FILE_READ_EA FILE_WRITE_EA FILE_EXECUTE FILE_TRAVERSE
   FILE_DELETE_CHILD FILE_WRITE_ATTRIBUTES DELETE READ_CONTROL WRITE_DAC WRITE_OWNER STANDARD_RIGHTS_REQUIRED
   SYNCHRONIZE FILE_ALL_ACCESS FILE_GENERIC_READ FILE_GENERIC_WRITE FILE_GENERIC_EXECUTE
   STANDARD_RIGHTS_READ STANDARD_RIGHTS_WRITE STANDARD_RIGHTS_EXECUTE STANDARD_RIGHTS_ALL SPECIFIC_RIGHTS_ALL
   ACCESS_SYSTEM_SECURITY MAXIMUM_ALLOWED
   CREATE_NEW CREATE_ALWAYS OPEN_EXISTING OPEN_ALWAYS TRUNCATE_EXISTING
   FILE_ATTRIBUTE_READONLY FILE_ATTRIBUTE_HIDDEN FILE_ATTRIBUTE_SYSTEM FILE_ATTRIBUTE_DIRECTORY
   FILE_ATTRIBUTE_ARCHIVE FILE_ATTRIBUTE_ENCRYPTED FILE_ATTRIBUTE_NORMAL FILE_ATTRIBUTE_TEMPORARY
   FILE_ATTRIBUTE_SPARSE_FILE FILE_ATTRIBUTE_REPARSE_POINT FILE_ATTRIBUTE_COMPRESSED
   FILE_ATTRIBUTE_OFFLINE FILE_ATTRIBUTE_NOT_CONTENT_INDEXED
   FILE_FLAG_OPEN_NO_RECALL FILE_FLAG_OPEN_REPARSE_POINT FILE_FLAG_POSIX_SEMANTICS
   FILE_FLAG_BACKUP_SEMANTICS FILE_FLAG_DELETE_ON_CLOSE FILE_FLAG_SEQUENTIAL_SCAN
   FILE_FLAG_RANDOM_ACCESS FILE_FLAG_NO_BUFFERING FILE_FLAG_OVERLAPPED FILE_FLAG_WRITE_THROUGH
   SECURITY_ANONYMOUS SECURITY_IDENTIFICATION SECURITY_IMPERSONATION SECURITY_DELEGATION
   SECURITY_CONTEXT_TRACKING   SECURITY_EFFECTIVE_ONLY SECURITY_SQOS_PRESENT SECURITY_VALID_SQOS_FLAGS
   MOVEFILE_REPLACE_EXISTING MOVEFILE_COPY_ALLOWED MOVEFILE_DELAY_UNTIL_REBOOT MOVEFILE_WRITE_THROUGH
   MOVEFILE_CREATE_HARDLINK MOVEFILE_FAIL_IF_NOT_TRACKABLE
   INVALID_HANDLE_VALUE
*/
// ## BEGIN MacroCloak Generated Code
#if defined (MAX_PATH)
// if one of these is defined, user included WINDOWS.H first.
#pragma message ("WINDOWS.H was included before " __FILE__ ", changing macros to enums.")
#define DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef      //remember for later.
#undef MAX_PATH
#undef FILE_LIST_DIRECTORY
#undef FILE_READ_ATTRIBUTES
#undef GENERIC_READ
#undef GENERIC_WRITE
#undef FILE_READ_DATA
#undef FILE_WRITE_DATA
#undef FILE_ADD_FILE
#undef FILE_APPEND_DATA
#undef FILE_ADD_SUBDIRECTORY
#undef FILE_CREATE_PIPE_INSTANCE
#undef FILE_SHARE_DELETE
#undef FILE_SHARE_READ
#undef FILE_SHARE_WRITE
#undef FILE_READ_EA
#undef FILE_WRITE_EA
#undef FILE_EXECUTE
#undef FILE_TRAVERSE
#undef FILE_DELETE_CHILD
#undef FILE_WRITE_ATTRIBUTES
#undef DELETE
#undef READ_CONTROL
#undef WRITE_DAC
#undef WRITE_OWNER
#undef STANDARD_RIGHTS_REQUIRED
#undef SYNCHRONIZE
#undef FILE_ALL_ACCESS
#undef FILE_GENERIC_READ
#undef FILE_GENERIC_WRITE
#undef FILE_GENERIC_EXECUTE
#undef STANDARD_RIGHTS_READ
#undef STANDARD_RIGHTS_WRITE
#undef STANDARD_RIGHTS_EXECUTE
#undef STANDARD_RIGHTS_ALL
#undef SPECIFIC_RIGHTS_ALL
#undef ACCESS_SYSTEM_SECURITY
#undef MAXIMUM_ALLOWED
#undef CREATE_NEW
#undef CREATE_ALWAYS
#undef OPEN_EXISTING
#undef OPEN_ALWAYS
#undef TRUNCATE_EXISTING
#undef FILE_ATTRIBUTE_READONLY
#undef FILE_ATTRIBUTE_HIDDEN
#undef FILE_ATTRIBUTE_SYSTEM
#undef FILE_ATTRIBUTE_DIRECTORY
#undef FILE_ATTRIBUTE_ARCHIVE
#undef FILE_ATTRIBUTE_ENCRYPTED
#undef FILE_ATTRIBUTE_NORMAL
#undef FILE_ATTRIBUTE_TEMPORARY
#undef FILE_ATTRIBUTE_SPARSE_FILE
#undef FILE_ATTRIBUTE_REPARSE_POINT
#undef FILE_ATTRIBUTE_COMPRESSED
#undef FILE_ATTRIBUTE_OFFLINE
#undef FILE_ATTRIBUTE_NOT_CONTENT_INDEXED
#undef FILE_FLAG_OPEN_NO_RECALL
#undef FILE_FLAG_OPEN_REPARSE_POINT
#undef FILE_FLAG_POSIX_SEMANTICS
#undef FILE_FLAG_BACKUP_SEMANTICS
#undef FILE_FLAG_DELETE_ON_CLOSE
#undef FILE_FLAG_SEQUENTIAL_SCAN
#undef FILE_FLAG_RANDOM_ACCESS
#undef FILE_FLAG_NO_BUFFERING
#undef FILE_FLAG_OVERLAPPED
#undef FILE_FLAG_WRITE_THROUGH
#undef SECURITY_ANONYMOUS
#undef SECURITY_IDENTIFICATION
#undef SECURITY_IMPERSONATION
#undef SECURITY_DELEGATION
#undef SECURITY_CONTEXT_TRACKING
#undef SECURITY_EFFECTIVE_ONLY
#undef SECURITY_SQOS_PRESENT
#undef SECURITY_VALID_SQOS_FLAGS
#undef MOVEFILE_REPLACE_EXISTING
#undef MOVEFILE_COPY_ALLOWED
#undef MOVEFILE_DELAY_UNTIL_REBOOT
#undef MOVEFILE_WRITE_THROUGH
#undef MOVEFILE_CREATE_HARDLINK
#undef MOVEFILE_FAIL_IF_NOT_TRACKABLE
#undef INVALID_HANDLE_VALUE
#endif
// ## END Generated Code

static const int MAX_PATH= 260;

enum access_t {
// look up ACCESS_MASK in "Platform SDK: Security" for info on how bits are organized.
   DELETE=                     0x00010000,
   READ_CONTROL=               0x00020000,
   WRITE_DAC=                  0x00040000,
   WRITE_OWNER=                0x00080000,
   STANDARD_RIGHTS_REQUIRED= WRITE_OWNER | WRITE_DAC | READ_CONTROL | DELETE,
   SYNCHRONIZE=                0x00100000,
   STANDARD_RIGHTS_READ= READ_CONTROL,
   STANDARD_RIGHTS_WRITE= READ_CONTROL,
   STANDARD_RIGHTS_EXECUTE= READ_CONTROL,
   STANDARD_RIGHTS_ALL=        0x001F0000,

   SPECIFIC_RIGHTS_ALL=        0x0000FFFF,

   GENERIC_READ=               0x80000000, 
   GENERIC_WRITE=              0x40000000, 
   GENERIC_READWRITE= GENERIC_READ|GENERIC_WRITE, // not in WINDOWS.H, but common and handy.

   ACCESS_SYSTEM_SECURITY=     0x01000000, // very exotic: read/write SACL (logs access)
   MAXIMUM_ALLOWED=            0x02000000, // ask for "as much as I can get".

   ACCESS_ONLY= 0, // not in WINDOWS.H, but needed so we can use strongly-typed enum not int
      // need a better name for that, too.
   FILE_LIST_DIRECTORY=        0x00000001, // directory
   FILE_READ_DATA=             0x00000001, // file, pipe
   FILE_WRITE_DATA=            0x00000002, // file, pipe
   FILE_ADD_FILE=              0x00000002, // directory
   FILE_APPEND_DATA=           0x00000004, // file
   FILE_ADD_SUBDIRECTORY=      0x00000004, // directory
   FILE_CREATE_PIPE_INSTANCE=  0x00000004, // named pipe
   FILE_READ_EA=               0x00000008, // file, directory
   FILE_WRITE_EA=              0x00000010, // file, directory
   FILE_EXECUTE=               0x00000020, // file
   FILE_TRAVERSE=              0x00000020, // directory
   FILE_DELETE_CHILD=          0x00000040, // directory
   FILE_READ_ATTRIBUTES=       0x00000080, // all
   FILE_WRITE_ATTRIBUTES=      0x00000100, // all
   FILE_ALL_ACCESS= (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0x3FF),
   FILE_GENERIC_READ= (STANDARD_RIGHTS_READ | FILE_READ_DATA | FILE_READ_ATTRIBUTES | FILE_READ_EA |SYNCHRONIZE),
   FILE_GENERIC_WRITE= (STANDARD_RIGHTS_WRITE | FILE_WRITE_DATA | FILE_WRITE_ATTRIBUTES | FILE_WRITE_EA | FILE_APPEND_DATA | SYNCHRONIZE),
   FILE_GENERIC_EXECUTE= (STANDARD_RIGHTS_EXECUTE | FILE_READ_ATTRIBUTES | FILE_EXECUTE | SYNCHRONIZE),
   };

enum sharing_t {
   FILE_SHARE_EXCLUSIVE = 0,  // not in WINDOWS.H, but needed so we can use strict enums not integers
   FILE_SHARE_DELETE = 4,
   FILE_SHARE_READ = 1,
   FILE_SHARE_WRITE = 2,
   FILE_SHARE_READWRITE = 3, // not in WINDOWS.H, but used so we don't have to OR flags together.
   FILE_SHARE_WIDEOPEN = 7 // not in WINDOWS.H, but used so we don't have to OR flags together.
   };

enum creation_t {
   CREATE_NEW = 1,  // error if file already exists.
   CREATE_ALWAYS = 2,  // blows away any existing file.
   OPEN_EXISTING = 3,  // error if file doesn't already exist.
   OPEN_ALWAYS = 4,  // open or create if needed.
   TRUNCATE_EXISTING = 5  // destroys existing file, error if doesn't already exist.
   };

// enum attribute_flags {
enum file_attributes {
   // CreateFile: documented as legal flag to CreateFile etc.
   // Find: documented as result of FindFirstFile etc.
   FILE_ATTRIBUTE_READONLY=             0x00000001,  // CreateFile, Find
   FILE_ATTRIBUTE_HIDDEN=               0x00000002,  // CreateFile, Find
   FILE_ATTRIBUTE_SYSTEM=               0x00000004,  // CreateFile, Find
   FILE_ATTRIBUTE_DIRECTORY=            0x00000010,  // Find
   FILE_ATTRIBUTE_ARCHIVE=              0x00000020,  // CreateFile, Find
   FILE_ATTRIBUTE_ENCRYPTED=            0x00000040,  // CreateFile, Find
   FILE_ATTRIBUTE_NORMAL=               0x00000080,  // CreateFile, Find
   FILE_ATTRIBUTE_TEMPORARY=            0x00000100,  // CreateFile, Find
   FILE_ATTRIBUTE_SPARSE_FILE=          0x00000200,  // Find
   FILE_ATTRIBUTE_REPARSE_POINT=        0x00000400,  // Find
   FILE_ATTRIBUTE_COMPRESSED=           0x00000800,  // Find
   FILE_ATTRIBUTE_OFFLINE=              0x00001000,  // CreateFile?, Find
   FILE_ATTRIBUTE_NOT_CONTENT_INDEXED=  0x00002000,   // CreateFile
   file_attributes_max= 0xffffffff  // ensure that it's implemented as a unsigned 32-bit value
   };

// Only 2 bits left unused in CreateFile's FlagsAndAttributes parameter.

enum file_create_flags {  // used in CreateFile's FlagsAndAttributes parameter
   FILE_FLAG_OPEN_NO_RECALL=      0x00100000,
   FILE_FLAG_OPEN_REPARSE_POINT=  0x00200000,
   FILE_FLAG_POSIX_SEMANTICS=     0x01000000,
   FILE_FLAG_BACKUP_SEMANTICS=    0x02000000,
   FILE_FLAG_DELETE_ON_CLOSE=     0x04000000,
   FILE_FLAG_SEQUENTIAL_SCAN=     0x08000000,
   FILE_FLAG_RANDOM_ACCESS=       0x10000000,
   FILE_FLAG_NO_BUFFERING=        0x20000000,
   FILE_FLAG_OVERLAPPED=          0x40000000,
   FILE_FLAG_WRITE_THROUGH=       0x80000000,
   };

enum file_create_SQOS {  // used in CreateFile's FlagsAndAttributes parameter
   SECURITY_ANONYMOUS=         0,
   SECURITY_IDENTIFICATION=    0x00010000,
   SECURITY_IMPERSONATION=     0x00020000,
   SECURITY_DELEGATION=        0x00030000,
   SECURITY_CONTEXT_TRACKING=  0x00040000,
   SECURITY_EFFECTIVE_ONLY=    0x00080000,
   SECURITY_SQOS_PRESENT=      0x00100000,  // set this to enable use of the others
   SECURITY_VALID_SQOS_FLAGS=  0x001F0000    // a mask for all bits in this group
   };

enum move_flags {
   MOVEFILE_REPLACE_EXISTING=       0x00000001,
   MOVEFILE_COPY_ALLOWED=           0x00000002,
   MOVEFILE_DELAY_UNTIL_REBOOT=     0x00000004,
   MOVEFILE_WRITE_THROUGH=          0x00000008,
   // following are new for Windows 2000
   MOVEFILE_CREATE_HARDLINK=        0x00000010,
   MOVEFILE_FAIL_IF_NOT_TRACKABLE=  0x00000020
   };

const types::IO_HANDLE INVALID_FILE= reinterpret_cast<types::IO_HANDLE> (0xffffffff);
const types::IO_HANDLE INVALID_HANDLE_VALUE= reinterpret_cast<types::IO_HANDLE> (0xffffffff);
/* Note: INVALID_HANDLE_VALUE is a misnomer, since it is not used for all kernel handles.  CreateFile
   uses it, but other handles, such as CreateMutex, return NULL on failure!  So INVALID_FILE
   is a better name for this purpose.
*/

#pragma pack (push, 1)
template <typename CharType>
struct WIN32_FIND_DATA {
   file_attributes FileAttributes;
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


} //end io
}
ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
#if defined DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
#undef DIDTHAT_856a80c0_4ba5_11d4_8e10_0006296222ef
using ratwin::io::MAX_PATH;
using ratwin::io::FILE_LIST_DIRECTORY;
using ratwin::io::FILE_READ_ATTRIBUTES;
using ratwin::io::GENERIC_READ;
using ratwin::io::GENERIC_WRITE;
using ratwin::io::FILE_READ_DATA;
using ratwin::io::FILE_WRITE_DATA;
using ratwin::io::FILE_ADD_FILE;
using ratwin::io::FILE_APPEND_DATA;
using ratwin::io::FILE_ADD_SUBDIRECTORY;
using ratwin::io::FILE_CREATE_PIPE_INSTANCE;
using ratwin::io::FILE_SHARE_DELETE;
using ratwin::io::FILE_SHARE_READ;
using ratwin::io::FILE_SHARE_WRITE;
using ratwin::io::FILE_READ_EA;
using ratwin::io::FILE_WRITE_EA;
using ratwin::io::FILE_EXECUTE;
using ratwin::io::FILE_TRAVERSE;
using ratwin::io::FILE_DELETE_CHILD;
using ratwin::io::FILE_WRITE_ATTRIBUTES;
using ratwin::io::DELETE;
using ratwin::io::READ_CONTROL;
using ratwin::io::WRITE_DAC;
using ratwin::io::WRITE_OWNER;
using ratwin::io::STANDARD_RIGHTS_REQUIRED;
using ratwin::io::SYNCHRONIZE;
using ratwin::io::FILE_ALL_ACCESS;
using ratwin::io::FILE_GENERIC_READ;
using ratwin::io::FILE_GENERIC_WRITE;
using ratwin::io::FILE_GENERIC_EXECUTE;
using ratwin::io::STANDARD_RIGHTS_READ;
using ratwin::io::STANDARD_RIGHTS_WRITE;
using ratwin::io::STANDARD_RIGHTS_EXECUTE;
using ratwin::io::STANDARD_RIGHTS_ALL;
using ratwin::io::SPECIFIC_RIGHTS_ALL;
using ratwin::io::ACCESS_SYSTEM_SECURITY;
using ratwin::io::MAXIMUM_ALLOWED;
using ratwin::io::CREATE_NEW;
using ratwin::io::CREATE_ALWAYS;
using ratwin::io::OPEN_EXISTING;
using ratwin::io::OPEN_ALWAYS;
using ratwin::io::TRUNCATE_EXISTING;
using ratwin::io::FILE_ATTRIBUTE_READONLY;
using ratwin::io::FILE_ATTRIBUTE_HIDDEN;
using ratwin::io::FILE_ATTRIBUTE_SYSTEM;
using ratwin::io::FILE_ATTRIBUTE_DIRECTORY;
using ratwin::io::FILE_ATTRIBUTE_ARCHIVE;
using ratwin::io::FILE_ATTRIBUTE_ENCRYPTED;
using ratwin::io::FILE_ATTRIBUTE_NORMAL;
using ratwin::io::FILE_ATTRIBUTE_TEMPORARY;
using ratwin::io::FILE_ATTRIBUTE_SPARSE_FILE;
using ratwin::io::FILE_ATTRIBUTE_REPARSE_POINT;
using ratwin::io::FILE_ATTRIBUTE_COMPRESSED;
using ratwin::io::FILE_ATTRIBUTE_OFFLINE;
using ratwin::io::FILE_ATTRIBUTE_NOT_CONTENT_INDEXED;
using ratwin::io::FILE_FLAG_OPEN_NO_RECALL;
using ratwin::io::FILE_FLAG_OPEN_REPARSE_POINT;
using ratwin::io::FILE_FLAG_POSIX_SEMANTICS;
using ratwin::io::FILE_FLAG_BACKUP_SEMANTICS;
using ratwin::io::FILE_FLAG_DELETE_ON_CLOSE;
using ratwin::io::FILE_FLAG_SEQUENTIAL_SCAN;
using ratwin::io::FILE_FLAG_RANDOM_ACCESS;
using ratwin::io::FILE_FLAG_NO_BUFFERING;
using ratwin::io::FILE_FLAG_OVERLAPPED;
using ratwin::io::FILE_FLAG_WRITE_THROUGH;
using ratwin::io::SECURITY_ANONYMOUS;
using ratwin::io::SECURITY_IDENTIFICATION;
using ratwin::io::SECURITY_IMPERSONATION;
using ratwin::io::SECURITY_DELEGATION;
using ratwin::io::SECURITY_CONTEXT_TRACKING;
using ratwin::io::SECURITY_EFFECTIVE_ONLY;
using ratwin::io::SECURITY_SQOS_PRESENT;
using ratwin::io::SECURITY_VALID_SQOS_FLAGS;
using ratwin::io::MOVEFILE_REPLACE_EXISTING;
using ratwin::io::MOVEFILE_COPY_ALLOWED;
using ratwin::io::MOVEFILE_DELAY_UNTIL_REBOOT;
using ratwin::io::MOVEFILE_WRITE_THROUGH;
using ratwin::io::MOVEFILE_CREATE_HARDLINK;
using ratwin::io::MOVEFILE_FAIL_IF_NOT_TRACKABLE;
using ratwin::io::INVALID_HANDLE_VALUE;
#endif
// ## END Generated Code

#endif


// The Repertoire Project copyright 2000 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\directory_list.cpp
// Revision: post - public build 5, shipped on 29-Feb-2000 or later

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\directory_list.h"
#include "ratwin\io\file.h"
#include "ratwin\utilities.h"
#include "classics\exception.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tristate directory_list::isUnicode= Maybe;
static const ratwin::types::HANDLE closed= reinterpret_cast<ratwin::types::HANDLE>(-1);
static const char FNAME[] = __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

template <typename CharType>
void remove_trailing_slash (classics::generic_string<CharType>& s)
 {
 int n= s.elcount() - 1;
 if (n >= 0 && s[n] == CharType('\\'))
    s.resize (n);
 }
 
}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void common_error_code (int line, int errorcode, const ustring& param)
 {
 win_exception X ("Classics", FNAME, line, errorcode);
 X.add_key (L"parameter", param);
 X += L"Error constructing directory_list object.";
 throw X;
 __assume (0);
 }
 
// =========================================

directory_list::directory_list (filename_t scheme)
 : handle(closed), find_data_wide(0), directory(scheme)
 {
 bool is_root= scheme.path_count()==1 && scheme.absolute();
 bool wantdir= (scheme.name_count()==0) && (scheme.path_count() > 0) && !is_root;
 directory.remove_name_this();
 if (isUnicode == Maybe) {
    // Try Unicode
    find_data_wide= new ratwin::io::WIN32_FIND_DATA<wchar_t>;
    classics::wstring s= scheme.text();
    if (wantdir) remove_trailing_slash (s);
    handle= ratwin::io::FindFirstFile (s.c_str(), *find_data_wide);
    if (handle == closed) {
       int errorcode= ratwin::util::GetLastError();
       if (errorcode == win_exception::call_not_implemented_error) {
          isUnicode= No;
          delete find_data_wide;
          goto narrow_case;
          }
       else if (errorcode == 3 || errorcode == 2) {
          shutdown();  // an empty result, not an error;
          return;
          }
       common_error_code (__LINE__, errorcode, s);
       __assume (0);
       }
    isUnicode= Yes;
    }
 else if (isUnicode == Yes) {
    find_data_wide= new ratwin::io::WIN32_FIND_DATA<wchar_t>;
    classics::wstring s= scheme.text();
    if (wantdir) remove_trailing_slash (s);
    handle= ratwin::io::FindFirstFile (s.c_str(), *find_data_wide);
    if (handle == closed) {
       int errorcode= ratwin::util::GetLastError();
       if (errorcode == 3 || errorcode == 2) {
          shutdown();  // an empty result, not an error;
          return;
          }
       common_error_code (__LINE__, errorcode, s);
       __assume (0);
       }
    }
 else {  //must be No
    narrow_case:
    find_data_narrow= new ratwin::io::WIN32_FIND_DATA<char>;
    classics::string s= scheme.text();
    if (wantdir) remove_trailing_slash (s);
    handle= ratwin::io::FindFirstFile (s.c_str(), *find_data_narrow);
    if (handle == closed) {
       int errorcode= ratwin::util::GetLastError();
       if (errorcode == 3 || errorcode == 2) {
          shutdown();  // an empty result, not an error;
          return;
          }
       common_error_code (__LINE__, errorcode, s);
       __assume (0);
       }
    }

 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void directory_list::shutdown()
 {
 if (!OK())  return;  //nothing to do.
 ratwin::io::FindClose (handle);
 handle= closed;
 if (isUnicode == Yes)  delete find_data_wide;
 else if (isUnicode == No)  delete find_data_narrow;
 find_data_narrow= 0;  //either way, since it's the same location.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool directory_list::next()
 {
 bool result= (isUnicode == Yes) ? ratwin::io::FindNextFile(handle,*find_data_wide) : ratwin::io::FindNextFile(handle,*find_data_narrow);
 if (!result)  shutdown();
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void directory_list::verify_OK() const
 {
 if (!OK()) {
    exception X ("Classics", "Directory List object is closed/finished", FNAME, __LINE__);
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__int64 directory_list::creation_time() const
 {
 verify_OK();
 return find_data_wide->ftCreationTime;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__int64 directory_list::last_access_time() const
 {
 verify_OK();
 return find_data_wide->ftLastAccessTime;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__int64 directory_list::last_write_time() const
 {
 verify_OK();
 return find_data_wide->ftLastWriteTime;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__int64 directory_list::filesize() const
 {
 verify_OK();
 union {
    unsigned long part[2];
    __int64 whole;
    };
 // structure has these backwards
 part[0]= find_data_wide->FileSizeLow;
 part[1]= find_data_wide->FileSizeHigh;
 return whole;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t directory_list::filename() const
 {
 verify_OK();
 filename_t result= directory;
 if (isUnicode == Yes)  result.set_name_this (find_data_wide->FileName);
 else result.set_name_this (find_data_narrow->FileName);
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

filename_t directory_list::shortname() const
 {
 verify_OK();
 filename_t result= directory;
 if (isUnicode == Yes)  result.set_name_this (find_data_wide->AlternateFileName);
 else result.set_name_this (find_data_narrow->AlternateFileName);
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

flagword<ratwin::io::file_attributes> directory_list::attributes() const
 {
 verify_OK();
 return find_data_wide->FileAttributes;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP



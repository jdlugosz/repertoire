// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\directory_list.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\filename_t.h"
#include "ratwin\io\file=struct.h"
#include "classics\misc_types.h"  //need tristate

STARTWRAP
namespace classics {

class directory_list {
   static tristate isUnicode;
   ratwin::types::HANDLE handle;
   union {
      ratwin::io::WIN32_FIND_DATA<char>* find_data_narrow;
      ratwin::io::WIN32_FIND_DATA<wchar_t>* find_data_wide;
      };
   filename_t directory;
   CLASSICS_EXPORT void shutdown();
   directory_list (const directory_list&);  //not defined
   void operator= (const directory_list&);  //not defined
   void verify_OK() const;
public:
   CLASSICS_EXPORT directory_list (filename_t scheme);
   ~directory_list()  { shutdown(); }
   CLASSICS_EXPORT bool next();  //iterate -- go on to the next file.
   bool OK() const  { return handle != reinterpret_cast<ratwin::types::HANDLE>(-1); }  //test current state valid or End.
   CLASSICS_EXPORT filename_t filename() const;  //name of the current file
   CLASSICS_EXPORT filename_t shortname() const;  //short alias name of the current file
   CLASSICS_EXPORT __int64 filesize() const;
   CLASSICS_EXPORT __int64 creation_time() const;
   CLASSICS_EXPORT __int64 last_access_time() const;
   CLASSICS_EXPORT __int64 last_write_time() const;
   CLASSICS_EXPORT flagword<ratwin::io::file_attributes> attributes() const;
   };


} //end namespace classics
ENDWRAP


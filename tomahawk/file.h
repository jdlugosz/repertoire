// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\file.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_file_INCLUDED
#define TOMAHAWK_file_INCLUDED

#include "tomahawk\base.h"
#include "ratwin\io\file.h"
#include "classics\string.h"

STARTWRAP
namespace tomahawk {

class file {
   ratwin::types::HANDLE H;
public:
   file() : H(0) {}
   ~file()  { close(); }
   ratwin::types::HANDLE h() const  { return H; }
   class open_spec;
   TOMAHAWK_EXPORT bool open (const open_spec&, const classics::string& filename);
   TOMAHAWK_EXPORT bool open (const open_spec&, classics::wstring filename);
   TOMAHAWK_EXPORT void close();
   TOMAHAWK_EXPORT __int64 size() const;
   // >> members to wrap all the primitives I do with files: read/write/etc.
   };

class file::open_spec {
   ratwin::io::access_t access;
   ratwin::io::sharing_t share;
   ratwin::io::creation_t how;
   ulong even_more_flags;
   bool CanFail;
   friend file;
public:
   void set (ratwin::io::access_t x) { access= x; }
   void set (ratwin::io::sharing_t x) { share= x; }
   void set (ratwin::io::creation_t x) { how= x; }
   void set (ratwin::io::attribute_flags x)  { even_more_flags |= x; }
   void clear (ratwin::io::attribute_flags x)  { even_more_flags &=~x; }
   void can_fail()  { CanFail= true; }
   void cant_fail()  { CanFail= false; }
   open_spec();
   };


} // end of tomahawk
ENDWRAP

#endif








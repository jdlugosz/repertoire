// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\file_factory.h
// Revision: public build 6, shipped on 28-Nov-1999

// This is copied from the file class in Tomahawk.  A full analysis and
// redesign may follow.

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\io\file.h"
#include "classics\filename_t.h"

STARTWRAP
namespace classics {

class file_factory {
protected:
   ratwin::io::access_t access;
   ratwin::io::sharing_t share;
   ratwin::io::creation_t how;
   ulong even_more_flags;
   bool CanFail;
public:
   void set (ratwin::io::access_t x) { access= x; }
   unsigned test (ratwin::io::access_t x) const { return access&x; }
   void set (ratwin::io::sharing_t x) { share= x; }
   unsigned test (ratwin::io::sharing_t x) const { return share&x; }
   void set (ratwin::io::creation_t x) { how= x; }
   unsigned test (ratwin::io::creation_t x) const { return how&x; }
   void set (ratwin::io::attribute_flags x)  { even_more_flags |= x; }
   unsigned test (ratwin::io::attribute_flags x) const { return even_more_flags&x; }
   void clear (ratwin::io::attribute_flags x)  { even_more_flags &=~x; }
   void can_fail()  { CanFail= true; }
   void cant_fail()  { CanFail= false; }
   enum construct_mode_t { Read, ReadWrite };
   CLASSICS_EXPORT file_factory (construct_mode_t);
   CLASSICS_EXPORT ratwin::types::HANDLE Create (const filename_t& name) const;
   };


} //end namespace classics
ENDWRAP



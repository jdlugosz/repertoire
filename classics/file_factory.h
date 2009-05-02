// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\file_factory.h
// Revision: public build 9, shipped on 18-Oct-2006

// This is copied from the file class in Tomahawk.  A full analysis and
// redesign may follow.

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\io\file=struct.h"
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
   // need to improve the access_t.  You have individual bits OR complete packages.
   // maybe redesign to use flagwords on all (separate) enums?  Then package them together into params.
   void set (ratwin::io::sharing_t x) { share= x; }
   unsigned test (ratwin::io::sharing_t x) const { return share&x; }
   void set (ratwin::io::creation_t x) { how= x; }
   unsigned test (ratwin::io::creation_t x) const { return how&x; }
   void set (ratwin::io::file_attributes x)  { even_more_flags |= x; }
   unsigned test (ratwin::io::file_attributes x) const { return even_more_flags&x; }
   void set (ratwin::io::file_create_flags x)  { even_more_flags |= x; }
   unsigned test (ratwin::io::file_create_flags x) const { return even_more_flags&x; }
   void set (ratwin::io::file_create_SQOS x)  { even_more_flags &= ~ ratwin::io::SECURITY_VALID_SQOS_FLAGS;  even_more_flags &= (x|ratwin::io::SECURITY_SQOS_PRESENT); }
   unsigned test (ratwin::io::file_create_SQOS x) const { return even_more_flags&x; }
   ratwin::io::file_create_SQOS get_SQOS() const { return static_cast<ratwin::io::file_create_SQOS>( even_more_flags & ratwin::io::SECURITY_VALID_SQOS_FLAGS ); }
   void clear (ratwin::io::file_attributes x)  { even_more_flags &=~x; }
   void clear (ratwin::io::file_create_flags x)  { even_more_flags &=~x; }
   void clear_SQOS() { even_more_flags &= ~ ratwin::io::SECURITY_VALID_SQOS_FLAGS;  }
   void can_fail()  { CanFail= true; }
   void cant_fail()  { CanFail= false; }
   enum construct_mode_t { Read, ReadWrite };
   CLASSICS_EXPORT file_factory (construct_mode_t);
   CLASSICS_EXPORT ratwin::types::IO_HANDLE Create (const filename_t& name) const;
   };


} //end namespace classics
ENDWRAP



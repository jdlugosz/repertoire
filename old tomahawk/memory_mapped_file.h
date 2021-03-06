// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\memory_mapped_file.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_memory_mapped_file_INCLUDED
#define TOMAHAWK_memory_mapped_file_INCLUDED

#include "tomahawk\file.h"

STARTWRAP
namespace tomahawk {

class memory_mapped_file {
   file f;
   ratwin::types::HANDLE mapper_object;
   void* map;
public:
   TOMAHAWK_EXPORT memory_mapped_file (const classics::wstring& name, bool readonly=false);
   memory_mapped_file (const classics::string& name, bool readonly=false);
   TOMAHAWK_EXPORT ~memory_mapped_file();
   void* get_map() const  { return map; }
   TOMAHAWK_EXPORT int size() const;
   };


} // end of tomahawk
ENDWRAP

#endif








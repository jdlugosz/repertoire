// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\copy_semantics.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\copy_semantics.h"
#include <string.h>

STARTWRAP
namespace classics {


void copy_semantics_s::initialize_elements (void* dest, int count) const
 {
 memset (dest, 0, count*Elsize);
 }
 
void copy_semantics_s::initialize_elements (void* dest, const void* src, int count) const
 {
#ifdef _DEBUG
 if (count!=0)
#endif
	 memcpy (dest, src, count*Elsize);
 }

void copy_semantics_s::copy_elements (void* dest, const void* src, int count) const
 {
 memmove (dest, src, count*Elsize);
 }

void copy_semantics_s::move_elements (void* dest, void* src, int count) const
 {
 memmove (dest, src, count*Elsize);
 }




}
ENDWRAP


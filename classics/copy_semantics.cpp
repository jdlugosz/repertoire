// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\vararray.cpp
// Revision: public build 6, shipped on 28-Nov-1999

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


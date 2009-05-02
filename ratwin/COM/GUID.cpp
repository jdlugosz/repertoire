// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID.cpp
// Revision: 

#define RATWIN_EXPORT __declspec(dllexport)
#include "ratwin\COM\GUID.h"

STARTWRAP
namespace ratwin {

bool operator== (const GUID& left, const GUID& right)
 {
 return left.inline_eq (right);
 }

}  //end of namespace
ENDWRAP




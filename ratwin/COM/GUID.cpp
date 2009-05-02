// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\GUID.cpp
// Revision: public build 5, shipped on 8-April-1999

#define RATWIN_EXPORT __declspec(dllexport)
#include "ratwin\COM\GUID.h"

// outside of namespace
bool operator== (const _GUID& left, const _GUID& right)
 {
 return inline_eq (left, right);
 }


STARTWRAP
namespace ratwin {


}  //end of namespace
ENDWRAP




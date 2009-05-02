// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.cpp
// Revision: public build 5, shipped on 8-April-1999

#define RATWIN_EXPORT __declspec(dllexport)

#include "ratwin\utilities.h"

STARTWRAP
namespace ratwin {
namespace util {

types::HINSTANCE get_Instance()
 {
 static types::HINSTANCE retval= GetModuleHandle();
 return retval;
 }

}}
ENDWRAP


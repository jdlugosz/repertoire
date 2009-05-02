// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.cpp
// Revision: public build 6, shipped on 28-Nov-1999

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


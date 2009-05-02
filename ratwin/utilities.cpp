// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.cpp
// Revision: public build 9, shipped on 18-Oct-2006

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


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\utilities.cpp
// Revision: public build 8, shipped on 11-July-2006

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


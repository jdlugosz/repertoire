// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\HWND_vpapa.h"

namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HWND_vpapa::HWND_vpapa()
 :WindowHandle(0)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void HWND_vpapa::report_error (const classics::exception& X)
 {
 X.show();
 }

}


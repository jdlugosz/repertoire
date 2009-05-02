// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\misc_API.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\ustring.h"
#include "classics\exception.h"
#include "ratwin\COM\guid.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ustring CLASSICS_EXPORT GetModuleFileName (ratwin::types::HINSTANCE);
ustring CLASSICS_EXPORT as_string (const ratwin::GUID&);

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP



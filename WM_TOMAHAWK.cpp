// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\MSG\WM_TOMAHAWK.h"
#include "ratwin\message.h"

namespace tomahawk {
namespace MSG {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static unsigned generate()
 {
 return ratwin::message::RegisterWindowMessage ("WM_TOMAHAWK");
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

unsigned WM_TOMAHAWK_msg::get_TOMAHAWK_id()
 {
 static unsigned id= generate();
 return id;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}}


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\MSG\WM_TOMAHAWK.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\MSG\WM_TOMAHAWK.h"
#include "ratwin\message.h"

namespace tomahawk {
namespace MSG {

using ratwin::WM_constants::messages;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static unsigned generate()
 {
 return ratwin::message::RegisterWindowMessage ("WM_TOMAHAWK");
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const messages WM_TOMAHAWK_msg::message_constant= static_cast<messages>(generate());

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

unsigned WM_TOMAHAWK_msg::get_TOMAHAWK_id()
 {
 static unsigned id= generate();
 return id;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}}


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\MSG\WM_INITMENU.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
namespace MSG {

struct WM_INITMENU_msg : public ratwin::message::MSG_base {
   ratwin::types::HMENU Menu;
   int unused;
   inline ratwin::types::HMENU sending_menu() const { return Menu; }
   // this goes in every message struct--just change the constant used to match.
   static const ratwin::WM_constants::messages message_constant= ratwin::WM_constants::WM_INITMENU;
   };

}}


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\MSG\WM_TOMAHAWK.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
namespace MSG {

struct WM_TOMAHAWK_msg : public ratwin::message::MSG_base {
   short SubCode;
   short param1;
   long param2;
   enum codes {
      pre_translate_message
      };
   codes notification_code() const { return static_cast<codes>(SubCode); }
   TOMAHAWK_EXPORT static unsigned get_TOMAHAWK_id();
   static const ratwin::WM_constants::messages message_constant;
   };

}}



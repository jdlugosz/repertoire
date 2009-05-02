// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#include "ratwin\message=struct.h"

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
   };

}}



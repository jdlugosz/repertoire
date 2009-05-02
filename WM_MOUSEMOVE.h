// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
namespace MSG {

struct WM_MOUSEMOVE_msg : public ratwin::message::MSG_base {
   unsigned KeyIndicators;
   short XPos;
   short YPos;
   enum KeyIndicators_t {
      // naturally, these have nothing to do with existing codes (e.g. VK_modifier) for the same meaning.
      LButton= 1,   // Left mouse button is down
      RButton= 2,   // Right mouse button is down
      MButton= 16,  // Middle mouse button is down
      Shift= 4,     // Shift key is held down (e.g. "shift click")
      Control= 8    // Control key is held down
      };
   inline KeyIndicators_t key_indicators() const { return static_cast<KeyIndicators_t>(KeyIndicators); }
   inline ratwin::types::POINT mouse_position() const
      { return ratwin::types::POINT (XPos,YPos); }
   // this goes in every message struct--just change the constant used to match.
   static const ratwin::WM_constants::messages message_constant= ratwin::WM_constants::WM_MOUSEMOVE;
   };


}}



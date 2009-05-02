// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\window=struct.h"

namespace tomahawk {
namespace MSG {

struct WM_SIZE_msg : public ratwin::message::MSG_base {
   unsigned ResizeFlag;  // SIZE_MAXHIDE, SIZE_MAXIMIZED, SIZE_MAXSHOW, SIZE_MINIMIZED, 
   unsigned short NewClientWidth;
   unsigned short NewClientHeight;
   inline ratwin::window::SIZE_window notification_code() 
      { return static_cast<ratwin::window::SIZE_window>(ResizeFlag); }
   inline ratwin::types::POINT client_size() const
      { return ratwin::types::POINT (NewClientWidth,NewClientHeight); }
   };

}}



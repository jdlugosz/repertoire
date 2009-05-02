// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\MSG\WM_SIZE.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\window=struct.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
namespace MSG {

struct WM_SIZE_msg : public ratwin::message::MSG_base {
   unsigned ResizeFlag;  // SIZE_MAXHIDE, SIZE_MAXIMIZED, SIZE_MAXSHOW, SIZE_MINIMIZED,
   unsigned short NewClientWidth;
   unsigned short NewClientHeight;
   inline ratwin::window::SIZE_window notification_code() const
      { return static_cast<ratwin::window::SIZE_window>(ResizeFlag); }
   inline ratwin::types::POINT client_size() const
      { return ratwin::types::POINT (NewClientWidth,NewClientHeight); }
   static const ratwin::WM_constants::messages message_constant= ratwin::WM_constants::WM_SIZE;
   };

}}



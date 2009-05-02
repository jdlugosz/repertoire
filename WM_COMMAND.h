// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#include "ratwin\message=struct.h"

namespace tomahawk {
namespace MSG {

struct WM_COMMAND_msg : public ratwin::message::MSG_base {
   unsigned short CommandID;
      // CommandID is the ID number assigned to the button pressed, the menu item chosen, etc.
      // For controls that only send one command (like a button) this is typically the same as that
      // control's Child ID.  For controls that send many commands (like a toolbar) the CommandID
      // is not the same as the control's Child ID, or (like a menu) the control itself does not even
      // a child of the receiving window.
   unsigned short Other; 
   // 'other' param is normally 1 for accelerator key, 0 for button.  But ComboBox notifications use
   // this field as a notification code.
   ratwin::types::HWND ControlWindow;  // the window sending the message (if applicable).
   inline command_ID() const { return CommandID; }
   inline ratwin::types::HWND sending_window() const { return ControlWindow; }
   inline unsigned short notification_code() const { return Other; }
   };


}}


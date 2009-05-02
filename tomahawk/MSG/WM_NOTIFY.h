// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\WM_constants.h"  // for NMHDR

namespace tomahawk {
namespace MSG {

struct WM_NOTIFY_msg : public ratwin::message::MSG_base {
   int ChildID;  // ID of common control sending the message
   const ratwin::WM_constants::NMHDR* info;
   inline int child_ID() const { return ChildID; }
   inline ratwin::types::HWND sending_window() const { return info->sender; }
   inline unsigned notification_code() const { return info->code; }
   };

}}


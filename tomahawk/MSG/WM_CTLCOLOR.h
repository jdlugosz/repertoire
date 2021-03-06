// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\MSG\WM_CTLCOLOR.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\message=struct.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
namespace MSG {

struct WM_CTLCOLOR_msg : public ratwin::message::MSG_base {
   ratwin::types::HDC hdc;
   ratwin::types::HWND control;
   inline ratwin::types::HDC target_DC() const { return hdc; }
   inline ratwin::types::HWND sending_window() const { return control; }
   // this goes in every message struct--just change the constant used to match.
   static const ratwin::WM_constants::messages message_constant= ratwin::WM_constants::WM_CTLCOLOR;
   };

}}




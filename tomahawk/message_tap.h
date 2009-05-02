// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.h
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "ratwin\message=struct.h"
#include "classics\closure.h"
#include "tomahawk\HWND_vpapa.h"

STARTWRAP
namespace tomahawk {

class message_tap : virtual public HWND_vpapa {
   long (__stdcall* OldWndProc)(ratwin::message::sMSG);
   const classics::member_callback_thunk<message_tap, long, ratwin::message::sMSG> EntryPoint;
   bool UnhookASAP;
   long SaneCheck;
   long hook_handler (ratwin::message::sMSG msg);
   void prevent_duplicate_hook() const;
protected:
   unsigned short LastMessage;  // unhook when I see this.
public:
   void sane_check() const;
   TOMAHAWK_EXPORT ratwin::window::WNDPROC_2 get_WndProc();
   TOMAHAWK_EXPORT message_tap();
   TOMAHAWK_EXPORT virtual ~message_tap();
   TOMAHAWK_EXPORT void hook (ratwin::types::HWND);
   TOMAHAWK_EXPORT bool unhook (bool force=true);
   void unhook_when_possible() { UnhookASAP= true;  }
//   TOMAHAWK_EXPORT virtual long handle_message (ratwin::message::sMSG& msg) =0;
   TOMAHAWK_EXPORT virtual int pre_translate_message (const ratwin::message::MSG& msg); // 0:no clue, 1:done&ate it, 2:done&proceed
   TOMAHAWK_EXPORT virtual void on_attach();  // called when hooked.
   TOMAHAWK_EXPORT long call_old_wndproc (ratwin::message::sMSG& msg);
   TOMAHAWK_EXPORT void set_window_handle (ratwin::types::HWND);
   };

}
ENDWRAP


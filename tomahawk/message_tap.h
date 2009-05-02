// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "ratwin\message=struct.h"
#include "classics\pointers.h"
#include "classics\closure.h"

STARTWRAP
namespace tomahawk {

class __single_inheritance message_tap : public classics::can_handle {
   ratwin::types::HWND WindowHandle;
   classics::handle <message_tap> WindowOwnsMe;  // on behalf of the (valid) WindowHandle
   long (__stdcall* OldWndProc)(ratwin::message::sMSG);
   const classics::member_callback_thunk<message_tap, long, ratwin::message::sMSG> EntryPoint;
   // disable copying
   message_tap (const message_tap&);  // never defined
   void operator= (const message_tap&); // never defined
   long hook_handler (ratwin::message::sMSG msg);
   void prevent_duplicate_hook() const;
protected:
   unsigned short LastMessage;  // unhook when I see this.
public:
   typedef long (__stdcall* Proc)(ratwin::message::sMSG);
   TOMAHAWK_EXPORT Proc get_WndProc();
   TOMAHAWK_EXPORT message_tap();
   TOMAHAWK_EXPORT virtual ~message_tap();
   TOMAHAWK_EXPORT void hook (ratwin::types::HWND);
   TOMAHAWK_EXPORT bool unhook();
   TOMAHAWK_EXPORT virtual long handle_message (ratwin::message::sMSG& msg);
   TOMAHAWK_EXPORT virtual bool translate_message (const ratwin::message::sMSG& msg);
   TOMAHAWK_EXPORT virtual void on_attach();  // called when hooked.
   TOMAHAWK_EXPORT long call_old_wndproc (ratwin::message::sMSG& msg);
   ratwin::types::HWND window_handle() { return WindowHandle; }
   TOMAHAWK_EXPORT void set_window_handle (ratwin::types::HWND);
   };

}


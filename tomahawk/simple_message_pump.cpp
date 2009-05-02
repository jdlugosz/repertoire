// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\simple_message_pump.h"
#include "ratwin\message.h"
#include "tomahawk\MSG\WM_TOMAHAWK.h"
#include "ratwin\window.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
using namespace ratwin::message;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

simple_message_pump::simple_message_pump()
 {
 // does nothing that's not built-in.  Non-inline to optimize for space.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int simple_message_pump::pumpit() throw()
 {
 try {
    return mainloop();
    }
 catch (classics::exception& X) {
    X ("Tomahawk", "Exception caught in message pump", __FILE__, __LINE__);
    report_error (X);
    }
 catch (std::exception& E) {
    classics::exception X ("Tomahawk", "Exception caught in message pump", __FILE__, __LINE__);
    X += E.what();
    report_error (X);
    }
 catch (...) {
    classics::exception X ("Tomahawk", "Unknown Exception caught in message pump", __FILE__, __LINE__);
    report_error (X);
    }
 return -1;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int simple_message_pump::mainloop()
 {
 ratwin::message::MSG msg;
 while ( GetMessage(msg) ) {
    if (msg.hwnd == 0)  thread_message (msg);
    else {
       if (!pre_translate (msg)) {  // check IsDialog,  TranslateAccelerator
          translate_key_event(msg);  // Win32 TranslateMessage
          DispatchMessage(msg); 
          }
       }
    }
 return (msg.wParam);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool simple_message_pump::pre_translate (ratwin::message::MSG& msg)
 {
 using namespace ratwin::WM_constants;
 if (msg.message < WM_KEYFIRST || msg.message > WM_KEYLAST)  return false;  // to speed it up, only test these messages.
 using MSG::WM_TOMAHAWK_msg;
 static unsigned WM_TOMAHAWK= WM_TOMAHAWK_msg::get_TOMAHAWK_id();
 WM_TOMAHAWK_msg x;
 x.hwnd= msg.hwnd;
 x.message= WM_TOMAHAWK;
 x.SubCode= x.pre_translate_message;
 x.param2= reinterpret_cast<long>(&msg);
 // Find out if anybody wants it
 while (x.hwnd) {
    int code= ratwin::window::SendMessage (MSG_cast<ratwin::message::MSG>(x));  // relies on DefWindProc returning 0 for unknown messages.
    if (code == 1) return true;
    if (code == 2) return false;
    // if code==0 keep looking
    x.hwnd= ratwin::window::GetAncestor(x.hwnd, ratwin::window::GA_PARENT);  // requires Win98 or later, NT4sp4 or later.
    }
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool simple_message_pump::translate_key_event (ratwin::message::MSG& msg)
 {
 return ratwin::message::TranslateMessage (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool simple_message_pump::report_error (const classics::exception& X)
 {
 X.show();
 return false;  // not fatal.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}


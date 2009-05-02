// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_tap.h"
#include "ratwin\window.h"
#include "classics\exception.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\MSG\WM_TOMAHAWK.h"
#include "classics\string_ios.h"

namespace tomahawk {

const char FNAME[]= __FILE__;
using classics::exception;
using classics::wFmt;
const long SaneMask= 0x19F52204;  // a random number.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::prevent_duplicate_hook() const
 {
 if (WindowHandle) {
    exception X ("Tomahawk", "Duplicate hook", FNAME, __LINE__);
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_tap::message_tap()
 : WindowHandle(0), OldWndProc(0), EntryPoint (this, &message_tap::hook_handler), 
   LastMessage (ratwin::WM_constants::WM_NCDESTROY), UnhookASAP(false),
   SaneCheck(SaneMask^reinterpret_cast<long>(this))
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_tap::~message_tap()
 {
 if (WindowHandle) {
     // this SHOULD HAVE been done already, because the Window owns this object!
     // but to be hardened against misuse, check again anyway.
    exception X ("Tomahawk", "Bug found: object improperly destroyed.", __FILE__, __LINE__);
    report_error (X);
    // If you get this, it might mean that you did not use the smart-pointer mechanism to control
    // the lifetime, but caused it to be destroyed before all references were dropped.
    unhook();
    }
 if (get_reference_count()) {
    exception X ("Tomahawk", "Bug found: object improperly destroyed.", __FILE__, __LINE__);
    report_error (X);
    // If you get this, it might mean that you did not use the smart-pointer mechanism to control
    // the lifetime, but caused it to be destroyed before all references were dropped.
    }
 SaneCheck= 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::on_attach()
 {
 // does nothing here.  Virtual function for derived classes to use.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::hook (ratwin::types::HWND window)
 {
 if (window == WindowHandle)  return;  // redundant, harmless.
 prevent_duplicate_hook();
 using namespace ratwin::window;
 WindowHandle= window;
 WindowOwnsMe= this;
 OldWndProc= static_cast<WNDPROC_2>( SetWindowLong (window, GWL_WNDPROC, EntryPoint.callptr()) );
 on_attach();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::window::WNDPROC_2 message_tap::get_WndProc()
 {
 prevent_duplicate_hook();
 return EntryPoint.callptr();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::set_window_handle (ratwin::types::HWND window)
 {
 if (window == WindowHandle)  return;  // redundant, harmless.
 prevent_duplicate_hook();
 WindowHandle= window;
 on_attach(); 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool message_tap::unhook (bool force)
 {
 if (!WindowHandle)  return true;  // nothing to do.
 using namespace ratwin::window;
 WNDPROC_2 current= static_cast<WNDPROC_2>( GetWindowLong (WindowHandle, GWL_WNDPROC) );
 bool graceful= (current == EntryPoint.callptr());
 if (!graceful && !force)  return false;  // can't do it.
 SetWindowLong (WindowHandle, GWL_WNDPROC, graceful ? OldWndProc : &::DefWindowProcA);
 // reset the data members
 OldWndProc= 0;
 WindowHandle= 0;
 WindowOwnsMe= 0;  // can cause deletion!!! Must do this last.  No member access allowed past this point.
 return graceful;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::sane_check() const
// This is not 100% reliable, but it is a sanity check to catch a bug
// where the object gets messages after it has been deleted.
 {
 if (SaneCheck != (SaneMask^reinterpret_cast<long>(this))) {
    exception X ("Tomahawk", "Invalid object", __FILE__, __LINE__);
    wFmt(X) << L"The memory at " << (void*)this << L" is not a message_tap object.";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::hook_handler (ratwin::message::sMSG msg)
// This is where the message hits the class.
 {
 using tomahawk::MSG::WM_TOMAHAWK_msg;
 sane_check();
 // the above is OUTSIDE the try block, so it does indeed propagate out.
 try {
    if (!WindowHandle)  {  // automatically set upon first message.
       WindowHandle= msg.hwnd;
       on_attach(); 
       }
    static unsigned const WM_TOMAHAWK= WM_TOMAHAWK_msg::get_TOMAHAWK_id();
    if (msg.message == WM_TOMAHAWK) {
       const WM_TOMAHAWK_msg& Tmsg= ratwin::message::MSG_cast<WM_TOMAHAWK_msg>(msg);
       if (Tmsg.notification_code() == WM_TOMAHAWK_msg::pre_translate_message) {
          ratwin::message::MSG* premessage= reinterpret_cast<ratwin::message::MSG*>(Tmsg.param2);
          return pre_translate_message (*premessage);
          }
       }
    int result= handle_message (msg);
    if (msg.message == LastMessage) unhook();  // May have triggered deletion!
    else if (UnhookASAP) unhook(false);  // *try* to unhook after every message.
    return result;
    }
 catch (exception& X)
    {
    X ("Tomahawk", "Exception caught in message handler", __FILE__, __LINE__);
    report_error (X);
    }
 catch (std::exception& E)
    {
    exception X ("Tomahawk", "Exception caught in message handler", __FILE__, __LINE__);
    X += E.what();
    report_error (X);
    }
 catch (...) {
    exception X ("Tomahawk", "Unknown Exception caught in message handler", __FILE__, __LINE__);
    report_error (X);
    }
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::handle_message (ratwin::message::sMSG& msg)
// not inline because it's virtual.
 {
 return call_old_wndproc (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int message_tap::pre_translate_message (const ratwin::message::MSG&)
 {
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::call_old_wndproc (ratwin::message::sMSG& msg)
 {
 if (OldWndProc)
    return ratwin::window::CallWindowProc (OldWndProc, msg);
 else return ratwin::window::DefWindowProc (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::report_error (const classics::exception& X)
 {
 X.show();
 }

}


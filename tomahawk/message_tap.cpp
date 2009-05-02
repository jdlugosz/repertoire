// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_tap.h"
#include "ratwin\window.h"
#include "classics\exception.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {

const char FNAME[]= __FILE__;
using classics::exception;

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
 : WindowHandle(0), OldWndProc(0), EntryPoint (this, &message_tap::hook_handler), LastMessage (ratwin::WM_constants::WM_NCDESTROY)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_tap::~message_tap()
 {
 if (WindowHandle) {
     // this SHOULD HAVE been done already, because the Window owns this object!
     // but to be hardened against misuse, check again anyway.
    // >> issue a warning here.
    unhook();
    }
 // >> could also check to make sure Lifetime object says it's OK, to catch manual deletion before the smart pointer said it can. 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_tap::on_attach()
 {
 // does nothing here.  Virtual function derived classes to use.
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

bool message_tap::unhook()
 {
 if (!WindowHandle)  return true;  // nothing to do.
 using namespace ratwin::window;
 WNDPROC_2 current= static_cast<WNDPROC_2>( GetWindowLong (WindowHandle, GWL_WNDPROC) );
 bool graceful= (current == EntryPoint.callptr());
 SetWindowLong (WindowHandle, GWL_WNDPROC, graceful ? OldWndProc : &::DefWindowProcA);
 // reset the data members
 OldWndProc= 0;
 WindowHandle= 0;
 WindowOwnsMe= 0;  // can cause deletion!!! Must do this last.  No member access allowed past this point.
 return graceful;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::hook_handler (ratwin::message::sMSG msg)
// This is where the message hits the class.
 {
 if (!WindowHandle)  {  // automatically set upon first message.
    WindowHandle= msg.hwnd;
    on_attach(); 
    }
 // TODO: break out translate_message case.
 int result= handle_message (msg);
 if (msg.message == LastMessage) unhook();  // May have triggered deletion!
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::handle_message (ratwin::message::sMSG& msg)
// not inline because it's virtual.
 {
 return call_old_wndproc (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool message_tap::translate_message (const ratwin::message::sMSG&)
 {
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::call_old_wndproc (ratwin::message::sMSG& msg)
 {
 if (OldWndProc)
    return ratwin::window::CallWindowProc (OldWndProc, msg);
 else return ratwin::window::DefWindowProc (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}


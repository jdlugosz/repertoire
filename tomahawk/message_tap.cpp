// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_tap.h"
#include "ratwin\window.h"
#include "classics\exception.h"

STARTWRAP
namespace tomahawk {

const char FNAME[]= __FILE__;
using classics::exception;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_tap::message_tap()
 : WindowHandle(0), OldWndProc(0), EntryPoint (this, &message_tap::hook_handler)
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

void message_tap::hook (ratwin::types::HWND window)
 {
 if (WindowHandle) {
    exception X ("Tomahawk", "Duplicate hook", FNAME, __LINE__);
    throw X;
    }
 using namespace ratwin::window;
 WindowHandle= window;
 WindowOwnsMe= this;
 OldWndProc= static_cast<WNDPROC_2>( SetWindowLong (window, GWL_WNDPROC, EntryPoint.callptr()) );
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool message_tap::unhook()
 {
 // >> implement!!
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::hook_handler (ratwin::message::sMSG msg)
// This is where the message hits the class.
 {
 // >> do my own needs first.  WM_NCDESTROY unhooks.
 return handle_message (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_tap::handle_message (ratwin::message::sMSG& msg)
// not inline because it's virtual.
 {
 return call_old_wndproc (msg);
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


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap_UT.cxx
// Revision: public build 8, shipped on 11-July-2006

#include "tomahawk\message_tap.h"
#include "ratwin\message.h"
#include "ratwin\window.h"
#include "ratwin\autolink.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\MSG\WM_MOUSEMOVE.h"
#include "tomahawk\MSG\WM_SIZE.h"
#include "ratwin\utilities.h"
#include <stdio.h>
#include <string.h>

using ratwin::types::HINSTANCE;
using ratwin::types::HWND;
using namespace ratwin::message;
static char WinclassName[]= "WinClass";
using tomahawk::MSG::WM_MOUSEMOVE_msg;
using tomahawk::MSG::WM_SIZE_msg;
using ratwin::types::POINT;

// =====================================================================
// This is a demo to derive from message_tap.
// Basically, the WndProc becomes a virtual function call on an instance.

class testhook_1 : public tomahawk::message_tap {
   POINT position;
   WM_MOUSEMOVE_msg::KeyIndicators_t key_indicators;
   HWND child1;
   void process_MouseMove (const WM_MOUSEMOVE_msg&);
   void process_Size (const WM_SIZE_msg&);
   void on_attach();  // finish my setup here, now that I know what my window is.
   void update_stats();
public:
   testhook_1() : child1(0), key_indicators(WM_MOUSEMOVE_msg::KeyIndicators_t(0)) {}
   long handle_message (sMSG& msg);  // supply this function to start getting messages.
   };


void testhook_1::update_stats()
 {
 const int bufsize= 256;
 char buffer[bufsize];
 sprintf (buffer, "Mouse position: %d,%d\n", position.x, position.y);
 if (key_indicators & WM_MOUSEMOVE_msg::LButton)  strcat (buffer, "Left Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::RButton)  strcat (buffer, "Right Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::MButton)  strcat (buffer, "Middle Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Shift)  strcat (buffer, "Shift key\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Control)  strcat (buffer, "Control key");
 ratwin::window::SetWindowText (child1, buffer);
 }

void testhook_1::on_attach()
// This virtual function is called after the window and object are put together.
// It fills the role of WM_CREATE, which can't be used because the call to hook()
// is done after the window has been created.
 {
 using namespace ratwin::window;
 ratwin::types::RECT clientrect;
 GetClientRect (window_handle(), clientrect);
 child1= CreateWindow ("STATIC", "text goes here.", WS_CHILD|WS_VISIBLE, 0,0, clientrect.right, clientrect.bottom, window_handle(), (int)0, ratwin::util::get_Instance(), 0);
 int errorcode= ratwin::util::GetLastError();  // see it in the debugger.
 // >> create modeless dialog box here.
 }
 
void testhook_1::process_Size (const WM_SIZE_msg& msg)
 {
 // make my child match the new size
 // The typical use of this message is to manage the geometry of the child windows or other displayed elements.
 POINT newsize= msg.client_size();
 ratwin::window::MoveWindow (child1, 0,0, newsize.x, newsize.y);
 }

void testhook_1::process_MouseMove (const WM_MOUSEMOVE_msg& msg)
// This demo shows mouse coodinates.  They are not used for anything, just demo.
 {
 position= msg.mouse_position();
 key_indicators= msg.key_indicators();
 update_stats();
 }

long testhook_1::handle_message (sMSG& msg)
// This is the main entry point, called with window messages.
 {
 using namespace ratwin::WM_constants;
 switch (msg.message) {
    case WM_MOUSEMOVE:
       process_MouseMove (MSG_cast<WM_MOUSEMOVE_msg>(msg));
       break;
    case WM_SIZE:
       process_Size (MSG_cast<WM_SIZE_msg>(msg));
       break;
    }
 return message_tap::handle_message (msg);  // pass it on to my base class.
 }

// =====================================================================
// Illustrate/test a modeless dialog box.

// =====================================================================
// Illustrate/test a modal dialog box.

// =====================================================================
// Illustrate/test a property sheet.

// =====================================================================

bool InitApplication (HINSTANCE hInstance)
 {
 // Nothing much to the "Window Class" at all!
 ratwin::window::window_class<char> winclass (WinclassName);
 ratwin::types::ATOM classID= ratwin::window::RegisterClass (winclass);
 return classID != 0;
 }

bool InitInstance (HINSTANCE hInstance, ratwin::window::SW_window nCmdShow)
 {
 using namespace ratwin::window;
 ratwin::types::HWND hWnd= CreateWindow (WinclassName, "message_tap sample",  WS_OVERLAPPEDWINDOW|WS_VISIBLE);
 if (!hWnd) return false;
 testhook_1* p= new testhook_1;
 p->hook (hWnd);  // now Window has (owns) a smart-pointer to it.
 return true;
 }

int message_pump()
 {
 // Acquire and dispatch messages until a WM_QUIT message is received.
 using namespace ratwin::message;
 MSG msg;
 while ( GetMessage(msg) ) {
    // >> this doesn't translate key events to handle Accelerator Tables or modeless dialog boxes.
    TranslateMessage(msg);
    DispatchMessage(msg); 
    }
 return (msg.wParam);
 }


int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
 {
 if (!InitApplication(hInstance))  return (1);
 if (!InitInstance(hInstance, ratwin::window::SW_window(nCmdShow))) return (2);
 return message_pump();
 }



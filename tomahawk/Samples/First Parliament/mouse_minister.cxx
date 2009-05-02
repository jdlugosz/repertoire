// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#include "tomahawk\simple_message_pump.h"
#include "tomahawk\message_parliament.h"
#include "tomahawk\minister.h"
#include "tomahawk\commission.h"
#include "tomahawk\message_tap.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\MSG\WM_SIZE.h"
#include "ratwin\window.h"
#include "ratwin\utilities.h"
#include "tomahawk\mouse_minister.h"
#include <stdio.h>
#include <string.h>
using ratwin::types::HINSTANCE;
using tomahawk::MSG::WM_MOUSEMOVE_msg;
using tomahawk::MSG::WM_SIZE_msg;
using namespace ratwin::message;
static wchar_t WinclassName[]= L"WinClass";
using ratwin::message::sMSG;

// =====================================================================

class mainwin : public tomahawk::message_tap, public tomahawk::message_parliament, public tomahawk::minister {
   ratwin::types::HWND child1;
   int Count;
   void add_minister();
   void on_attach();  // finish my setup here, now that I know what my window is.
   void process_Size (const WM_SIZE_msg&);
   void process_MouseMove (const WM_MOUSEMOVE_msg&);
   administer_result_t administer_message (ratwin::message::sMSG& msg, int id, int status, message_parliament*);
   void add_external_minister();
public:
   mainwin()  : Count(0), child1(0) { add_minister(); }
   int count() const { return Count; }
   void count (int newval);
   };

// =====================================================================

class ExtMin : public tomahawk::minister {
   classics::baro<mainwin> parent;
public:
   ExtMin (mainwin* parent);
   administer_result_t administer_message (ratwin::message::sMSG& msg, int id, int status, tomahawk::message_parliament*);
   };

// =====================================================================

ExtMin::ExtMin (mainwin* parent)
 :parent(parent)
 {
 using namespace ratwin::WM_constants;
 tomahawk::message_range range;
 range << WM_LBUTTONDOWN;
 tomahawk::message_parliament::locked_commission commish (parent->message_parliament::add (this, range));
 commish->appointed_minister.own(true);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ExtMin::administer_result_t ExtMin::administer_message (ratwin::message::sMSG& msg, int id, int status, tomahawk::message_parliament*)
 {
 using namespace ratwin::WM_constants;
 switch (msg.message) {
    case WM_LBUTTONDOWN: {
       classics::handle<mainwin> p (parent);
       p->count ( 1+p->count() );
       } break;
    default:  return NeverHandles;
    }
 return Handled;
 }

// =====================================================================

void mainwin::count (int newval)
 {
 if (newval == Count)  return;  // no change
 Count= newval;
 if (child1) {
    const int bufsize= 256;
    char buffer[bufsize];
    sprintf (buffer, "Count is now set to %d.", Count);
    ratwin::window::SetWindowText (child1, buffer);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mainwin::add_minister()
 {
 using namespace ratwin::WM_constants;
 tomahawk::message_range range;
 range << WM_MOUSEMOVE << WM_SIZE;
 message_parliament::add (this, range);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mainwin::add_external_minister()
 {
 new ExtMin (this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mainwin::on_attach()
 {
 using namespace ratwin::window;
 ratwin::types::RECT clientrect;
 message_parliament::OldWndProc=get_old_wndproc();
 GetClientRect (window_handle(), clientrect);
 child1= CreateWindow ("STATIC", "text goes here.", WS_CHILD|WS_VISIBLE, 0,0, clientrect.right, clientrect.bottom, window_handle(), ratwin::ChildidOrHMENU(), ratwin::util::get_Instance(), 0);
 add_external_minister();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mainwin::process_Size (const WM_SIZE_msg& msg)
 {
 // make my child match the new size
 ratwin::types::POINT newsize= msg.client_size();
 ratwin::window::MoveWindow (child1, 0,0, newsize.x, newsize.y);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void mainwin::process_MouseMove (const WM_MOUSEMOVE_msg& msg)
// This demo shows mouse coodinates.  They are not used for anything, just demo.
 {
 ratwin::types::POINT position= msg.mouse_position();
 WM_MOUSEMOVE_msg::KeyIndicators_t key_indicators= msg.key_indicators();
 const int bufsize= 256;
 char buffer[bufsize];
 sprintf (buffer, "Mouse position: %d,%d\n", position.x, position.y);
 if (key_indicators & WM_MOUSEMOVE_msg::LButton)  strcat (buffer, "Left Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::RButton)  strcat (buffer, "Right Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::MButton)  strcat (buffer, "Middle Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Shift)  strcat (buffer, "Shift key\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Control)  strcat (buffer, "Control key\n");
 ratwin::window::SetWindowText (child1, buffer);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

mainwin::administer_result_t mainwin::administer_message (ratwin::message::sMSG& msg, int id, int status, message_parliament*)
 {
 using namespace ratwin::WM_constants;
 switch (msg.message) {
    case WM_MOUSEMOVE:
       process_MouseMove (MSG_cast<WM_MOUSEMOVE_msg>(msg));
       return Handled;
    case WM_SIZE:
       process_Size (MSG_cast<WM_SIZE_msg>(msg));
       return Handled;
    }
 return NeverHandles;
 }

// =====================================================================

bool InitApplication (HINSTANCE hInstance)
 {
 // Nothing much to the "Window Class" at all!
 ratwin::window::window_class<wchar_t> winclass (WinclassName);
 ratwin::types::ATOM classID= ratwin::window::RegisterClass (winclass);
 return classID != 0;
 }


bool InitInstance (HINSTANCE hInstance, ratwin::window::SW_window nCmdShow)
 {
 using namespace ratwin::window;
 ratwin::types::HWND hWnd= CreateWindow (WinclassName, L"First Parliament",  WS_OVERLAPPEDWINDOW|WS_VISIBLE);
 if (!hWnd) return false;
 mainwin* p= new mainwin;
 p->hook (hWnd);  // now Window has (owns) a smart-pointer to it.
 return true;
 }


int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
 {
 if (!InitApplication(hInstance))  return (1);
 if (!InitInstance(hInstance, ratwin::window::SW_window(nCmdShow))) return (2);
 tomahawk::simple_message_pump pump;
 int exitcode= pump.pumpit();
 return exitcode;
 }


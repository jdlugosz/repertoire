// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\Samples\Message Tap Demo\message_tap_demo.cxx
// Revision: post-public build 9

#define _CRT_SECURE_NO_DEPRECATE

#include "tomahawk\message_tap.h"
#include "tomahawk\Dialog_message_tap.h"
#include "ratwin\message.h"
#include "ratwin\window.h"
#include "ratwin\autolink.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\MSG\WM_MOUSEMOVE.h"
#include "tomahawk\MSG\WM_SIZE.h"
#include "tomahawk\MSG\WM_COMMAND.h"
#include "ratwin\utilities.h"
#include <stdio.h>
#include <string.h>
#include "ratwin\controls\basic.h"
#include "ratwin\dialog.h"
#include "ratwin\property_sheet.h"
#include "tomahawk\simple_message_pump.h"

using ratwin::types::HINSTANCE;
using ratwin::types::HWND;
using namespace ratwin::message;
static char WinclassName[]= "WinClass";
using tomahawk::MSG::WM_MOUSEMOVE_msg;
using tomahawk::MSG::WM_SIZE_msg;
using ratwin::types::POINT;
using ratwin::util::OutputDebugString;
using tomahawk::MSG::WM_COMMAND_msg;

// =====================================================================
// This is a demo to derive from message_tap.
// Basically, the WndProc becomes a virtual function call on an instance.

class testhook_2;

class testhook_1 : public tomahawk::message_tap {
   POINT position;
   WM_MOUSEMOVE_msg::KeyIndicators_t key_indicators;
   HWND child1;
   classics::handle<testhook_2> dialogbox;
   int foovalue;
   void process_MouseMove (const WM_MOUSEMOVE_msg&);
   void process_Size (const WM_SIZE_msg&);
   void on_attach();  // finish my setup here, now that I know what my window is.
   void update_stats();
public:
   testhook_1();
   ~testhook_1() { OutputDebugString ("destructing testhook_1 object\n"); }
   long handle_message (sMSG& msg);  // supply this function to start getting messages.
   // other stuff that is this class's business, not part of the framework.
   void set_foo (int);
   };


// =====================================================================
// Illustrate/test a modeless dialog box.

class testhook_2 : public tomahawk::Dialog_message_tap {
   classics::baro<testhook_1> parent;
   enum control_ID { OKButton= 1, TopText=101, EditBox, ComboBox, RadioGroupBox, Radio1, Radio2, Radio3, Radio4,
      UpDown, UpDownBuddy, CheckGroupBox, Check1, Check2, Check3, Check4, PushButton };
   bool process_COMMAND (const WM_COMMAND_msg&);
public:
   testhook_2 (classics::baro<testhook_1> parent) : parent(parent)
      {
      char buf[256];
      sprintf (buf, "constructing testhook_2 object at %08x\n", this);
      OutputDebugString (buf);
      }
   ~testhook_2() {
      char buf[256];
      sprintf (buf, "destructing testhook_2 object at %08x\n", this);
      OutputDebugString (buf);
      }
   long handle_message (sMSG& msg);  // supply this function to start getting messages.
   void on_attach();
   };


int demo_prop_page (classics::handle<testhook_2> object)
 {
 // first I need a page.
 ratwin::property_sheet::PROPSHEETPAGE<wchar_t> page;
 page.set_v58_size();
 page.dwFlags= 0;  // use defaults
 page.hInstance= ratwin::util::get_Instance();
 page.pszTemplate= L"SampleDialog";
 page.pfnDlgProc= 0;  // must use 0 here, real value is supplied by Dialog_message_tap.
 page.lParam= 0;  // ditto.
 // finally...
 ratwin::types::HPROPSHEETPAGE hPage= object->CreatePropertySheetPage (page);
 // Now that I have one page, describe a sheet containing it
 ratwin::property_sheet::PROPSHEETHEADER<wchar_t> sheet;
 sheet.dwSize= sizeof sheet;
 sheet.dwFlags= 0;
 sheet.hwndParent= 0;  // or could supply another window here.
 sheet.hInstance= ratwin::util::get_Instance();
 sheet.pszCaption= L"Property Sheet Demo";
 sheet.nPages= 1;  // important! size of array in next line.
 sheet.phpage= &hPage;
 sheet.nStartPage= 0;
 int result= ratwin::property_sheet::PropertySheet (sheet);  // run it.
 // note: PropertySheet automatically deletes hPage when done.
 return result;
 }

bool testhook_2::process_COMMAND (const WM_COMMAND_msg& msg)
 {
 // tell my main window about it.
 try {
    classics::handle<testhook_1> p (parent);
    p->set_foo (msg.command_ID());
    }
 catch (...) {}
 // now could do other things with it.
 // Illustrate interaction between controls
 switch (msg.command_ID()) {
    case Radio1:
    case Radio2:
    case Radio3:
    case Radio4: {
       char buffer[256];
       sprintf (buffer, "You selected radio button %d.", msg.command_ID()-Radio1+1);
       ratwin::dialog::SetDlgItemText (window_handle(), TopText, buffer);
       } return true;  // indicate that it was handled.
    case OKButton:
       if (is_modal()) {
          EndDialog (1);
          return true;
          }
       break;
    case PushButton: {
       classics::handle<testhook_2> popup (new testhook_2 (parent));
       int result;
       if (is_modal()) {
          // demonstrate property page
          result= demo_prop_page (popup);
          }
       else {  // demonstrate modal
          result= popup->ModalDialogBox (ratwin::util::get_Instance(), "SampleDialog", window_handle());
          }
       // >> can continue to inspect the popup object or use the result.
       return true;
       }
    }
 return false;
 }

void testhook_2::on_attach()
 {
 if (!is_modal()) {
    HWND child= ratwin::dialog::GetDlgItem (window_handle(), OKButton);
    ratwin::window::ShowWindow (child, ratwin::window::SW_HIDE);
    }
 }

long testhook_2::handle_message (sMSG& msg)
 {
 using namespace ratwin::WM_constants;

 switch (msg.message) {
    case WM_COMMAND:
       return process_COMMAND (MSG_cast<WM_COMMAND_msg>(msg));
       break;
    }
 return call_old_wndproc (msg);  // pass it on to my base class.
 }


//======================================================================
// Illustrate/test a basic window


testhook_1::testhook_1()
: child1(0), key_indicators(WM_MOUSEMOVE_msg::KeyIndicators_t(0)), foovalue(0)
{
OutputDebugString ("constructing testhook_1 object\n");
}

void testhook_1::update_stats()
 {
 const int bufsize= 256;
 char buffer[bufsize];
 sprintf (buffer, "Mouse position: %d,%d\n", position.x, position.y);
 if (key_indicators & WM_MOUSEMOVE_msg::LButton)  strcat (buffer, "Left Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::RButton)  strcat (buffer, "Right Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::MButton)  strcat (buffer, "Middle Button\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Shift)  strcat (buffer, "Shift key\n");
 if (key_indicators & WM_MOUSEMOVE_msg::Control)  strcat (buffer, "Control key\n");
 if (foovalue)  {
    sprintf (buffer+strlen(buffer), "Incoming Message from: %d\n", foovalue);
    }
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
 child1= CreateWindow ("STATIC", "text goes here.", WS_CHILD|WS_VISIBLE, 0,0, clientrect.right, clientrect.bottom, window_handle(), ratwin::ChildidOrHMENU(), ratwin::util::get_Instance(), 0);
 int errorcode= ratwin::util::GetLastError();  // see it in the debugger.
 // >> create modeless dialog box here.
 using namespace ratwin::controls;
 // need to do this for everything needed.  Yucky, 'cause I need to =know= what's needed, instead
 // of treating the dlg template as opaque.  Idea: make that part of the dlgproc?
 InitCommonControls (ICC_WIN95_CLASSES);
 dialogbox= new testhook_2 (classics::baro<testhook_1>(this));  // this is a smart pointer handle.
 dialogbox->ModelessDialogBox (ratwin::util::get_Instance(), "SampleDialog", window_handle());
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
    case WM_SIZE_msg::message_constant:
       process_Size (MSG_cast<WM_SIZE_msg>(msg));
       break;
    }
 return call_old_wndproc(msg);
 }


void testhook_1::set_foo (int newval)
 {
 foovalue= newval;
 update_stats();
 }

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


int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
 {
 if (!InitApplication(hInstance))  return (1);
 if (!InitInstance(hInstance, ratwin::window::SW_window(nCmdShow))) return (2);
 tomahawk::simple_message_pump pump;
 int exitcode= pump.pumpit();
// if (tomahawk::message_tap::get_object_count())  OutputDebugString ("*** Not all objects were destroyed!\n");
 return exitcode;
 }



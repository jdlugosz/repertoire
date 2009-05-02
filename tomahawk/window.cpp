// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\window.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\window.h"
#include "tomahawk\window_factory.h"
#include "ratwin\utilities.h"
#include "ratwin\message.h"
#include "ratwin\dialog.h"
#include "ratwin\WM_constants.h"
#include "classics\exception.h"
#include "tomahawk\event.h"
#include "tomahawk\gdi\dc.h"
#include "tomahawk\rect.h"
#include "classics\string_ios.h"  //for formatting error messages

STARTWRAP
namespace tomahawk {
using namespace ratwin::message;
using classics::exception;
using classics::win_exception;
using classics::wFmt;
using std::endl;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/*     window                                                   */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int window::window_instance_count= 0;

window::window()
 : hwnd(0), Parent(0), quit_on_destroy (classics::Automatic)
 {
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window::~window()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::scroll_contents (point delta)
 {
 ratwin::window::ScrollWindow (hwnd, delta.x, delta.y);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& window::get_default_factory()
 {
 // this should not be called.
 throw exception ("Tomahawk", "Don't call this", __FILE__, __LINE__);
 static window_factory_userdef wc ("Tomahawk::catchall");
 return wc;
 }

window_factory& created_window::get_default_factory()
 {
 static window_factory_userdef wc ("Tomahawk::MainWindow");
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::create (window_factory& factory, const char* title, window* parent, int ID)
 {
 using ratwin::window::CW_USEDEFAULT;
 static point usedefault (CW_USEDEFAULT, CW_USEDEFAULT);
 create (factory, title, parent, ID, usedefault, usedefault);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::create (const char* title, window* parent, int ID, const point& origin, const point& extent)
 {
 create (get_default_factory(), title, parent, ID, origin, extent);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::create (window_factory& factory, const char* title, window* parent, int ID, const point& origin, const point& extent)
 {
 if (hwnd)  throw exception ("Tomahawk", "Duplicate Create", __FILE__, __LINE__);
 Parent= parent;
 ratwin::types::HWND parent_handle= parent ? parent->get_handle() : 0;
 // prepare for tapping.
 factory.pre_create (this, reinterpret_cast<ratwin::window::WNDPROC>(::DefWindowProcA));
 // let'er rip.
 hwnd= ratwin::window::CreateWindowEx (factory.style2, factory.get_registration(), title, factory.style,
    origin.x, origin.y, extent.x, extent.y,
    parent_handle, ID, ratwin::util::get_Instance(), 0);
 if (!hwnd) {
    win_exception X ("Tomahawk", __FILE__, __LINE__);
    wFmt(X) << L"Error creating window of class \"" << string(factory.get_registration()) << L"\" with title \"" << string(title) << L"\"." << endl;
    throw X;
    }
 factory.post_create (hwnd);
 get_lifetime_object()->inc_owned_count();  // the system window points back to this object.
 on_initialize();
 ++ window_instance_count;    //count how many open windows
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool window::translate_key_event (MSG& e)
 {
 return Parent ? Parent->translate_key_event(e) : false;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::update()
 {
 if (! ratwin::window::UpdateWindow (hwnd)) {
    win_exception X ("Tomahawk", __FILE__, __LINE__);
    X += L"Error calling window::update [nee win32::UpdateWindow]\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool window::on_destroy()
 {
 -- window_instance_count;
 if (quit_on_destroy == classics::Yes || (quit_on_destroy == classics::Automatic && window_instance_count == 0)) {
    ratwin::window::PostQuitMessage(0);
    return true;
    }
 else return basic_router::on_destroy();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void created_window::router_disengage_cleanup()
 {
 get_lifetime_object()->dec_owned_count();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool created_window::on_paint (event& e)
 {
 paintstruct ps (e.wnd);
 return on_paint (ps);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void dispatch_recover (ratwin::types::HWND wnd)
 {
 const int WM_CANCELMODE= 0x001F;
 ratwin::window::SendMessage (wnd, WM_CANCELMODE);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int window::simple_message_loop()
 {
 using namespace ratwin::WM_constants;
 MSG msg;                       
 while (GetMessage (msg)) {
    try {
		if (msg.message >= WM_KEYFIRST && msg.message <= WM_KEYLAST && window_router::translate_key_event (msg.hwnd, msg))  continue;
       TranslateMessage (msg);
       DispatchMessage (msg); 
       }
    catch (classics::exception& err) {
       // >> will do something much fancier, later.
       err.show();
       dispatch_recover (msg.hwnd);
       }
    catch (...) {
	   ratwin::util::MessageBox ("Unknown Exception Caught\nin simple_message_loop()", "Problem!");
       dispatch_recover (msg.hwnd);
       }
    }   
 return msg.wParam;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool window::move (point pos, int nWidth, int nHeight, bool bRepaint)
 {
 return ratwin::window::MoveWindow (get_handle(), pos.x, pos.y, nWidth, nHeight, bRepaint);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool window::move (const rect& position, bool bRepaint)
 {
 return ratwin::window::MoveWindow (get_handle(), position.left, position.top, position.width(), position.height(), bRepaint);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool window::attach_to_child (int id, handle parent)
 {
 hwnd= ratwin::dialog::GetDlgItem (parent->get_handle(), id);
 if (!hwnd)  return false;   //child not found
 Parent= parent.operator->();
 message_tap_2::instance.link (hwnd, *this);  //assumes tap2.  could be more flexible?
 get_lifetime_object()->inc_owned_count();  // the system window points back to this object.
 on_initialize();
 ++ window_instance_count;    //count how many open windows
 return true;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::attach_to_hwnd (ratwin::types::HWND handle, message_tap& tap)
 {
 tap.link (handle, *this);
 hwnd= handle;
 get_lifetime_object()->inc_owned_count();
 on_initialize();
 ++ window_instance_count;    //count how many open windows
 using namespace ratwin::window;
 Parent= object (GetParent (handle));
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::attach_to_hwnd (ratwin::types::HWND handle)
 {
 attach_to_hwnd (handle, message_tap_2::instance);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long window::set_text (const string& s)
 {
 return set_text (s.c_str());
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

string window::get_text() const
 {
 const unsigned WM_GETTEXTLENGTH=  0x000E;
 const unsigned WM_GETTEXT=  0x000D;
 int len= send_message (WM_GETTEXTLENGTH, 0);
 string retval (len, 1+len);
 // It appears that the size parameter to WM_GETTEXT is the total buffer size, including
 // room for the trailing '\0'.  However, the return value does not include the '\0'.
 len= send_message (WM_GETTEXT, 1+len, retval.get_buffer());
 // the GETTEXTLENGTH message can sometimes return a value that is too large!
 // So I use that as a maximum and allocate that much space.  The GETTEXT message
 // will provide the actual length.
 retval.truncate (len);
 return retval;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long window::send_message (unsigned msg, unsigned p1, ulong p2) const
 {
 assert_created();
 return ratwin::window::SendMessage (hwnd, msg, p1, p2);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long window::send_message (unsigned msg, unsigned p1, const void* p2) const
 {
 assert_created();
 return ratwin::window::SendMessage (hwnd, msg, p1, p2);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::assert_created() const
 {
 if (!hwnd)  {
    exception X ("Tomahawk", "Assertion Failed", __FILE__, __LINE__);
    X += L"window handle is zero\n";
    throw X;
    }
 // this is a full member of window rather than just a utility function taking
 // any hwnd, so a future version can give more intimate information on
 // just which window is failing.
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window::get_location (ratwin::types::RECT& r, const window& w) const
 {
 ratwin::window::GetWindowRect (hwnd, r);
 ratwin::types::POINT* p= reinterpret_cast<ratwin::types::POINT*> (&r);
 p[0]= w.screen_to_client (p[0]);
 p[1]= w.screen_to_client (p[1]);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

rect window::client_to_screen (rect r) const
 {
 ratwin::types::POINT* pt= reinterpret_cast<ratwin::types::POINT*>(&r);
 ratwin::window::ClientToScreen (hwnd, pt[0]);
 ratwin::window::ClientToScreen (hwnd, pt[1]);
 return r;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP


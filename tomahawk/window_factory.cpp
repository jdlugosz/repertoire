// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\window_factory.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\window_factory.h"
#include "tomahawk\cursor.h"
#include "ratwin\atom.h"
#include "ratwin\resource.h"
#include "ratwin\utilities.h"
#include "tomahawk\global.h"
#include "classics\exception.h"
#include "classics\string_ios.h"

STARTWRAP
namespace tomahawk {
using classics::wFmt;
using std::endl;
using classics::exception;
using classics::win_exception;
using classics::string;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/*     window_factory                                           */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory::window_factory()
 : registered_name(0), style(ratwin::window::WS_OVERLAPPEDWINDOW), style2(0)
 {
 tapper= &message_tap_1::instance;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory_userdef::window_factory_userdef (const char* name)
 {
 wc.cbWndExtra= 4;    //for my object pointer.
 function (message_tap::install_hook);
 wc.className= name;
 wc.hIcon= ratwin::resource::LoadIcon (module_handle, "APPICON");
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const char* window_factory::get_registration()
 {
 return registered_name;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const char* window_factory_userdef::get_registration()
 {
 if (!registered_name) {
    if (!ratwin::window::RegisterClass (wc)) {
       win_exception X ("Tomahawk", __FILE__, __LINE__);
       wFmt(X) << L"can't register WindowClass " << string(wc.className) << endl;
       throw X;
       }
    registered_name= wc.className;
    }
 return registered_name;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window_factory::verify_unregistered() const
 {
 if (registered_name) {
    exception X ("Tomahawk", "WindowClass already registered", __FILE__, __LINE__);
    wFmt(X) << L"Can't modify " << string(registered_name) << L" which is already registered." << endl;
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory_userdef::~window_factory_userdef()
 {  //add unregister logic later.
 }


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void window_factory_userdef::cursor (const tomahawk::cursor& cur)
 {
 verify_unregistered();
 wc.hCursor= cur.h();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory_builtin::window_factory_builtin (const char* name)
 {
 tapper= &message_tap_2::instance;
 registered_name= name;
 }
 
}
ENDWRAP


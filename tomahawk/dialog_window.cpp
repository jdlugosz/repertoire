// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\dialog_window.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\dialog_window.h"
#include "tomahawk\controls\base.h"
#include "tomahawk\message_tap.h"
#include "ratwin\dialog.h"
#include "tomahawk\event.h"
#include "ratwin\message.h"

STARTWRAP
namespace tomahawk {

namespace {

int __stdcall dialog_proc (ratwin::types::HWND hDlg, unsigned uMsg, unsigned wParam, ulong lParam)
 {
 return false;
 }

}

void dialog_window::subclass_remaining_controls()
 {
 using namespace ratwin::window;
 for (ratwin::types::HWND wnd= GetWindow (get_handle(), GW_CHILD); wnd; wnd=GetWindow(wnd,GW_HWNDNEXT)) {
    // subclass everything that's not already mine
    if (-42 == ping (wnd, 42))  continue;  //I already have a command handler.
    controls::register_control::find_and_hook (wnd);
    }
 }

void dialog_window::field_to_control()
 {
 using namespace ratwin::window;
 for (ratwin::types::HWND wnd= GetWindow (get_handle(), GW_CHILD); wnd; wnd=GetWindow(wnd,GW_HWNDNEXT)) {
    controls::control_base* ctl= dynamic_cast<controls::control_base*>(object(wnd));
    /// around this is common code to get all controls
    if (ctl)  ctl->field_to_control();
    /// end of common loop
    }
 }

void dialog_window::control_to_field()
 {
 }

void dialog_window::run (int resource, ratwin::types::HWND parent)
 {
 if (hwnd)  throw "duplicate run!";
 hwnd= ratwin::dialog::CreateDialogParam (resource, dialog_proc, 0, parent);
 message_tap_2::instance.link (hwnd, *this);
 get_lifetime_object()->inc_owned_count();  // the system window points back to this object.
 on_initialize();
 ++ window_instance_count;    //count how many open windows
 }
 
void dialog_window::on_initialize()
 {
 subclass_remaining_controls();
 create_bindings();
 field_to_control();  //updates everything
 }
 
dialog_window::dialog_window()
{}

bool dialog_window::on_OK_button()
 {
 control_to_field();  //updates everything
 // ... give the derived class a crack at it HERE.
 destroy();
 return true;
 }
 
bool dialog_window::on_CANCEL_button()
 {
 destroy();
 return true;
 }

bool dialog_window::on_command (int id, unsigned notification_code, ratwin::types::HWND)
 {
 if (notification_code == ratwin::dialog::BN_CLICKED)  return on_button_clicked (id);
 else return false;  //not handled
 }
 
bool dialog_window::on_button_clicked (int id)
 {
 using namespace ratwin::dialog;
 switch (id) {
    case IDOK:  return on_OK_button();
    case IDCANCEL: return on_CANCEL_button();
    default:  return false;
    }
 }
 
extern ratwin::message::MSG msg;     //global kludge for debugging

bool dialog_window::translate_key_event (ratwin::message::MSG& msg)
 {
 return ratwin::message::IsDialogMessage (get_handle(), msg) || window::translate_key_event (msg);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

controls::control_base& dialog_window::get_control (int id)
 {
 ratwin::types::HWND child_handle= ratwin::dialog::GetDlgItem (hwnd, id);
 return dynamic_cast <controls::control_base&> (*object(child_handle));
 // I could make another scm command message to avoid the reinterpret_cast.
 // Or, I may end up doing this with its own local list of controls instead.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


}
ENDWRAP


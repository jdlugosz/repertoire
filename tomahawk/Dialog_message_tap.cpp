// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\Dialog_message_tap.h"
#include "ratwin\dialog.h"
#include "classics\exception.h"
#include "ratwin\property_sheet.h"

namespace tomahawk {
using ratwin::types::HWND;
using namespace ratwin::dialog;
using classics::exception;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

Dialog_message_tap::Dialog_message_tap()
: isModal(false)
 {
 LastMessage= 0;  // disable Unhook behavior
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

Dialog_message_tap::~Dialog_message_tap()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HWND Dialog_message_tap::ModelessDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, HWND parent)
 {
 HWND dialogbox= CreateDialogParam (module_for_resource, resource, parent, DLGPROC(get_WndProc()), 0);
 set_window_handle (dialogbox);
 return dialogbox;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int Dialog_message_tap::ModalDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, HWND parent)
 {
 isModal= true;
 int result= DialogBox (module_for_resource, resource, parent, DLGPROC(get_WndProc()));
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long Dialog_message_tap::handle_message (ratwin::message::sMSG& msg)
// Unlike a Window Proc which calls the base class or default, a Dialog Proc
// returns FALSE for "not processed".
 {
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void Dialog_message_tap::EndDialog (int result)
 {
 if (!is_modal()) {
    exception X ("Tomahawk", "Not a modal dialog box", __FILE__, __LINE__);
    throw X;
    }
 ratwin::dialog::EndDialog (window_handle(), result);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HPROPSHEETPAGE Dialog_message_tap::CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<char>& pagedef)
 {
 if (pagedef.pfnDlgProc) {
    exception X ("Tomahawk", "DialogProc is supplied; must be NULL initially", __FILE__, __LINE__);
    throw X;
    }
 pagedef.pfnDlgProc= DLGPROC(get_WndProc());
 return ratwin::property_sheet::CreatePropertySheetPage (pagedef);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HPROPSHEETPAGE Dialog_message_tap::CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<wchar_t>& pagedef)
 {
 if (pagedef.pfnDlgProc) {
    exception X ("Tomahawk", "DialogProc is supplied; must be NULL initially", __FILE__, __LINE__);
    throw X;
    }
 pagedef.pfnDlgProc= DLGPROC(get_WndProc());
 return ratwin::property_sheet::CreatePropertySheetPage (pagedef);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}


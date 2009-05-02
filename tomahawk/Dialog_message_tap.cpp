// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\Dialog_message_tap.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\Dialog_message_tap.h"
#include "ratwin\dialog.h"
#include "ratwin\message.h"
#include "classics\exception.h"
#include "ratwin\property_sheet.h"
#include "ratwin\window.h"
#include "ratwin\WM_constants.h"

namespace tomahawk {
using ratwin::types::HWND;
using namespace ratwin::dialog;
using classics::exception;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static int __stdcall dlg_stub (HWND w, unsigned message, unsigned p1, unsigned long p2)
 {
 if (message == ratwin::WM_constants::WM_INITDIALOG) {
    ratwin::window::SetWindowLong (w, DWL_DLGPROC, (void*)0);
    Dialog_message_tap* object= reinterpret_cast<Dialog_message_tap*>(p2);
    try { object->sane_check(); }
    catch (classics::exception& X) {  // add do that.
       X ("Tomahawk", "lParam does not appear to be my object", __FILE__, __LINE__);
       throw;
       }
    object->hook (w);
    }
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

Dialog_message_tap::Dialog_message_tap()
: isModal(false)
 {
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

Dialog_message_tap::~Dialog_message_tap()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

HWND Dialog_message_tap::ModelessDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, HWND parent)
 {
 HWND dialogbox= CreateDialogParam (module_for_resource, resource, parent, 0,0);
 hook (dialogbox);
 return dialogbox;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int Dialog_message_tap::ModalDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, HWND parent)
 {
 isModal= true;
 int result= DialogBoxParam (module_for_resource, resource, parent, dlg_stub, this);
 return result;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int Dialog_message_tap::pre_translate_message (const ratwin::message::MSG& msg)
 {
 return ratwin::message::IsDialogMessage (window_handle(), msg) ? 1 : 2;
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

static int __stdcall dlg_stub_prop (HWND w, unsigned message, unsigned p1, unsigned long p2)
 {
 if (message == ratwin::WM_constants::WM_INITDIALOG) {
    ratwin::window::SetWindowLong (w, DWL_DLGPROC, (void*)0);
    ratwin::property_sheet::PROPSHEETPAGE<char>* page= reinterpret_cast<ratwin::property_sheet::PROPSHEETPAGE<char>*>(p2);
    Dialog_message_tap* object= reinterpret_cast<Dialog_message_tap*>(page->lParam);
    try { object->sane_check(); }
    catch (classics::exception& X) {  // add to that.
       X ("Tomahawk", "lParam does not appear to be my object", __FILE__, __LINE__);
       throw;
       }
    object->hook (w);
    }
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HPROPSHEETPAGE Dialog_message_tap::CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<char>& pagedef)
 {
 if (pagedef.pfnDlgProc && pagedef.lParam) {
    exception X ("Tomahawk", "DialogProc and/or lParam is supplied; must be NULL initially", __FILE__, __LINE__);
    throw X;
    }
 pagedef.pfnDlgProc= dlg_stub_prop;
 pagedef.lParam= reinterpret_cast<long>(this);
 return ratwin::property_sheet::CreatePropertySheetPage (pagedef);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::HPROPSHEETPAGE Dialog_message_tap::CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<wchar_t>& pagedef)
 {
 if (pagedef.pfnDlgProc && pagedef.lParam) {
    exception X ("Tomahawk", "DialogProc and/or lParam is supplied; must be NULL initially", __FILE__, __LINE__);
    throw X;
    }
 pagedef.pfnDlgProc= dlg_stub_prop;
 pagedef.lParam= reinterpret_cast<long>(this);
 return ratwin::property_sheet::CreatePropertySheetPage (pagedef);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}


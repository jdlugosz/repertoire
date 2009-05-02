// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\Dialog_message_tap.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "tomahawk\message_tap.h"
#include "ratwin\NumOrName.h"
#include "ratwin\property_sheet=struct.h"

namespace tomahawk {

class Dialog_message_tap : public message_tap {
   bool isModal;
public:
   TOMAHAWK_EXPORT Dialog_message_tap();
   TOMAHAWK_EXPORT ~Dialog_message_tap();
   TOMAHAWK_EXPORT int pre_translate_message (const ratwin::message::MSG& msg);
   TOMAHAWK_EXPORT ratwin::types::HWND ModelessDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, ratwin::types::HWND parent=0);
   bool is_modal() const { return isModal; }
   TOMAHAWK_EXPORT int ModalDialogBox (ratwin::types::HINSTANCE module_for_resource, ratwin::NumOrName<char> resource, ratwin::types::HWND parent=0);
   TOMAHAWK_EXPORT void EndDialog (int result=0);
   TOMAHAWK_EXPORT ratwin::types::HPROPSHEETPAGE CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<char>&);
   TOMAHAWK_EXPORT ratwin::types::HPROPSHEETPAGE CreatePropertySheetPage (ratwin::property_sheet::PROPSHEETPAGE<wchar_t>&);
   };


}


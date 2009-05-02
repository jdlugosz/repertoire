// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\dialog.cpp
// Revision: public build 8, shipped on 11-July-2006

#define RATWIN_EXPORT __declspec(dllexport)

#include "ratwin\dialog.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace ratwin {
namespace dialog {

types::HWND CreateDialogParam (int resource, DLGPROC proc, void* param, types::HWND parent)
 {
 return CreateDialogParam (util::get_Instance(), reinterpret_cast<const char*>(resource), parent, proc, param);
 }

 
int DialogBox (int resource, DLGPROC proc, types::HWND parent)
 {
 return DialogBox (util::get_Instance(), reinterpret_cast<const char*>(resource), parent, proc);
 }


}}
ENDWRAP

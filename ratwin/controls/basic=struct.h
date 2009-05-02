// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\basic=struct.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {
namespace controls {

struct DRAWITEMSTRUCT {
    unsigned        CtlType;
    unsigned        CtlID;
    unsigned        itemID;
    unsigned        itemAction;
    unsigned        itemState;
    types::HWND        hwndItem;
    types::HDC         hDC;
    types::RECT        rcItem;
    ulong       itemData;
};

struct INITCOMMONCONTROLSEX {
   unsigned long struct_size;
   unsigned long bitflags;
   };

enum ICC_flags {
   ICC_LISTVIEW_CLASSES=     0x00000001, // listview, header
   ICC_TREEVIEW_CLASSES=     0x00000002, // treeview, tooltips
   ICC_BAR_CLASSES=          0x00000004, // toolbar, statusbar, trackbar, tooltips
   ICC_TAB_CLASSES=          0x00000008, // tab, tooltips
   ICC_UPDOWN_CLASS=         0x00000010, // updown
   ICC_PROGRESS_CLASS=       0x00000020, // progress
   ICC_HOTKEY_CLASS=         0x00000040, // hotkey
   ICC_ANIMATE_CLASS=        0x00000080, // animate
   ICC_WIN95_CLASSES=        0x000000FF, ///// everything above here.
   ICC_DATE_CLASSES=         0x00000100, // month picker, date picker, time picker, updown
   ICC_USEREX_CLASSES=       0x00000200, // comboex
   ICC_COOL_CLASSES=         0x00000400, // rebar (coolbar) control
   ICC_INTERNET_CLASSES=     0x00000800,
   ICC_PAGESCROLLER_CLASS=   0x00001000, // page scroller
   ICC_NATIVEFNTCTL_CLASS=   0x00002000, // native font control
   };


enum CCS_flags {  // common control window styles
   CCS_TOP=              0x00000001,
   CCS_NOMOVEY=          0x00000002,
   CCS_BOTTOM=           0x00000003,
   CCS_NORESIZE=         0x00000004,
   CCS_NOPARENTALIGN=    0x00000008,
   CCS_ADJUSTABLE=       0x00000020,
   CCS_NODIVIDER=        0x00000040,
   CCS_VERT=             0x00000080,
   CCS_LEFT=             (CCS_VERT | CCS_TOP),
   CCS_RIGHT=            (CCS_VERT | CCS_BOTTOM),
   CCS_NOMOVEX=          (CCS_VERT | CCS_NOMOVEY)
   };


} // end of controls

}
ENDWRAP



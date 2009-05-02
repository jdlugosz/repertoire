// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\controls\basic.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined RATWIN_Controls_BASIC_INCLUDED
#define RATWIN_Controls_BASIC_INCLUDED

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) void __stdcall InitCommonControls();
}

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

} // end of controls

}
ENDWRAP
#endif


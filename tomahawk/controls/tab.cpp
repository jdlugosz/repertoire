// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tab.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\tab.h"
#include "ratwin\utilities.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\rect.h"
#include "classics\exception.h"

STARTWRAP
namespace tomahawk {
namespace controls {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace {

class Error : public classics::win_exception {
public:
   Error (int line);
   };
   
//=============================================

Error::Error (int line)
 :classics::win_exception("Tomahawk", __FILE__, line)
 {}
}
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static void attach_new (ratwin::types::HWND wnd)
 {
 (new tab)->attach_to_hwnd (wnd);
 }

static register_control xx1 ("SysTabControl", attach_new);


struct TC_ITEM {
   unsigned mask;
   ulong state;
   ulong state_mask;
   const char* text;
   int textmax;
   int image;
   tab::info* extra_data;
   };

enum commands {
   TCM_FIRST= 0x1300,
   TCM_GETITEM= TCM_FIRST + 5,
   TCM_SETITEM= TCM_FIRST + 6,
   TCM_INSERTITEM= TCM_FIRST + 7,
   TCM_GETCURSEL= TCM_FIRST + 11,
   TCM_ADJUSTRECT= TCM_FIRST + 40,
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int tab::add (const char* name, info* data, int index)
 {
 TC_ITEM info= { 9, 0,0, name, 0, -1, data };
 index= send_message (TCM_INSERTITEM, index, &info);
 if (index == -1) {
    Error X (__LINE__);
    X += L"Error adding an item to a tab control.\n";
    throw X;
    }
 return index;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tab::set_data (int index, info* data)
 {
 TC_ITEM info= { 8, 0,0, 0,0, -1, data };
 if (!send_message (TCM_SETITEM, index, &info)) {
    Error X (__LINE__);
    X += L"Error setting data in a tab control.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tab::info* tab::get_data (int index)  const
 {
 TC_ITEM info= { 8 };
 if (index == -1)  index= current_selection();
 if (!send_message (TCM_GETITEM, index, &info)) {
    Error X (__LINE__);
    X += L"Error getting data from a tab control.\n";
    throw X;
    }
 return info.extra_data;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int tab::current_selection() const
 {
 return send_message (TCM_GETCURSEL);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

rect tab::interior (const window& parent) const
 {
 rect r;
 get_location (r, parent);
 send_message (TCM_ADJUSTRECT, false, &r);
 return r;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of controls
} // end of tomahawk
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\controls\tree.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\base.h"
#include "tomahawk\controls\tree.h"
#include "ratwin\utilities.h"
#include "tomahawk\window_factory.h"
#include "classics\exception.h"
#include "tomahawk\controls\tree=structs.h"
#include "tomahawk\rect.h"
#include "ratwin\mouse.h"  // context_menu() needs current mouse position.
#include "ratwin\menu.h"  // to support context_menu()

STARTWRAP
namespace tomahawk {
namespace controls {

using classics::string;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool tree::on_destroy()
 {
 remove_all();
 return window::on_destroy();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& tree::get_default_factory()
 {
 using namespace ratwin::window;  //easy access to style flag names
 static bool inited= init_common_controls();
 static window_factory_builtin treeclass ("SysTreeView32");
 const int HASBUTTONS= 0x0001;
 const int HASLINES= 0x0002;
 const int LINESATROOT= 0x0004;
 const int SHOWSELALWAYS= 0x0020;
 treeclass.style= WS_CHILD | WS_VISIBLE | HASBUTTONS|HASLINES|SHOWSELALWAYS|LINESATROOT;
 treeclass.style2= ratwin::window::WS_EX_CLIENTEDGE;
 return treeclass;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::create_control (window* parent, int childID, const rect& position)
 {
 create ("", parent, childID);
 move (position);
 install_reflector (parent);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::create_control (window* parent, int childID)
 {
 create ("", parent, childID);
 install_reflector (parent);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

const HTREEITEM TVI_LAST= ((HTREEITEM)0xFFFF0002);
const HTREEITEM TVI_ROOT= ((HTREEITEM)0xFFFF0000);
const int TVM_INSERTITEM= 0x1100;
const int TVM_DELETEITEM= 0x1101;
const int TVM_EXPAND= 0x1102;
const int TVM_GETITEMRECT= 0x1104;
const int TVM_GETCOUNT= 0x1105;
const int TVM_GETNEXTITEM= 0x110A;
const int TVM_GETITEM= 0x110C;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::insert (info* p)
 {
 char* TEXTCALLBACK= (char*)-1;
 TV_INSERTSTRUCT x= {
    0,  //no parent, so insert at top level
    TVI_LAST,
    { // item structure
       5 /*TVIF_PARAM|TVIF_TEXT*/,  //which members are valid
       0,  //item handle not used on input
       0,  //state
       0,  //stateMask
       TEXTCALLBACK,
       0,  //text size ignored on input
       0,  //image not being set
       0,  //selected image
       0,  //child count not used on input
       p  // Param points back to the object
       }
    };
 p->itemhandle= (HTREEITEM)send_message(TVM_INSERTITEM, 0, &x);
 if (!p->itemhandle) {
    classics::exception X ("Tomahawk", "Tree Control Error", __FILE__, __LINE__);
    // >> how do I get more error information from the control?
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::insert_child (const info* parent, info* p)
 {
 char* TEXTCALLBACK= (char*)-1;
 TV_INSERTSTRUCT x= {
    parent->itemhandle,
    TVI_LAST,
    { // item structure
       5 /*TVIF_PARAM|TVIF_TEXT*/,  //which members are valid
       0,  //item handle not used on input
       0,  //state
       0,  //stateMask
       TEXTCALLBACK,
       0,  //text size ignored on input
       0,  //image not being set
       0,  //selected image
       0,  //child count not used on input
       p  // Param points back to the object
       }
    };
 p->itemhandle= (HTREEITEM)send_message(TVM_INSERTITEM, 0, &x);
 if (!p->itemhandle) {
    classics::exception X ("Tomahawk", "Tree Control Error", __FILE__, __LINE__);
    // >> how do I get more error information from the control?
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::remove (info* node)
 {
 bool success= send_message (TVM_DELETEITEM, 0, node->itemhandle);
 if (!success) {
    classics::exception X ("Tomahawk", "Error Removing Node", __FILE__, __LINE__);
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::remove_all()
 {
 bool success= send_message (TVM_DELETEITEM, 0, TVI_ROOT);
 if (!success) {
    classics::exception X ("Tomahawk", "Error Removing Node", __FILE__, __LINE__);
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int tree::elcount() const
 {
 return send_message (TVM_GETCOUNT);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tree::info* tree::get_selection() const
 {
 HTREEITEM handle= reinterpret_cast<HTREEITEM*>( send_message (TVM_GETNEXTITEM, 9) );
 return info_from_handle (handle);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tree::info* tree::get_highlighted() const
 {
 HTREEITEM handle= reinterpret_cast<HTREEITEM*>( send_message (TVM_GETNEXTITEM, 8) );
 return info_from_handle (handle);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tree::info* tree::info_from_handle (void* htreeitem) const
 {
 TV_ITEM x= {
    4, // TVIF_PARAM
    htreeitem
    };
 bool success= send_message (TVM_GETITEM, 0, &x);
 if (!success)  return 0;
 return x.lParam;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

rect tree::bounding_rect (const info* item, bool labelonly)
 {
 union {
    ratwin::types::RECT retval;   //for output
    HTREEITEM hi;  //for input
    };
 hi= item->itemhandle;
 bool success= send_message (TVM_GETITEMRECT, labelonly, &retval);
 if (!success) {
    classics::exception X ("Tomahawk", "No Bounding Rect", __FILE__, __LINE__);
    throw X;
    }
 return static_cast<rect&>(retval);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::expand (const info* item, bool open)
 {
 int TVE_EXPAND= 2;
 int TVE_COLLAPSE= 1;
 bool result= send_message (TVM_EXPAND, open?TVE_EXPAND:TVE_COLLAPSE, item->itemhandle);
 if (!result) {
    classics::exception X ("Tomahawk", "Error Expanding/Contracting Tree", __FILE__, __LINE__);
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// tree::info members
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree::info::context_menu (tree* sender, ratwin::types::HMENU m, ratwin::types::HWND handler)
 {
 tomahawk::controls::tree::info* other= sender->get_highlighted();
 if (!other)  other= this;
 tomahawk::rect r= sender->client_to_screen (sender->bounding_rect (other, true));
 tomahawk::point p;
 if (!ratwin::GetCursorPos(p)) {
    // error getting mouse cursor position.  Improvise.
    p= r.ul_corner();
    }
 using namespace ratwin::menu;
 unsigned flags= TPM_RIGHTBUTTON|TPM_VERTICAL;
 if (!TrackPopupMenu (m, flags, p, handler, r)) {
    classics::win_exception X ("Tomahawk", __FILE__, __LINE__);
    X += L"Failed call to Win32's TrackPopupMenu function\n";
    throw X;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}}
ENDWRAP



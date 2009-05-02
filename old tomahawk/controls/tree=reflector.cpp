// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tree=reflector.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\tree.h"
#include "tomahawk\event_router\contributer.h"
#include "ratwin\WM_constants.h"
#include "tomahawk\event.h"
#include "tomahawk\controls\tree=structs.h"
#include <cstring>  //need memcpy()

STARTWRAP
namespace tomahawk {

using event_router_n::contributer;
using event_router_n::message_range;
using event_router_n::delegator;

enum codes {
   TVN_FIRST= 0U-400U,  // tree control
   TVN_GETDISPINFO= TVN_FIRST-3,
   TVN_KEYDOWN= TVN_FIRST-12,
   TVN_DELETEITEM= TVN_FIRST-9,
   TVN_SELCHANGED= TVN_FIRST-2,
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

struct TV_DISPINFO : public ratwin::WM_constants::NMHDR {
   controls::TV_ITEM item;
   };

struct TV_KEYDOWN : public ratwin::WM_constants::NMHDR {
   ushort wVKey;
   unsigned flags;
   };
    
struct NM_TREEVIEW  : public ratwin::WM_constants::NMHDR {
   unsigned action;
   tomahawk::controls::TV_ITEM itemOld;
   tomahawk::controls::TV_ITEM itemNew;
   ratwin::types::POINT ptDrag;
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class tree_reflector : public contributer {
   static message_range& make_range();
   bool get_disp_info (TV_DISPINFO*);
   bool key_down (TV_KEYDOWN*);
   controls::tree* const mytree;
public:
   tree_reflector (controls::tree* p) : mytree(p) {}
   void add (delegator* master);
   // virtual overrides
   bool delegated_event (event&, int id);
   bool process_event (event& x)  { return delegated_event(x,0); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool tree_reflector::delegated_event (event& e, int id)
 {
 using namespace ratwin::WM_constants;
 if (e.message != WM_NOTIFY)  return false;
 NMHDR* p= static_cast<NMHDR*> (e.plp);
 // make sure this message is for me.
 if (p->sender != mytree->get_handle())  return false;
 // OK, now deal with it.
 // first handle things that don't need a current selection
 switch (p->code) {
    case TVN_GETDISPINFO:
       return get_disp_info (static_cast<TV_DISPINFO*>(p));
    case TVN_DELETEITEM: {
       NM_TREEVIEW* pp= static_cast<NM_TREEVIEW*>(p);
       controls::tree::info* info= pp->itemOld.lParam;
       delete info;
       return true;
       }
    case TVN_SELCHANGED: {
       NM_TREEVIEW* pp= static_cast<NM_TREEVIEW*>(p);
       controls::tree::info* oldinfo= pp->itemOld.lParam;
       controls::tree::info* newinfo= pp->itemNew.lParam;
       newinfo->on_select (mytree, oldinfo);
       return true;
       }
    }
 // the rest use the selection, so get that once.
 controls::tree::info* info= mytree->get_selection();
 if (!info)  return false;
 // common control messages
 if (info->handle_common_message (mytree, p->code))  return true;
 // the rest of the tree-specific messages
 switch (p->code) {
    case TVN_KEYDOWN: {
       TV_KEYDOWN* pp= static_cast<TV_KEYDOWN*>(p);
       info->on_key_down (mytree, pp->wVKey);
       return true;
       }
    default:
       return false;  //I did not handle this message.
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool tree_reflector::get_disp_info (TV_DISPINFO* p)
 {
 const string& s= p->item.lParam->label();
 int len= s.elcount();
 const int maxlen= p->item.cchTextMax - 1;  //leave room for '\0'
 if (len > maxlen)  len= maxlen;
 memcpy (p->item.pszText, s.get_buffer(), len);
 p->item.pszText[len]= '\0';
 return true;  // handled this message.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range& tree_reflector::make_range()
 {
 static message_range range;
 range << ratwin::WM_constants::WM_NOTIFY;
 return range;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void tree_reflector::add (delegator* master)
 {
 classics::baro<contributer> xh (this);
 xh.own(true);
 delegator::delegate data (make_range(), xh, classics::Normal);
 master->add (data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

namespace controls {

void tree::install_reflector (delegator* parent)
 {
 tree_reflector* x= new tree_reflector(this);
 x->add (parent);
 }

}}
ENDWRAP




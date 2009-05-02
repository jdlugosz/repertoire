// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tree.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#include "tomahawk\window.h"
#include "tomahawk\controls\common_control_info.h"

STARTWRAP
namespace tomahawk {
class window_factory;
namespace controls {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class tree : public window {
   void install_reflector (event_router_n::delegator*);
public:
   class info;
   TOMAHAWK_EXPORT window_factory& get_default_factory();
   TOMAHAWK_EXPORT void create_control (window* parent, int childID, const rect& position);
   TOMAHAWK_EXPORT void create_control (window* parent, int childID);
   TOMAHAWK_EXPORT void insert (info*);  //tree takes ownership
   TOMAHAWK_EXPORT void insert_child (const info* parent, info*);  //tree takes ownership
   TOMAHAWK_EXPORT void remove (info* node);
   TOMAHAWK_EXPORT void remove_all();
   TOMAHAWK_EXPORT info* get_selection() const;
   TOMAHAWK_EXPORT info* get_highlighted() const;
   TOMAHAWK_EXPORT rect bounding_rect (const info*, bool labelonly);
   TOMAHAWK_EXPORT void expand (const info* item, bool open= true);
   TOMAHAWK_EXPORT int elcount() const;  //how many items are in the tree
   void contract (const info* item)  { expand(item,false); }
   TOMAHAWK_EXPORT bool on_destroy();
protected:
   TOMAHAWK_EXPORT info* info_from_handle (void* htreeitem) const;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class tree::info : public common_control_info<tree> {
public:
   void* itemhandle;
   virtual string label() const =0;
   info() : itemhandle(0) {}
   virtual ~info() {}
   virtual void on_key_down (tree* sender, ushort vkey) {}
   TOMAHAWK_EXPORT void context_menu (tree* sender, ratwin::types::HMENU m, ratwin::types::HWND handler);
   virtual void on_select (tree* sender, info* old) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of controls
} // end of tomahawk
ENDWRAP


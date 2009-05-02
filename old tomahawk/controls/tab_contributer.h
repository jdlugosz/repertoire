// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\controls\tab_contributer.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_TAB_CONTROL_CONTRIBUTER_INCLUDED
#define TOMAHAWK_TAB_CONTROL_CONTRIBUTER_INCLUDED

#include "tomahawk\controls\tab.h"

STARTWRAP
namespace tomahawk {

// The compiler hangs if I put tab_contributer inside the controls namespace too.
class tab_contributer : public event_router_n::contributer {
public:
   TOMAHAWK_EXPORT tab_contributer (event_router_n::delegator* master);
   TOMAHAWK_EXPORT bool delegated_event (event&, int id);
   TOMAHAWK_EXPORT virtual bool selection_changing (controls::tab::handle control);
      // return true to prevent selection from changing.
   TOMAHAWK_EXPORT virtual void selection_changed (controls::tab::handle control);
   };

} // end of tomahawk
ENDWRAP

#endif





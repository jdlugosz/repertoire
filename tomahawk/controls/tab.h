// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\tab.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_Controls_TAB_INCLUDED
#define TOMAHAWK_Controls_TAB_INCLUDED

#include "tomahawk\controls\base.h"
#include "tomahawk\event_router\delegator.h"

STARTWRAP
namespace tomahawk {
class window_factory;
namespace controls {

class tab : public control_base {
public:
   typedef derived_handle <tab, window> handle;
   class info {
   public:
      virtual void activate() {}
      virtual void deactivate() {}
      virtual void change_from (handle control);
      };
   TOMAHAWK_EXPORT int add (const char* name, info* data= 0, int index= 0x7fffffff);
   TOMAHAWK_EXPORT rect interior (const window& parent) const;
   TOMAHAWK_EXPORT void set_data (int index, info* data);
   TOMAHAWK_EXPORT info* get_data (int index=-1)  const;
   TOMAHAWK_EXPORT int current_selection() const;
      // returns -1 if none is selected.
   };


} // end of controls
} // end of tomahawk
ENDWRAP

#endif


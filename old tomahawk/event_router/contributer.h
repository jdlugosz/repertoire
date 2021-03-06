// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\event_router\contributer.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EventRouter_CONTRIBUTER_INCLUDED
#define TOMAHAWK_EventRouter_CONTRIBUTER_INCLUDED

#include "classics\schedule_t.h"
#include "tomahawk\event_router\base.h"

STARTWRAP
namespace tomahawk {
namespace event_router_n {

class delegator;
class message_range;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class message_range {
public:
   unsigned low;
   unsigned high;
   message_range() : low(~0), high(0) {}
   TOMAHAWK_EXPORT message_range& operator<< (unsigned item);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class contributer : virtual public base {
public:
   enum traversal { Cancel, Restart };
   typedef classics::schedule_t schedule_t;
   TOMAHAWK_EXPORT contributer (delegator*, const message_range& range, schedule_t schedule= /*classics::Normal*/ schedule_t (32*1024));
      // !! VC5.0 compiler bug: Normal replaced with magic number as work-around
   contributer() {}
   virtual ~contributer() {}
   virtual bool delegated_event (event&, int id) =0;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of event_router_n
} // end of tomahawk
ENDWRAP

#endif



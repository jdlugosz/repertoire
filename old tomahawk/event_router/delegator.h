// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\event_router\delegator.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EventRouter_DELEGATOR_INCLUDED
#define TOMAHAWK_EventRouter_DELEGATOR_INCLUDED

#include "classics\vararray.h"
#include "tomahawk\event_router\contributer.h"

STARTWRAP
namespace tomahawk {

namespace event_router_n {
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class contributer;

class delegator : public virtual base {
public:
   class delegate {
   public:
      typedef classics::baro<contributer> baro;
   private:
      typedef contributer::schedule_t schedule_t;
      message_range range;
      int id;
      baro contribution;
      schedule_t schedule;
   public:
      TOMAHAWK_EXPORT delegate (const message_range& range, const baro& contributer, schedule_t schedule, int id=0);
      delegate() : schedule(classics::Never) {}
      TOMAHAWK_EXPORT bool process_all_event (event&, bool handled) const;
      TOMAHAWK_EXPORT static int compare (const delegate&, const delegate&);
      const baro& get_contribution() const  { return contribution; }
      int get_id() const  { return id; }
      };
   classics::vararray_g<delegate> contributer_list;
   TOMAHAWK_EXPORT bool process_event (event&);
   TOMAHAWK_EXPORT void add (const delegate&);  //input object is copied.
   TOMAHAWK_EXPORT int remove (const contributer*, int id= -1);
   };



}
} // end of tomahawk
ENDWRAP

#endif



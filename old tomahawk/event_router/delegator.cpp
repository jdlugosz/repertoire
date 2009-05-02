// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\event_router\delegator.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "classics\exception.h"
#include "tomahawk\event_router\delegator.h"
#include "tomahawk\event.h"

STARTWRAP

namespace tomahawk {
namespace event_router_n {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

delegator::delegate::delegate (const message_range& range, const baro& x, schedule_t schedule, int id)
 : range(range), contribution(x), schedule(schedule), id(id)
 {}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int delegator::delegate::compare (const delegate& left, const delegate& right)
 {
 return (left.schedule&0xffff) - (right.schedule&0xffff);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void delegator::add (const delegate& value)
 {
 contributer_list.sorted_insert (value, delegate::compare);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int delegator::remove (const contributer* p, int id)
 {
 int count= 0;
 int index= 0;
 while (index < contributer_list.elcount()) {
    const delegate& x= contributer_list.get_at(index);
    if (x.get_contribution().points_to (p) && (id==-1 || id==x.get_id())) {
       contributer_list.remove (index);
       ++count;
       }
    else ++index;
    }
 return count;  //how many were removed.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool delegator::process_event (event& e)
 {
 restart:
 bool handled= false;
 try {  //callbacks can interact with this loop via exceptions
    const classics::vararray_g<delegate> list (contributer_list);
    // make a COW copy, so any changes made by the contributers
    // won't mess up my traversal.
    const int max= list.elcount();
    for (int loop= 0;  loop < max;  ++loop) {
       handled= list.get_at(loop).process_all_event (e, handled);
       }
    }
 catch (contributer::traversal command) {
    if (command == contributer::Restart)  goto restart;
    // command==Cancel drops out.
    }
 return handled;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool delegator::delegate::process_all_event (event& e, bool handled) const
 {
 // skip if not part of my schedule
 if ((handled && !(schedule & 0x00010000)) || schedule == 0)  return handled;
 // skip if message number is out of range
 if (e.message < range.low || e.message > range.high)  return handled;
 // OK, have this contributer do his stuff.
 try {
    classics::handle<contributer> h (contribution);
    handled= (h->delegated_event (e, id)  || handled);
       //turn on handled, but never turn off.
    }
 catch (classics::exception& err) {
    err.show();
    }
 return handled;
 }

}}


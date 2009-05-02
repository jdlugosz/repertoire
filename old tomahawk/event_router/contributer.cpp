// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event_router\contributer.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)

#include "tomahawk\event_router\contributer.h"
#include "tomahawk\event_router\delegator.h"

STARTWRAP
namespace tomahawk {
namespace event_router_n {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_range& message_range::operator<< (unsigned item)
 {
 if (item < low)  low= item;
 if (item > high)  high= item;
 return *this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

contributer::contributer (delegator* master, const message_range& range, schedule_t schedule)
 {
 delegator::delegate data (range, delegator::delegate::baro(this), schedule);
 master->add (data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of event_router_n
} // end of tomahawk
ENDWRAP


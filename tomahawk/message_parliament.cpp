// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\message_tap.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\message_parliament.h"
#include "tomahawk\commission.h"
#include "ratwin\window.h"
#include "tomahawk\minister.h"

namespace tomahawk {

using classics::schedule_t;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::message_parliament()
 : OldWndProc (ratwin::window::WNDPROC(0))
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::~message_parliament()
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

long message_parliament::handle_message (ratwin::message::sMSG& msg)
 {
 restart:
 int status;
 handle_message_return_code= 0;
 status= 0;  // nothing happened yet.
      // bit 1 means 'handled'.
 // iterate over all commissions
 for (classics::iterator<commission> it (commission_list); it;  ++it) {
    int step= 0;  // for use in error reporting.
    try {
       commission& commish= *it;
       if ((status&1) && !(commish.schedule&0x00010000))  continue;  // don't call this one if message already handled.
       if (commish.rangefunc && !commish.rangefunc(msg.message))  continue;  // not meant for me.
       if (!commish.range.contains (msg.message))  continue;  // not meant for me.
       ++step;
       classics::handle<minister> M (commish.appointed_minister);
       ++step;
       minister::administer_result_t result= M->administer_message (msg, commish.id, status, this);
       // >> act on result
       status |= result;
       }
    catch (minister::traversal command) {
       if (command == minister::Restart)  goto restart;
       // command == minister::Cancel drops out
       }
    // >> will log/alert but continue with next minister.
    // >> but handle my baro resolution separately.
    catch (...) { /* ... */ }
    }
 if (status & 1)  return handle_message_return_code;
 // Last Ditch handling.  This mechanism (parliament) did not handle it.
 if (OldWndProc)
    return ratwin::window::CallWindowProc<wchar_t> (OldWndProc, msg);
 else return ratwin::window::DefWindowProc<wchar_t> (msg);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int commission::compare (const commission& left, const commission& right)
 {
 return (right.schedule & 0xffff) - (left.schedule & 0xffff);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int commission::comparekey (const commission& left, const schedule_t& right)
 {
 return (right & 0xffff) -  (left.schedule & 0xffff);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void message_parliament::add (const commission& x)
 {
 listlocker_t lock (*this);
 commission_list.sorted_insert (x, &commission::compare);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::locked_commission message_parliament::add (minister* m, message_range range, schedule_t schedule, int id)
 {
 listlock.enter();
 int index= ~ classics::binary_search (commission_list, schedule, &commission::comparekey);
 // >> Well?  Need a special kind of insert on vararray in order to get the special savings.
 // That is, "move" rather than "copy" the new elements.
 commission temp;
 temp.appointed_minister= m;
 temp.range= range;
 temp.schedule= schedule;
 temp.id= id;
 commission_list.replace (index, 0, &temp, 1);
 locked_commission retval (&listlock, &commission_list[index]);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::locked_commission message_parliament::add (minister* m, message_range range)
 {
 listlock.enter();
 commission temp;
 temp.appointed_minister= m;
 temp.range= range;
 int index= classics::binary_search (commission_list, temp.schedule, &commission::comparekey);
 if (index < 0)  index= ~index;
 // >> Well?  Need a special kind of insert on vararray in order to get the special savings.
 // That is, "move" rather than "copy" the new elements.
 commission_list.replace (index, 0, &temp, 1);
 locked_commission retval (&listlock, &commission_list[index]);
 return retval;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int message_parliament:: remove (const minister*, int id)
 {
 return 0;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

message_parliament::locked_commission message_parliament::find (const minister*, int id)
 {
 commission* result= 0;
 locked_commission retval (&listlock, result);
 listlock.enter();
 // >>> do the search
 return retval;
 }

}


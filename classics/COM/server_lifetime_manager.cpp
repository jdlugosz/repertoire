// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\server_lifetime_manager.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include "classics\COM\server_lifetime_manager.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {
namespace COM {

server_lifetime_manager_t server_lifetime_manager;
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

server_lifetime_manager_t::server_lifetime_manager_t()
 : server_lock_count(0), object_count(0), unloadable(0)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

event_flag& server_lifetime_manager_t::unload_flag() const
 {
 // Note: create-on-first-use logic is not thread safe.
 if (!unloadable)  unloadable= new event_flag (event_flag::manual_reset, false);
 return *unloadable;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void server_lifetime_manager_t::idlewait (int time)
 {
 // Not very good because it puts a minimum time down.  Needs to interact with the "inc" functions.
 inc_server_lock();
 ratwin::util::Sleep(time);
 dec_server_lock();  //triggers unload if no connections/locks made yet.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void server_lifetime_manager_t::dec_server_lock()
 {
 if (--server_lock_count==0 && object_count==0 && unloadable)
    unloadable->set();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void server_lifetime_manager_t::dec_objects()
 {
 if (--object_count==0 && server_lock_count==0 && unloadable)
    unloadable->set();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end COM namespace

// This function is defined out here because VC5 crashes if it's in its normal place.
COM::server_lifetime_manager_t::~server_lifetime_manager_t()
 {
 delete unloadable;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end namespace
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\server_lifetime_manager.cpp
// Revision: public build 9, shipped on 18-Oct-2006

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
 if (unload_flag().wait (time) != 0) {
    inc_server_lock();
    dec_server_lock();  //triggers unload if no connections/locks made yet.
    }
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


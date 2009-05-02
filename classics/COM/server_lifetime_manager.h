// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\server_lifetime_manager.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#include "classics\atomic_counter.h"
#include "classics\event_flag.h"

STARTWRAP
namespace classics {
namespace COM {

class server_lifetime_manager_t {
   atomic_counter<long> server_lock_count;
   atomic_counter<long> object_count;
   mutable event_flag* unloadable;  //created on first use
public:
   server_lifetime_manager_t();
   ~server_lifetime_manager_t();
   void inc_server_lock() { ++server_lock_count; }
   CLASSICS_EXPORT void dec_server_lock();
   void inc_objects() { ++object_count; }
   CLASSICS_EXPORT void dec_objects();
   bool can_unload_now() const
      { return server_lock_count==0 && object_count==0; }
   CLASSICS_EXPORT event_flag& unload_flag() const;
   CLASSICS_EXPORT void idlewait (int time);
   };

extern server_lifetime_manager_t CLASSICS_EXPORT server_lifetime_manager;

}}  //end of classics namespace
ENDWRAP


// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\server_lifetime_manager.h
// Revision: post-public build 6

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
   class obj_reference {
   // use this as a class member to give destructor semantics
   public:
      inline obj_reference();
      inline ~obj_reference();
      };
   };

extern server_lifetime_manager_t CLASSICS_EXPORT server_lifetime_manager;

server_lifetime_manager_t::obj_reference::obj_reference() { server_lifetime_manager.inc_objects(); }
server_lifetime_manager_t::obj_reference::~obj_reference() { server_lifetime_manager.dec_objects(); }

}}  //end of classics namespace
ENDWRAP


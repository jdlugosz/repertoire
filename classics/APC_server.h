// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\APC_server.h
// Revision: updated

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\command_object.h"
#include "ratwin\base.h"

STARTWRAP
namespace classics {

class APC_server {
   ratwin::types::Thread_HANDLE thread_handle;
   volatile bool done;
   static void __stdcall handler (void*);
   class commander;
   friend class commander;
public:
   enum control { Quit };
   void start();  //used internally only.
   CLASSICS_EXPORT APC_server();
   CLASSICS_EXPORT ~APC_server();
   CLASSICS_EXPORT void send (abstract_command_object*);
   CLASSICS_EXPORT void quit();
   CLASSICS_EXPORT void wait_till_done();
   };

} // end of classics
ENDWRAP



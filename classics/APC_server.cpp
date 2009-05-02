// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\APC_server.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\APC_server.h"
#include "classics\thread.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class APC_server::commander : public abstract_command_object {
   APC_server* object;
   control command;
public:
   commander (APC_server* object, control command) : object(object), command(command) {}
   void operator() ();
   };
   
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::commander::operator() ()
 {
 switch (command) {
    case Quit:
       object->done= true;
       break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

APC_server::APC_server()
 : done (false)
 {
 thread_handle= launch_thread (*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

APC_server::~APC_server()
 {
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::send (abstract_command_object* p)
 {
 ratwin::tasking::QueueUserAPC (handler, thread_handle, p);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::start()
 {
 while (!done)
    ratwin::util::Sleep (0xffffffff, true);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::handler (void* raw)
 {
 abstract_command_object* p= static_cast<abstract_command_object*>(raw);
 try {
    (*p)();  //perform the command
    }
 catch (...) {/*eat it*/}
 delete p;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::quit()
 {
 send (new commander(this,Quit));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void APC_server::wait_till_done()
 {
 ratwin::tasking::WaitForSingleObject (thread_handle);
 }

} // end of classics
ENDWRAP


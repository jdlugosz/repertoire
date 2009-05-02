// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: 
// Revision: fresh

#pragma once

namespace tomahawk {
namespace MSG {

class simple_message_pump {
protected:
   // override these functions to supply the corresponding functionality in the standard loop.
   virtual void thread_message (ratwin::message::sMSG);
   virtual bool translate_key_event (ratwin::message::sMSG);
   // override the mainloop to change the logic.
   virtual int mainloop();
public:
   int pumpit();  // calls mainloop, surrounds with EH handlers.
   };

}}


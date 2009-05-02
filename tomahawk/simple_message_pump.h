// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\simple_message_pump.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\message=struct.h"
#include "classics\exception.h"

namespace tomahawk {

class simple_message_pump {
protected:
   // override these functions to supply the corresponding functionality in the standard loop.
   virtual void thread_message (ratwin::message::MSG&)  {}
   TOMAHAWK_EXPORT virtual bool pre_translate (ratwin::message::MSG&);  // call TranslateAccelerator, IsDialog
   TOMAHAWK_EXPORT virtual bool translate_key_event (ratwin::message::MSG&);  // call TranslateMessage
   // override the mainloop to change the logic.
   TOMAHAWK_EXPORT virtual int mainloop();
public:
   TOMAHAWK_EXPORT simple_message_pump();
   TOMAHAWK_EXPORT int pumpit()  throw();  // calls mainloop, surrounds with EH handlers.
   TOMAHAWK_EXPORT virtual bool report_error (const classics::exception&);
   };

}


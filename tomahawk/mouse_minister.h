// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "tomahawk\minister.h"
#include "classics\schedule_t.h"
#include "tomahawk\MSG\WM_MOUSEMOVE.h"

namespace tomahawk {

class mouse_minister : public tomahawk::minister {
   administer_result_t administer_message (ratwin::message::sMSG& msg, int id, int status, tomahawk::message_parliament*);
protected:
   TOMAHAWK_EXPORT mouse_minister ();
   classics::schedule_t schedule_base, schedule_active;
   unsigned trigger_button;
   unsigned trigger_modifiers;
   // callbacks for notifications
   virtual void button_down (unsigned button, unsigned modifiers) {}
   virtual void button_up (bool accept) {}  //false for cancel
   virtual void moved_statusquo (const MSG::WM_MOUSEMOVE_msg&) {}
   virtual void moved_out_of_range (const MSG::WM_MOUSEMOVE_msg&) {}
   virtual void moved_back_in_range (const MSG::WM_MOUSEMOVE_msg&) {}
   virtual void changed_modifiers (unsigned modifiers) {}
   virtual void changed_buttons (unsigned buttons) {}
public:
   void add (tomahawk::message_parliament*, bool own);
   };

}


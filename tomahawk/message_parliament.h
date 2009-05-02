// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "classics\vararray.h"
#include "tomahawk\HWND_vpapa.h"
#include "ratwin\message=struct.h"
#include "classics\schedule_t.h"
#include "tomahawk\message_range.h"
#include "classics\critical_section.h"

namespace tomahawk {

class commission;
class minister;

class message_parliament : public virtual HWND_vpapa {
   classics::vararray_g<commission> commission_list;
   classics::critical_section listlock;
protected:
   TOMAHAWK_EXPORT void add (const commission&);
   TOMAHAWK_EXPORT commission& add (minister*, message_range);
   TOMAHAWK_EXPORT commission& add (minister*, message_range, classics::schedule_t, int id= 0);
   TOMAHAWK_EXPORT int remove (const minister*, int id=-1);
   class listlocker_t : public classics::critical_section::locker {
   public:
      listlocker_t (message_parliament& x) : locker(x.listlock) {}
      };

public:
   TOMAHAWK_EXPORT virtual long handle_message (ratwin::message::sMSG& msg);
   long handle_message_return_code;
   TOMAHAWK_EXPORT message_parliament();
   TOMAHAWK_EXPORT ~message_parliament();
   };

}


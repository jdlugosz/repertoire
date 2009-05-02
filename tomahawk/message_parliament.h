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
#include "ratwin\window=struct.h"

namespace tomahawk {

class commission;
class minister;

class message_parliament : public virtual HWND_vpapa {
   classics::vararray_g<commission> commission_list;
   classics::critical_section listlock;
protected:
   ratwin::window::WNDPROC_sig OldWndProc;
   class listlocker_t : public classics::critical_section::locker {
   public:
      listlocker_t (message_parliament& x) : locker(x.listlock) {}
      };
   class locked_commission {
      classics::critical_section* lock;
      commission* record;
      void operator= (const locked_commission*);  // never defined
   public:
      locked_commission (classics::critical_section* lock, commission* record)
         : lock(lock), record(record) {}
      locked_commission (locked_commission& old)  // transfer ownership out of returning function
         : lock(old.lock), record(old.record) { old.lock= 0; }
      ~locked_commission() { if (lock) lock->leave(); }
      commission* operator->() const { return record; }
      operator bool() const { return record; }
      bool operator! () const { return ! operator bool(); }
      };
public:
   TOMAHAWK_EXPORT void add (const commission&);
   TOMAHAWK_EXPORT locked_commission add (minister*, message_range);
   TOMAHAWK_EXPORT locked_commission add (minister*, message_range, classics::schedule_t, int id= 0);
   TOMAHAWK_EXPORT int remove (const minister*, int id=-1);
   TOMAHAWK_EXPORT locked_commission find (const minister*, int id=-1);
   TOMAHAWK_EXPORT virtual long handle_message (ratwin::message::sMSG& msg);
   long handle_message_return_code;
   TOMAHAWK_EXPORT message_parliament();
   TOMAHAWK_EXPORT ~message_parliament();
   };

}


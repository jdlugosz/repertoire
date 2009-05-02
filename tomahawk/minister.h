// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "classics\pointers.h"
#include "ratwin\message=struct.h"
#include "tomahawk\commission.h"

namespace tomahawk {

class message_parliament;
class __declspec(novtable) minister: public virtual classics::can_handle {
public:
   virtual ~minister() {}
   enum administer_result_t {
      NotHandled= 0,
      Handled= 1,
      NeverHandles= 2,
      PostProcessed= 5,
      PreProcessed= 8
      };
   struct traversal_state {
      int status;
      message_parliament* parliament;
      commission* current;
      int id() const { return current->id; }
      classics::schedule_t schedule() const { return current->schedule; }
      };
   virtual administer_result_t administer_message (ratwin::message::sMSG& msg, const traversal_state&) =0;
   enum traversal { Cancel, Restart };
   };

}


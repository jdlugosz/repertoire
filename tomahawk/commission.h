// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "classics\vararray.h"
#include "classics\schedule_t.h"
#include "tomahawk\message_range.h"

namespace tomahawk {

class minister;

namespace internal {
struct commission_data {
   typedef classics::baro<minister> baro;
   baro appointed_minister;
   message_range range;
   bool (*rangefunc)(unsigned);
   classics::schedule_t schedule;
   int id;
   commission_data() : rangefunc(0), schedule(classics::Normal), id(0) {}
   };
}

class commission : public internal::commission_data {
public:
   TOMAHAWK_EXPORT commission();
   TOMAHAWK_EXPORT ~commission();
   TOMAHAWK_EXPORT commission (const commission&);
   TOMAHAWK_EXPORT commission& operator= (const commission&);
   TOMAHAWK_EXPORT static int compare (const commission&, const commission&);
   TOMAHAWK_EXPORT static int comparekey (const commission&, const classics::schedule_t&);
   };

}


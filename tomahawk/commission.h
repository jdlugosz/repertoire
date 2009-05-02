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

class commission {
public:
   typedef classics::baro<minister> baro;
   baro appointed_minister;
   message_range range;
   classics::schedule_t schedule;
   int id;
   };

}


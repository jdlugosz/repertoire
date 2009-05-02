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

namespace tomahawk {

class commission;
class minister;

class message_parliament : public virtual HWND_vpapa {
   classics::vararray_g<commission> commission_list;
protected:
   TOMAHAWK_EXPORT void add (const commission&);
   TOMAHAWK_EXPORT int remove (const minister*, int id=-1);
public:
   TOMAHAWK_EXPORT virtual long handle_message (ratwin::message::sMSG& msg);
   TOMAHAWK_EXPORT message_parliament();
   TOMAHAWK_EXPORT ~message_parliament();
   };

}


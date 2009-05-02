// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\embellishment.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_EMBELLISHMENT_INCLUDED
#define TOMAHAWK_EMBELLISHMENT_INCLUDED

#include "classics\pointers.h"
#include "tomahawk\base.h"

STARTWRAP
namespace tomahawk {

class embellishment : virtual public classics::can_handle {
public:
   virtual void scrollpos_changed (point newpos) {}
   virtual void pagesize_changed (point newsize) {}
   virtual void viewsize_changed (point newsize) {}
   virtual void pagenumber_changed (int newpage) {}
   };


} // end of tomahawk
ENDWRAP

#endif



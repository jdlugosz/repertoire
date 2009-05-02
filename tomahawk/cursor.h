// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\cursor.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_CURSOR_INCLUDED
#define TOMAHAWK_CURSOR_INCLUDED

#include "classics\pointers.h"
#include "ratwin\base.h"
#include "tomahawk\base.h"

STARTWRAP
namespace tomahawk {

class cursor {
public:
   enum stock {
      arrow=32512, I_beam, wait, cross, uparrow,
      sizeNWSE=32642, sizeNESW, sizeWE, sizeNS, sizeall,
      no=32648, appstarting= 32650, help };
   class internal : public classics::can_handle {
      ratwin::types::HCURSOR H;
   public:
      TOMAHAWK_EXPORT ~internal();
      internal (ratwin::types::HCURSOR H) : H(H) {}
      internal (ratwin::types::HINSTANCE inst, const char* name);
      ratwin::types::HCURSOR h() const  { return H; }
      TOMAHAWK_EXPORT internal (stock);
      };
   cursor (ratwin::types::HCURSOR H) : impl (new internal(H)) {}
   cursor (stock x) : impl (new internal(x)) {}
   cursor (ratwin::types::HINSTANCE inst, const char* name)  : impl (new internal (inst, name)) {}
   ratwin::types::HCURSOR h() const  { return impl->h(); }
   TOMAHAWK_EXPORT void make_active() const;
private:
   classics::const_handle<internal> impl;
   };
   


} // end of tomahawk
ENDWRAP

#endif



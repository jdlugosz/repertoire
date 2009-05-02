// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\event.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_EVENT_DEFINED
#define TOMAHAWK_EVENT_DEFINED

#include "tomahawk\base.h"
#include "ratwin\base.h"
//#include "tomahawk\point.h"

STARTWRAP
namespace tomahawk {

class event {
public:
   ratwin::types::HWND wnd;
   unsigned message;
   union {
      unsigned wp;
      struct {
         ushort lo;
         ushort hi;
         } xwp;
      };   
   union {
      ulong lp;  //second parameter as number
      void* plp; //or as pointer
      struct {
         ushort lo;
         ushort hi;
         } xlp;
      };
   union {   
      long ret;   //return value as number
      void* pret; //or as pointer
      };
// these are not used.
//   ulong time;
//   point pt;
   event (ratwin::types::HWND wnd, unsigned message, unsigned wp, ulong lp)
     : wnd(wnd), message(message), wp(wp), lp(lp), ret(0) {}
//   event (ratwin::types::HWND wnd, unsigned message, unsigned wp, ulong lp, ulong time, ratwin::types::POINT pt)
//     : wnd(wnd), message(message), wp(wp), lp(lp), ret(0), time(time), pt(pt) {}
   };

}
ENDWRAP
#endif


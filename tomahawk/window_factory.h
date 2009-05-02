// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\window_factory.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once
#if !defined TOMAHAWK_WINDOW_FACTORY_INCLUDED
#define TOMAHAWK_WINDOW_FACTORY_INCLUDED

#include "tomahawk\base.h"
#include "tomahawk\message_tap.h"

STARTWRAP
namespace tomahawk {

class cursor;

class window_factory {
protected:
   const char* registered_name;
   TOMAHAWK_EXPORT void verify_unregistered() const;
   message_tap* tapper;
public:
   ulong style, style2;            //style bits used when creating window
   TOMAHAWK_EXPORT window_factory();
   TOMAHAWK_EXPORT virtual const char* get_registration();
   void pre_create (event_router_n::window_router* r, ratwin::window::WNDPROC p)
      { tapper->pre_create (r,p); }
   void post_create (ratwin::types::HWND wnd) { tapper->post_create (wnd); }
   };


class window_factory_userdef : public window_factory {
protected:
   ratwin::window::window_class wc;
public:
   TOMAHAWK_EXPORT window_factory_userdef (const char* name);
   TOMAHAWK_EXPORT ~window_factory_userdef();  //unregisters the window class
   TOMAHAWK_EXPORT const char* get_registration();    //registers the window class on first use
   ratwin::window::WNDPROC function() const  { return wc.lpfnWndProc; }
   void function (ratwin::window::WNDPROC x)  { verify_unregistered(); wc.lpfnWndProc= x; }
   void extra_bytes (int x)  { verify_unregistered(); wc.cbWndExtra=x; }
   void style (unsigned x)  { verify_unregistered(); wc.style= x; }
   void background (ratwin::types::HBRUSH x)  { verify_unregistered(); wc.hbrBackground= x; }
   TOMAHAWK_EXPORT void cursor (const cursor&);
       // TODO:  replace HCURSOR with class.
   bool registered() const  { return registered_name; }
   };
   
class window_factory_builtin : public window_factory {
public:
   TOMAHAWK_EXPORT window_factory_builtin (const char* name);   
   };
   
}
ENDWRAP
#endif



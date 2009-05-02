// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\window.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_WINDOW_INCLUDED
#define TOMAHAWK_WINDOW_INCLUDED

#include "tomahawk\event_router\basic_router.h"
#include "classics\pointers.h"
#include "classics\misc_types.h"
#include "classics\string.h"

STARTWRAP
namespace tomahawk {

using classics::string;
class window_factory;
class message_tap;
class event;     //in tomahawk\event.h
class paintstruct; //in tomahawk\gdi\dc.h
class rect;

class window : public event_router_n::basic_router {
protected:   
   ratwin::types::HWND hwnd;
   static int window_instance_count;
   event_router_n::window_router* Parent;  //***
public:
   TOMAHAWK_EXPORT virtual ~window();
   TOMAHAWK_EXPORT void assert_created() const;
   typedef classics::handle<window> handle;
   // >> the term "handle" used for two purposes.  Review this.
   handle get_smartptr();
   event_router_n::window_router* parent() const  { return Parent; }  //***
   // >> need separate const and non-const forms.
   TOMAHAWK_EXPORT window();
   virtual void on_initialize() {}
   classics::tristate quit_on_destroy;
   TOMAHAWK_EXPORT bool on_destroy();
   bool show (int showflags=5)
      { return ratwin::window::ShowWindow (hwnd, showflags); }
   bool hide()  { return show(0); }
   TOMAHAWK_EXPORT void update();
   ratwin::types::HWND get_handle()  { return hwnd; }
   TOMAHAWK_EXPORT virtual bool attach_to_child (int id, handle parent);
   TOMAHAWK_EXPORT virtual void attach_to_hwnd (ratwin::types::HWND, message_tap& );
   TOMAHAWK_EXPORT void attach_to_hwnd (ratwin::types::HWND);  //uses tap 2.
   TOMAHAWK_EXPORT static int simple_message_loop();
  // operations on windows
   TOMAHAWK_EXPORT bool move (point, int nWidth, int nHeight, bool bRepaint= true);
   TOMAHAWK_EXPORT bool move (const rect& position, bool bRepaint= true);
   TOMAHAWK_EXPORT long send_message (unsigned msg, unsigned p1=0, ulong p2=0) const;  //sometimes const, anyway.
   TOMAHAWK_EXPORT long send_message (unsigned msg, unsigned p1, const void* p2) const;
   long set_text (const char* s)
    { return send_message (0xc, 0, s); }
   TOMAHAWK_EXPORT long set_text (const string&);
   TOMAHAWK_EXPORT string get_text() const; 
   long set_extended_style (long style)  { return (long)ratwin::window::SetWindowLong (get_handle(), ratwin::window::GWL_EXSTYLE, style); }
   string get_WC_name() const  { return ratwin::window::GetClassName (hwnd); }
   void destroy() { ratwin::window::DestroyWindow (hwnd); }
   void get_client (ratwin::types::RECT& r) const { ratwin::window::GetClientRect (hwnd, r); }
   void get_location (ratwin::types::RECT& r, const window&) const;
   TOMAHAWK_EXPORT bool translate_key_event (ratwin::message::MSG&);
   TOMAHAWK_EXPORT void scroll_contents (point delta);
   point client_to_screen (point p) const
      { ratwin::window::ClientToScreen (hwnd, p);  return p; }
   TOMAHAWK_EXPORT rect client_to_screen (rect p) const;
   point screen_to_client (point p) const
      { ratwin::window::ScreenToClient (hwnd, p);  return p; }
   TOMAHAWK_EXPORT virtual void create (window_factory&, const char* title, window* parent=0, int ID= 0);
   void create (const char* title, window* parent=0, int ID=0)   { create (get_default_factory(), title, parent, ID); }
   TOMAHAWK_EXPORT void create (window_factory&, const char* title, window* parent, int ID, const point& origin, const point& extent);
   TOMAHAWK_EXPORT void create (const char* title, window* parent, int ID, const point& origin, const point& extent);
   TOMAHAWK_EXPORT virtual window_factory& get_default_factory();
   void execute (event_router_n::command& cmd)  {  window_router::execute (hwnd, cmd); }
   };

inline
window::handle window::get_smartptr()
 {
 return handle(this);
 // this will be different after switching to "non-intrusive" smart pointers.
 // so make sure I keep this abstracted.
 }

template <class T, class B>
class derived_handle : public classics::handle<T> {
	typedef classics::handle<T> Base;
public:
   explicit derived_handle (T* p) : Base(p) {}
   derived_handle() {}
   derived_handle& operator= (T* other) { Base::operator=(other);  return *this; }
   operator B::handle () const { return B::handle (data()); }
   };

class created_window : public virtual window {
protected:
   TOMAHAWK_EXPORT void link_window_proc();     //install my virtual window function
public:
   typedef derived_handle <created_window, window> handle;
   TOMAHAWK_EXPORT virtual window_factory& get_default_factory();
   TOMAHAWK_EXPORT void router_disengage_cleanup();
   virtual bool on_paint (paintstruct&) { return false; }
   TOMAHAWK_EXPORT bool on_paint (event&);
   };


}
ENDWRAP
#endif


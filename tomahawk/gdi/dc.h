// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\gdi\dc.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once
#if !defined TOMAHAWK_GDI_DC_INCLUDED
#define TOMAHAWK_GDI_DC_INCLUDED

#include "ratwin\GDI.h"
#include "ratwin\text.h"
#include "tomahawk\window.h"

#include "tomahawk\color_t.h"
  // only needed for work-around at point (1).

STARTWRAP
namespace tomahawk {

class color_t;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class dc {
protected:
   ratwin::types::HDC Handle;
public:
   TOMAHAWK_EXPORT point text_extent (const char* buf, int len);
   TOMAHAWK_EXPORT color_t text_color() const;
   ratwin::types::HDC get_handle() { return Handle; }
   void get_metrics (ratwin::text::TEXTMETRIC& tm) const  { ratwin::text::GetTextMetrics (Handle, tm); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// rendering_dc is anything that's not an "information only" DC.
class rendering_dc : public dc {
public:
   virtual ~rendering_dc() {}  //dtor varies by concrete class
   TOMAHAWK_EXPORT color_t bk_color (color_t newcolor);
   TOMAHAWK_EXPORT color_t bk_color_window();
   TOMAHAWK_EXPORT void TextOut (point, const char* s, int len);
//1:   using dc::text_color;
   /* MSVC compiler bug */   color_t text_color() const  { return dc::text_color(); }
   TOMAHAWK_EXPORT color_t text_color (color_t newcolor);
   };

class window_dc_A : public rendering_dc {
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// window_dc is not a printer or memory.
class window_dc : public window_dc_A {
   window::handle Wnd;
   // >> could get rid of Wnd.  Worth it?
public:
   enum create_flags {
      NonClient= 1,
      FromCache= 2,
      ClipChildren= 8,
      ClipSiblings= 0x10,
      UseParent= 0x20,
      LockedWindowUpdate= 0x400,
      //VALIDATE         0x00200000L
      //NORESETATTRS     0x00000004L
      // I don't understand what it does, so don't use it!
      //EXCLUDERGN       0x00000040L
      //NTERSECTRGN     0x00000080L
      // These will be another param, used with a different constructor.
      //EXCLUDEUPDATE    0x00000100L
      //NTERSECTUPDATE  0x00000200L
      // I don't find documentation on these.
      };
   window_dc (const window::handle& wnd) : Wnd(wnd) { Handle= ratwin::gdi::GetDC (wnd->get_handle()); }
   ~window_dc() { ratwin::gdi::ReleaseDC (Wnd->get_handle(), Handle); }
   };

inline window_dc::create_flags operator| (window_dc::create_flags x, window_dc::create_flags y) { return window_dc::create_flags(int(x)|int(y)); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class paintstruct : public window_dc_A, public ratwin::gdi::PAINTSTRUCT {
   const ratwin::types::HWND Wnd;
public:
   paintstruct (ratwin::types::HWND wnd) : Wnd(wnd) {  Handle= ratwin::gdi::BeginPaint (Wnd, this); }
   ~paintstruct() {  ratwin::gdi::EndPaint (Wnd, this); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// move this to another file?
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class textmetric : public ratwin::text::TEXTMETRIC {
public:
   textmetric (dc& context)  { context.get_metrics (*this); }
   int nominal_lineheight() const  { return Height + ExternalLeading; }
   };
   

} // end namespaces
ENDWRAP
#endif


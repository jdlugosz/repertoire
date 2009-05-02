// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\edit.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_Controls_EDIT_INCLUDED
#define RATWIN_Controls_EDIT_INCLUDED
#pragma warning (disable:4250)

#include "tomahawk\controls\base.h"

STARTWRAP

// forward declarations
namespace ratwin {
namespace controls {
   class char_format;
}}

namespace tomahawk {

class window_factory;

namespace controls {

///////////////////////////

enum edit_control_style {
   ES_LEFT=              0x0000L,
   ES_CENTER=            0x0001L,
   ES_RIGHT=             0x0002L,
   ES_MULTILINE=         0x0004L,
   ES_UPPERCASE=         0x0008L,
   ES_LOWERCASE=         0x0010L,
   ES_PASSWORD=          0x0020L,
   ES_AUTOVSCROLL=       0x0040L,
   ES_AUTOHSCROLL=       0x0080L,
   ES_NOHIDESEL=         0x0100L,
   ES_OEMCONVERT=        0x0400L,
   ES_READONLY=          0x0800L,
   ES_WANTRETURN=        0x1000L,
   ES_NUMBER=            0x2000L,
   // for rich edit
   ES_SAVESEL=           0x00008000,
   ES_SUNKEN=            0x00004000,
   ES_DISABLENOSCROLL=   0x00002000,
   ES_SELECTIONBAR=      0x01000000,
   ES_EX_NOCALLOLEINIT=  0x01000000,
   ES_VERTICAL=          0x00400000,
   ES_NOIME=             0x00080000,
   ES_SELFIME=           0x00040000
   };

class edit_base : public control_base {
public:
   typedef derived_handle <edit_base, window> handle;
   TOMAHAWK_EXPORT void get_value (classics::string&) const;
   TOMAHAWK_EXPORT void set_value (const classics::string&);
   TOMAHAWK_EXPORT void replace_sel (const char* s, bool canundo=false);
   static void attach_new_text (ratwin::types::HWND);
   };

class text : virtual public edit_base {
public:
   TOMAHAWK_EXPORT window_factory& get_default_factory();
   };

class rtf : virtual public edit_base {
public:
   TOMAHAWK_EXPORT window_factory& get_default_factory();
   TOMAHAWK_EXPORT bool set_char_format (unsigned flags, const ratwin::controls::char_format&);
  // high-level format controls
   TOMAHAWK_EXPORT void format_bold (bool enable=true);
   TOMAHAWK_EXPORT void format_italic (bool enable=true);
   TOMAHAWK_EXPORT void format_underscore (bool enable=true);
   };

class multi_edit_base : virtual public edit_base {
   };

class text_multiline : public text, public multi_edit_base {
public:
   TOMAHAWK_EXPORT window_factory& get_default_factory();
   };

class rtf_multiline : public rtf, public multi_edit_base {
public:
   TOMAHAWK_EXPORT window_factory& get_default_factory();
   };


}}
ENDWRAP
#endif


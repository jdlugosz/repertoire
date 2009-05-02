// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\edit.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\controls\edit.h"
#include "ratwin\controls\text.h"
#include "ratwin\utilities.h"
#include "tomahawk\window_factory.h"


STARTWRAP
namespace tomahawk {
namespace controls {

static register_control xx1 ("edit", edit_base::attach_new_text);
 
void edit_base::attach_new_text (ratwin::types::HWND wnd)
 {
 ( (reinterpret_cast<unsigned long>(ratwin::window::GetWindowLong (wnd, ratwin::window::GWL_STYLE)) & ES_MULTILINE) ?
   (new text_multiline) : (new text) ) ->attach_to_hwnd (wnd);
 // Yucky cast: GetWindowLong can't be overloaded based on return type.  I'll fix this later.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void edit_base::replace_sel (const char* s, bool canundo)
 {
 send_message (ratwin::controls::EM_REPLACESEL, canundo, s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void edit_base::get_value (classics::string& s) const
 {
 s= get_text();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void edit_base::set_value (const classics::string& s)
 {
 set_text (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& text::get_default_factory()
 {
 using namespace ratwin::window;  //easy access to style flag names
 static bool inited= init_common_controls();
 static window_factory_builtin editclass ("EDIT");
 editclass.style= WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
       // check the options and decide what is most suitable.
 return editclass;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& rtf::get_default_factory()
 {
 using namespace ratwin::window;  //easy access to style flag names

 static bool inited= init_common_controls();
 static ratwin::types::HINSTANCE hRTFLib = ratwin::util::LoadLibrary ("RICHED32.DLL");
 static window_factory_builtin editclass ("RICHEDIT");
 editclass.style= WS_CHILD | WS_VISIBLE | ES_SAVESEL | WS_HSCROLL;
       // check the options and decide what is most suitable.
 return editclass;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool rtf::set_char_format (unsigned flags, const ratwin::controls::char_format& format)
 {
 return send_message (ratwin::controls::EM_SETCHARFORMAT, flags, &format);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void rtf::format_bold (bool enable)
 {
 using namespace ratwin::controls;
 char_format fmt;
 fmt.effects= CFE_BOLD;
 fmt.mask= CFM_BOLD;
 bool xx= set_char_format (SCF_SELECTION, fmt);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void rtf::format_italic (bool enable)
 {
 using namespace ratwin::controls;
 char_format fmt;
 fmt.effects= CFE_ITALIC;
 fmt.mask= CFM_ITALIC;
 bool xx= set_char_format (SCF_SELECTION, fmt);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void rtf::format_underscore (bool enable)
 {
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& text_multiline::get_default_factory()
 {
 window_factory& wc= text::get_default_factory();
 using namespace ratwin::window;  //easy access to style flag names
 wc.style |= ES_MULTILINE | WS_VSCROLL | ES_WANTRETURN;
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& rtf_multiline::get_default_factory()
 {
 window_factory& wc= rtf::get_default_factory();
 using namespace ratwin::window;  //easy access to style flag names
 wc.style |= ES_MULTILINE | WS_VSCROLL;
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


}}
ENDWRAP


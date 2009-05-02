// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\controls\common_control_info.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

STARTWRAP
namespace tomahawk {
namespace controls {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class common_control_info {
public:
   bool handle_common_message (T* sender, unsigned code);
   virtual void on_click (T* sender) {}
   virtual void on_double_click (T* sender) {}
   virtual void on_right_click (T* sender) {}
   virtual void on_right_double_click (T* sender) {}
   virtual void on_set_focus (T* sender) {}
   virtual void on_kill_focus (T* sender) {}
   virtual void on_enterkey (T* sender) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
bool common_control_info<T>::handle_common_message (T* sender, unsigned code)
 {
 const unsigned NM_FIRST= 0;
 const unsigned NM_CLICK= (NM_FIRST-2);
 const unsigned NM_DBLCLK= (NM_FIRST-3);
 const unsigned NM_RETURN= (NM_FIRST-4);
 const unsigned NM_RCLICK= (NM_FIRST-5);
 const unsigned NM_RDBLCLK= (NM_FIRST-6);
 const unsigned NM_SETFOCUS= (NM_FIRST-7);
 const unsigned NM_KILLFOCUS= (NM_FIRST-8);
// const unsigned NM_CUSTOMDRAW= (NM_FIRST-12);
// const unsigned NM_HOVER= (NM_FIRST-13);
 switch (code) {
    case NM_CLICK:
       on_click (sender);
       return true;
    case NM_DBLCLK:
       on_double_click (sender);
       return true;
    case NM_RETURN:
       on_enterkey (sender);
       return true;
    case NM_RCLICK:
       on_right_click (sender);
       return true;
    case NM_RDBLCLK:
       on_right_double_click (sender);
       return true;
    case NM_SETFOCUS:
       on_set_focus (sender);
       return true;
    case NM_KILLFOCUS:
       on_kill_focus (sender);
       return true;
    default:
       return false;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of controls
} // end of tomahawk
ENDWRAP



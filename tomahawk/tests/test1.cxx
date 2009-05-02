// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\test1.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include "ratwin\window.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\window.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "tomahawk\controls\edit.h"

#include <iostream.h>

using namespace Dlugosz;
using tomahawk::window;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

tomahawk::controls::rtf_multiline* make_richedit (window* parent)
 {
// using ratwin::types::point;
 tomahawk::controls::rtf_multiline* w2= new tomahawk::controls::rtf_multiline;
 const int child_id= 0;
 w2->create ("Hello World!", parent, child_id);
 return w2;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public window, public classics::debug::noisy1 {
   typedef window Base;
   ~test_window() { if (editbox)  editbox->dec_reference(); }
   tomahawk::controls::rtf_multiline* editbox;
   bool on_move (int x, int y);
   void on_initialize();
   bool on_size (size_state, unsigned width, unsigned height);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_size (size_state flag, unsigned width, unsigned height)
 {
 editbox->move (0,0, width, height);
 return Base::on_size (flag,width,height); 
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void test_window::on_initialize()
 {
 editbox= make_richedit (this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_move (int x, int y) 
 {
 editbox->format_italic();
 editbox->replace_sel ("I've been moved.\r\n"); 
 cout << "moved: " << x << ',' << y << endl;
 return Base::on_move (x,y);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    window::handle wnd (new test_window);
    wnd->create ("Hello!");
    wnd->show (showflags);
    wnd->update();
    window::simple_message_loop();
    }
 catch (const char* message) {
    cout << "I got an error:  " << message << endl;
    return 2;
    }

 return 0;
 }
 


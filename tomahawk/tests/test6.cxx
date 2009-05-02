// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\test6.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include "ratwin\window.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\window.h"
#include "tomahawk\dialog_window.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "tomahawk\controls\edit.h"

#include <iostream.h>

using namespace Dlugosz;
using tomahawk::window;
using tomahawk::created_window;
using tomahawk::dialog_window;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public created_window {
   typedef window Base;
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_dialog : public dialog_window {
   tomahawk::controls::edit_base::handle blank1, blank2;
public:
   typedef tomahawk::derived_handle <test_dialog, dialog_window> handle;
   void run (window::handle owner);
   void on_initialize();
   bool on_button_clicked (int id);
   test_dialog() : blank1 (new tomahawk::controls::text), blank2 (new tomahawk::controls::text) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_dialog::on_initialize()
 {
 blank1->attach_to_child (1000, this);
 blank2->attach_to_child (1003, this);
 dialog_window::on_initialize();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
   
void test_dialog::run (window::handle owner)
 {
 dialog_window::run (int ("test_dialog"), owner);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_dialog::on_button_clicked (int id)
 {
 if (id == 1001) {
    blank2->replace_sel ("howdy ho.");
    return true;
    }
 return dialog_window::on_button_clicked (id);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class start_window : public created_window {
   typedef window Base;
   bool on_close()  { 
       created_window::handle wnd (new test_window);
       wnd->create ("Second");
       wnd->show();
       wnd->update();
       test_dialog::handle dlg (new test_dialog);
       dlg->run (wnd);
       return false;
       }   
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    created_window::handle wnd (new start_window);
    wnd->create ("hello!");
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
 



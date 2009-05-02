// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\test7.cxx
// Revision: public build 4, shipped on 29-Aug-98

#include "ratwin\window.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\window.h"
#include "tomahawk\dialog_window.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "tomahawk\controls\edit.h"
#include "classics\string.h"
#include "ratwin\utilities.h"  //MessageBox for error handling

using namespace Dlugosz;
using tomahawk::window;
using tomahawk::created_window;
using tomahawk::dialog_window;
using ratwin::util::MessageBox;
using classics::collections::string;

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
 switch (id) {
    case 1001: {
       string val;
       blank1->get_value (val);
       blank2->set_value (val);
       return true;
       }
    case 1002: {
       string val ("12345");
       blank1->set_text (val);
       MessageBox ("Button has been pressed.", "notice");
       return true;
       }
    default:   
       return dialog_window::on_button_clicked (id);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    created_window::handle wnd (new test_window);
    wnd->create ("Second");
    wnd->show();
    wnd->update();
    test_dialog::handle dlg (new test_dialog);
    dlg->run (wnd);
    window::simple_message_loop();
    }
 catch (const char* message) {
    MessageBox (message, "Exception Caught");
    return 2;
    }

 return 0;
 }
 



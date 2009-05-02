// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\test12.cxx
// Revision: public build 4, shipped on 29-Aug-98

#include "classics\string.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"
#include "tomahawk\window.h"
#include "tomahawk\window_factory.h"
#include "ratwin\WM_constants.h"
#include "ratwin\utilities.h"
#include "tomahawk\dialog_window.h"

//using namespace Dlugosz;
using classics::string;
using ratwin::util::MessageBox;
using tomahawk::window;
using tomahawk::dialog_window;
using tomahawk::point;
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_dialog : public dialog_window {
public:
   typedef tomahawk::derived_handle <test_dialog, dialog_window> handle;
   void run ();
   void on_initialize();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_dialog::on_initialize()
 {
 dialog_window::on_initialize();

 using namespace ratwin::WM_constants;
 using namespace ratwin::window;
 ratwin::types::HWND parent= get_handle();
 int childID= 101;
 CreateWindow ("EDIT", "", WS_CHILD | WS_VISIBLE | /*ES_SAVESEL |*/ WS_HSCROLL,
    0,0, 400,100, parent, (ratwin::types::HMENU)childID, ratwin::util::get_Instance(), 0);

 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
   
void test_dialog::run ()
 {
 dialog_window::run (int ("output"));
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 try {
    test_dialog::handle dialog (new test_dialog);
    dialog->run();
    window::simple_message_loop();
    }
 catch (classics::exception& error) {
    error.show();
    return 2;
    }
 catch (const char* message) {
    MessageBox (message, "Exception Caught");
    return 2;
    }

 return 0;
 }



// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\tests\memoline.cxx
// Revision: public build 8, shipped on 11-July-2006

#include "tomahawk\dialog_window.h"
#include "classics\string.h"
#include "ratwin\dialog.h"  //MessageBox for error handling
#include "tomahawk\controls\binder.h"   //for linking dialog box to record
#include <time.h>  //to get and format the current time

using namespace Dlugosz;
using tomahawk::window;
using tomahawk::created_window;
using tomahawk::dialog_window;
using ratwin::dialog::MessageBox;
using classics::collections::string;

const int hourblanks= 4;

struct record {
   string name;
   string date;
   string hours[hourblanks];
   void set_values();
   };

void record::set_values()
// Sets a meaningful starting value for the fields.
 {
 name= "Sandra";
 time_t ltime;
 ::time (&ltime);
 struct tm* today= localtime( &ltime );
 char buf [128];
 strftime (buf, 128, "%d-%b-%y", today);
 date= buf;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_dialog : public dialog_window, public record {
public:
   typedef tomahawk::derived_handle <test_dialog, dialog_window> handle;
   void run () { dialog_window::run (101); }
   void create_bindings();
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_dialog::create_bindings()
 {
 using tomahawk::controls::bind;
 bind (get_control(1001), name);
 bind (get_control(1000), date);
 for (int loop= 0;  loop < hourblanks;  loop++) {
    bind (get_control(1002+loop), hours[loop]);
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    test_dialog::handle dlg (new test_dialog);
    dlg->set_values();
    dlg->run();
    window::simple_message_loop();
    }
 catch (const char* message) {
    MessageBox (message, "Exception Caught");
    return 2;
    }

 return 0;
 }
 



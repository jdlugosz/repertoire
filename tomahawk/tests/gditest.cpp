// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\gditest.cpp
// Revision: public build 5, shipped on 8-April-1999

#include "ratwin\window.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\window.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "classics\string.h"
#include "ratwin\utilities.h"  //MessageBox for error handling
#include "ratwin\gdi.h"

using namespace Dlugosz;
using tomahawk::window;
using tomahawk::created_window;
using ratwin::util::MessageBox;
using classics::collections::string;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public created_window {
   typedef window Base;
   bool on_paint (ratwin::gdi::PAINTSTRUCT&);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_paint (ratwin::gdi::PAINTSTRUCT& ps)
 {
 using namespace ratwin;
 static types::HBRUSH brush= gdi::CreateSolidBrush (0xff0000);
 types::HGDIOBJ old= gdi::SelectObject (ps.hdc, brush);
 gdi::RoundRect (ps.hdc, 10,10, 40,50, 5,5);
// bool b= gdi::DeleteObject (brush);
 types::HGDIOBJ old2= gdi::SelectObject (ps.hdc, old);
// b= gdi::DeleteObject (brush);
 gdi::SelectObject (ps.hdc, brush);
 gdi::RoundRect (ps.hdc, 50,60, 90,140, 5,5);
// b= gdi::DeleteObject (brush);
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    created_window::handle wnd (new test_window);
    wnd->create ("GDI Explorations");
    wnd->show();
    wnd->update();
    window::simple_message_loop();
    }
 catch (const char* message) {
    MessageBox (message, "Exception Caught");
    return 2;
    }

 return 0;
 }
 




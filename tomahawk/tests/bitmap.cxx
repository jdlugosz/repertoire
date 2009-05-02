// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\bitmap.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include "ratwin\window.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\window.h"
#include "classics\pointers.h"
#include "classics\debug.h"
#include "classics\string.h"
#include "ratwin\utilities.h"  //MessageBox for error handling
#include "ratwin\GDI.h"
#include "tomahawk\scroll.h"
#include "ratwin\resource.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

using namespace Dlugosz;
using tomahawk::window;
using tomahawk::created_window;
using ratwin::util::MessageBox;
using classics::collections::string;
using tomahawk::window_factory;

 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public created_window, public tomahawk::scroll_mixin {
   typedef window Base;
//   const ratwin::bitmap::BITMAPINFOHEADER* ginger;
   ratwin::bitmap::BITMAPINFOHEADER* drawing;
   tomahawk::scroller vscroll, hscroll;
   bool reroute (tomahawk::event& e)  { vscroll.process_event(e); hscroll.process_event(e); return created_window::reroute(e); }  //change later.
public:
   bool on_paint (ratwin::gdi::PAINTSTRUCT&);
   bool on_size (size_state, unsigned width, unsigned height);
   void on_initialize();
   window_factory& get_default_factory();
   test_window() : vscroll (this,vscroll.vertical), hscroll(this,hscroll.horizontal) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& test_window::get_default_factory()
 {
 static tomahawk::window_factory_userdef wc ("my program's class");
 using namespace ratwin::window;
 wc.window_factory::style |= WS_VSCROLL | WS_HSCROLL;
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int rand_round (double x)
 {
 x /= 8;    //handle 5, not 8, bit pixels
 int val= floor(x);
 double frac= x - val;
 int rr= rand();
 double test=  rr/double(RAND_MAX);
 if (test < frac)  val++;
 return 8*val;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int inline sqr (int x) { return x*x; }

byte compute_point (int point_x, int point_y, int r_x, int r_y, int distance)
 {
 int result= rand_round (255 * sqrt (double(sqr(point_y-r_y) + sqr(point_x-r_x))) / (1.5*distance));
 if (result > 255)  result= 255;
 return 255-result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void testimage (byte* data)
 {
 // fundimental constants
 const int center_x= 320;
 const int center_y= 240;
 const int radius= 180;
 // lay out my radiating points
 const int B_x= center_x;
 const int B_y= center_y - radius;
 int y= radius/2;
 int x= y * sqrt(3.0);
 const int R_x= center_x - x;
 const int R_y= center_y + y;
 const int G_x= center_x + x;
 const int G_y= center_y + y;
 const int dist= G_x - R_x;  //how far between my radiators
 srand (1234);
 for (y= 0;  y < 480;  y++) {
    for (x= 0;  x < 640;  x++) {
       *data++ = compute_point (x,y, B_x,B_y, dist);
       *data++ = compute_point (x,y, G_x,G_y, dist);
       *data++ = compute_point (x,y, R_x,R_y, dist);
       }
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::on_initialize()
 {
 using namespace ratwin::window;
 vscroll.set_range (hwnd, 0, 480);
 hscroll.set_range (hwnd, 0, 640);
 hscroll.linesize= vscroll.linesize= 10;

 using namespace ratwin::resource;
// using ratwin::types::HRSRC;
// HRSRC handle= FindResource (ratwin::util::get_Instance(), "ginger", 2);
// ginger= static_cast<const ratwin::bitmap::BITMAPINFOHEADER*>(LoadResource (ratwin::util::get_Instance(), handle));
 const int size= 640*480*3;
 drawing= reinterpret_cast<ratwin::bitmap::BITMAPINFOHEADER*> (new char [size + 40]);
 byte* data= reinterpret_cast <byte*> (drawing+1);
 drawing->biSize= 40;
 drawing->biWidth= 640;
 drawing->biHeight= 480;
 drawing->biPlanes= 1;
 drawing->biBitCount= 24;
 drawing->biCompression= 0;
 drawing->biSizeImage= 640*480*3;
 drawing->biXPelsPerMeter=0;
 drawing->biYPelsPerMeter=0;
 drawing->biClrUsed=0;
 drawing->biClrImportant=0;
#if 0
 for (int y= 0;  y < 480;  y++) {
    for (int x= 0;  x < 640;  x++) {
       data[0]= y;
       data[1]= 0;
       data[2]= x;
       data += 3;
       }
    }
#endif
 testimage (data);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_paint (ratwin::gdi::PAINTSTRUCT& ps)
 {
 const void* data= drawing + 1;  //just after the header
 ratwin::gdi::SetDIBitsToDevice (ps.hdc, -hscroll.position,-vscroll.position, 640,480, 0,0, 0,480, data, drawing, ratwin::gdi::DIB_RGB_COLORS);
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_size (size_state state, unsigned width, unsigned height)
 {
 hscroll.forwarded_on_size (hwnd, state, width, height);
 vscroll.forwarded_on_size (hwnd, state, width, height);
 return Base::on_size (state, width, height);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 using namespace tomahawk;

 try {
    created_window::handle wnd (new test_window);
    wnd->create ("Bitmap Experiments");
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
 



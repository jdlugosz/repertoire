// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\tests\test9.cxx
// Revision: public build 8, shipped on 11-July-2006

#include "classics\string.h"
#include "classics\exception.h"
#include "ratwin\utilities.h"
#include "tomahawk\window.h"
#include "tomahawk\win_embellishee.h"
#include "tomahawk\window_factory.h"
#include "tomahawk\scroll.h"
#include "tomahawk\color_t.h"
#include "tomahawk\gdi\text_drawer.h"

//using namespace Dlugosz;
using classics::string;
using ratwin::util::MessageBox;
using tomahawk::window;
using tomahawk::created_window;
using tomahawk::window_factory;
using tomahawk::paintstruct;
using tomahawk::color_t;
using tomahawk::point;
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public created_window, public tomahawk::win_embellishee {
   typedef window Base;
   int lineheight, charwidth;
   int linecount;
   classics::handle<tomahawk::scroller> vscroll, hscroll;
public:
   typedef classics::handle<test_window> handle;
   bool on_paint (paintstruct&);
   void on_initialize();
   window_factory& get_default_factory();
   test_window() : vscroll(new tomahawk::scroller(this,this,tomahawk::scroller::vertical)), hscroll(new tomahawk::scroller(this,this,tomahawk::scroller::horizontal)) {}
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

window_factory& test_window::get_default_factory()
 {
 // factory concept still needs work.
 static tomahawk::window_factory_userdef wc ("my program's class");
 using namespace ratwin::window;
 wc.window_factory::style = WS_VSCROLL | WS_HSCROLL | WS_CHILD|WS_CLIPSIBLINGS;
 wc.window_factory::style2= WS_EX_CLIENTEDGE;
// wc.window_factory::style = WS_VSCROLL | WS_HSCROLL | WS_CHILD|WS_THICKFRAME;
 return wc;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::on_initialize()
 {
 // gather my context information
 tomahawk::window_dc dc (get_smartptr());
 tomahawk::textmetric tm (dc);
 // set my other members
 lineheight= tm.nominal_lineheight();
 charwidth= tm.AveCharWidth;
 linecount= 101;
 vscroll->linesize= lineheight;
 hscroll->linesize= charwidth;
 pagesize (point(50*charwidth, linecount*lineheight));
 // >> need to set initial viewsize here.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool test_window::on_paint (paintstruct& ps)
 {
 const int firstline= ((ps.rcPaint.top+ scrollpos().y) / lineheight) -1;
 const int lastline= ((ps.rcPaint.bottom+scrollpos().y) / lineheight) -1;
 tomahawk::text_drawer output (ps);
 output.pos (point(
    output.leftedge= 3 -scrollpos().x,
    lineheight * (firstline+1) - scrollpos().y ));
 output.lineheight= lineheight;
 color_t blue (0,0,0xff);
 ps.bk_color_window();
 color_t oldcolor= ps.text_color();
 for (int loop= firstline;  loop <= lastline;  loop++) {
    if (loop == -1) {
       output << "lineheight= " << lineheight << " pixels\n";
       }
    else if (loop >= 100)  break;
    else {
       output << loop << " squared is " << loop*loop << ',';
       output << blue << " doubled is " << 2*loop << oldcolor << output.endl;
       }
    }
 return true;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class frame_window : public created_window {
   test_window::handle child1, child2, child3;
public:
   void on_initialize();
   bool on_size (size_state, unsigned width, unsigned height);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void frame_window::on_initialize()
 {
 child1= new test_window;
 child2= new test_window;
 child3= new test_window;
 point origin1 (5,5);
 point origin2 (20,20);
 point extent (100,60);
 child1->create ("the child", this, 0, origin1, extent);
 child1->show();
 child2->create ("second child", this, 0, origin2, extent);
 child2->show();
 child3->create ("third child", this);
 child3->show();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool frame_window::on_size (size_state s, unsigned width, unsigned height)
 {
 const int y1= height*2/3;
 child1->move (point(0,0), width/2, y1);
 child2->move (point(width/2, 0), width/2, y1);
 child3->move (point(0,y1), width, height-y1);
 return false;  //continue with default processing.
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 try {
//    created_window::handle wnd (new test_window);
    created_window::handle wnd (new frame_window);
    wnd->create ("Test 9");
    wnd->show();
    wnd->update();
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


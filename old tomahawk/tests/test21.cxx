// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\tests\test21.cxx
// Revision: public build 6, shipped on 28-Nov-1999

#include "classics\exception.h"
#include "tomahawk\controls\tree.h"
#include "tomahawk\rect.h"
#include "ratwin\utilities.h"
#include "classics\string_ios.h"
#include "ratwin\menu.h"
#include "ratwin\menu.h"
#include "tomahawk\multimatte.h"
#include "tomahawk\controls\edit.h"
#include <iostream>

using classics::string;
using classics::ushort;
using std::cout;
using std::endl;
using classics::Fmt;

ratwin::types::HMENU m;

void settext (const string&);

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// class info is a tree item.
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class info : public tomahawk::controls::tree::info {
   string S;
   info (const info&);  //not defined
   void operator= (const info&);  //not defined
public:
   static int count;
   info (string S) : S(S) { ++count; }
   ~info() { --count; }
   string label() const { return S; }
   void on_key_down (tomahawk::controls::tree* sender, ushort);
   void on_right_click (tomahawk::controls::tree* sender);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int info::count= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void info::on_key_down (tomahawk::controls::tree* sender, ushort keycode)
 {
 cout << "on_key_down " << keycode << endl;
 switch (keycode) {
    case 45: { //INS key
       for (int loop= 0;  loop < 10;  loop++) {
          sender->insert_child (this, new info ("added child"));
          sender->expand(this);
          }
       break;
       }
    case 46:  //DEL key
       sender->remove (this);
       break;
    case 191: { // [/?] key
       string s;
       Fmt(s) << "There are " << info::count << " nodes alive.";
       settext (s);
       }
       break;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void info::on_right_click (tomahawk::controls::tree* sender)
 {
 context_menu (sender, m, sender->get_handle());
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
// class test_window is my application's main frame
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class test_window : public tomahawk::created_window {
   classics::handle<tomahawk::controls::tree> tree1, tree2;
   tomahawk::multimatte::handle hs;
   void add_testchildren (const info* parent, classics::handle<tomahawk::controls::tree> tree);
   void add_testdata(classics::handle<tomahawk::controls::tree> tree);
public:
   classics::handle<tomahawk::controls::text> stat;
   test_window() {}
   void on_initialize();
   void add_testdata();
   };

test_window* global;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::on_initialize()
 {
 hs= tomahawk::multimatte::createnew (this);
 enum layout_control_values { left,top,right,bottom,sep,ysplit };
 hs->add_control_value_prop (sep, left,right, 1,2);
 hs->add_control_value_fixed (ysplit, bottom, -25);
 hs->add_horizontal_slider (sep, top,ysplit);
 // left tree
 tomahawk::controls::tree* tree= new tomahawk::controls::tree;
 tree1= tree;
 tree->create_control (this, 1);
 classics::handle<tomahawk::window> child1 (tree);
 hs->add_request (child1, left,top, sep,ysplit);
 // right tree
 tree= new tomahawk::controls::tree;
 tree2= tree;
 tree->create_control (this, 2);
 classics::handle<tomahawk::window> child2 (tree);
 hs->add_request (child2, sep,top, right,ysplit);
 // status bar
 tomahawk::controls::text* editbar= new tomahawk::controls::text;
 stat= editbar;
 editbar->create_control (this, 3);
 classics::handle<tomahawk::window> child3 (editbar);
 hs->add_request (child3, left,ysplit, right,bottom);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::add_testchildren (const info* parent, classics::handle<tomahawk::controls::tree> tree)
 {
 for (int loop= 0;  loop < 10;  loop++) {
    tree->insert_child (parent, new info ("child"));
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::add_testdata(classics::handle<tomahawk::controls::tree> tree)
 {
 info* p= new info ("Alpha");
 tree->insert (p);
 add_testchildren (p, tree);
 p= new info ("Beta");
 tree->insert (p);
 add_testchildren (p, tree);
 p= new info ("Gamma");
 tree->insert (p);
 add_testchildren (p, tree);
 p= new info ("Delta");
 tree->insert (p);
 add_testchildren (p, tree);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test_window::add_testdata()
 {
 add_testdata (tree1);
 add_testdata (tree2);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void settext (const string& s)
 {
 global->stat->set_value (s);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int __stdcall WinMain (ratwin::types::HINSTANCE hInstance, ratwin::types::HINSTANCE, char* commandline, int showflags)
 {
 cout << "Test21 running" << endl;
 m= ratwin::menu::LoadMenu (hInstance, "ITEMMENU");
 m= ratwin::menu::GetSubMenu (m, 3);
 try {
    classics::handle<test_window> wnd (global=new test_window);
    wnd->create ("Test 21");
    wnd->add_testdata();
    wnd->show();
    wnd->update();
    tomahawk::window::simple_message_loop();
    }
 catch (classics::exception& error) {
    ratwin::util::MessageBox ("info written to cerr", "Exception Caught");
    error.show();
    return 2;
    }
 catch (const char* message) {
    ratwin::util::MessageBox (message, "Exception Caught");
    return 2;
    }
 cout << "Test21 exiting" << endl;
 cout << "There are " << info::count << " nodes still allocated." << endl;
 return 0;
 }


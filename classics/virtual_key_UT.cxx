// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\virtual_key_UT.cxx
// Revision: public build 9, shipped on 18-Oct-2006

#include "classics\virtual_key.h"
#if _MSC_VER == 1310
   #pragma warning( disable : 4348 )  // Microsoft's std headers don't clean compile!
#endif
#include <iostream>
#include "classics\string_ios.h"
#include "ratwin\io\console.h"
#include "ratwin\io\general.h"
#include "ratwin\io\file=struct.h"
using classics::string;
using std::cout;
using std::endl;
using namespace classics::VK;

int errorcount= 0;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test1 (int modifier)
 {
 for (int loop= 0;  loop < 256;  loop++) {
    VK key= VK(modifier+loop);
    string s= as_ustring(key);
//    cout << loop << ". " << s << endl;
    VK k= parse<VK> (s);
    if (k != key) {
       cout << "*failed " << int(key) << " => " << s << " => " << int(k) << endl;
       ++errorcount;
       }
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void test2()
 {
 cout << "monitoring Console events." << endl;
 using namespace ratwin::io;
 ratwin::types::HANDLE console= GetStdHandle(STD_INPUT_HANDLE);
 if (console == ratwin::io::INVALID_FILE) {
    classics::win_exception X ("test2", __FILE__, __LINE__);
    X += "can't get std input handle";
    throw X;
    }
 INPUT_RECORD<wchar_t> rec;
 for (int loop= 0;  loop < 10;  loop++) {
    int outlen;
    bool result= ReadConsoleInput (console, &rec, 1, &outlen);
    if (!result) {
       classics::win_exception X ("test2", __FILE__, __LINE__);
       X.show();
       }
    switch (rec.EventType) {
       case KEY_EVENT: {
          KEY_EVENT_RECORD<wchar_t>& r= rec.KeyEvent;
          cout << "Key Event - " << (r.KeyDown ? "Down" : "Up") << endl;
          if (r.RepeatCount != 1)  cout << "\trepeat count: " << r.RepeatCount << endl;
          VK vkey= VKencode (r.VirtualKeyCode, r.ControlKeyState);
          cout << "\tKey: " << string (as_ustring(vkey)) << " - ";
          cout << "scan code: " << r.VirtualScanCode << " - ";
          cout << "character: 0x" << std::hex << int(r.Char);
          if (r.Char > ' ' && r.Char <= '~')  cout << '\'' << char(r.Char) << '\'';
          cout << "\n\tcontrol key state: 0x" << r.ControlKeyState << std::dec << endl;
          } break;
       case MOUSE_EVENT: {
          cout << "Mouse Event" << endl;
          } break;
       case WINDOW_BUFFER_SIZE_EVENT:
          cout << "Window Buffer Size Event" << endl;
          break;
       case MENU_EVENT:
          cout << "Menu Event" << endl;
          break;
       case FOCUS_EVENT:
          cout << "Focus Event" << endl;
          break;
       default:
          cout << "Unknown event type " << rec.EventType << endl;
       }
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


int main()
 {
 try {
    test1 (0);
    test1 (ShiftKey);
    test1 (ControlKey);
    test1 (AltKey);
    test1 (ShiftKey+AltKey);
    ///
    test2();
    }
 catch (classics::exception& X) {
    cout << "exception found." << endl;
    X.show();
    }
 catch (...) {
    cout << "unknown exception found." << endl;
    }
 cout << "There were " << errorcount << " errors." << endl;
 return 0;
 }
 

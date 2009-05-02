// Kodak Foundation Components ©2000 Kodak Health Imaging (Dallas)
// Information:  intranet website not yet established.  Contact Lance VanNostrand for info.
// Documentation:  reference manual is part number 2E0104.
// File: Dependant_Libs\Repertoire\ratwin\window.cpp
// Version: Iteration 2, Revision 1, Patch 2, released 11-Oct-2000
// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// Revision: public build 5, shipped on 8-April-1999

#define RATWIN_EXPORT __declspec(dllexport)

#include "ratwin\window.h"
#include "ratwin\resource.h"
#include "ratwin\color.h"
#include "ratwin\utilities.h"
#include "ratwin\WM_constants.h"

STARTWRAP
namespace ratwin {
namespace window {

static  // compiler (VC6) couldn't find it in unnamed namespace!
long __stdcall really_minimal_window_proc (types::HWND wnd, unsigned mess, unsigned p1, ulong p2)
 {
 if (mess == WM_constants::WM_DESTROY) {
    PostQuitMessage(0);
    return 0;
    }
 else return DefWindowProc (wnd, mess, p1, p2);
 }


template<typename CharT>
window_class<CharT>::window_class (const CharT* classname)
 {
 style= 0;
 lpfnWndProc= &really_minimal_window_proc;
 cbClsExtra= 0;
 cbWndExtra= 0;
 hInstance= util::get_Instance();
 hIcon= 0;
 hCursor= resource::LoadCursor (0, resource::IDC_ARROW);
 colorBackground= 1+color::COLOR_WINDOW;
 lpszMenuName= 0;
 lpszClassName= classname;
 }


// explicit instantiations
template class window_class<char>;
template class window_class<wchar_t>;


types::HWND CreateWindow (const char* lpClassName, const char* lpWindowName, ulong dwStyle)
 {
 return CreateWindow (lpClassName, lpWindowName, dwStyle,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    0, ChildidOrHMENU(), util::get_Instance(), 0);
 }


types::HWND CreateWindowEx (ulong moreflags, const char* lpClassName, const char* lpWindowName, ulong dwStyle)
 {
 return CreateWindowEx (moreflags, lpClassName, lpWindowName, dwStyle,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    0, ChildidOrHMENU(), util::get_Instance(), 0);
 }

#if 0
classics::string GetClassName (types::HWND hwnd)
 {
 // There does not seem to be a way to find out the length of the ClassName.
 // So, I have a simple hard-coded limit.  It only has to be long enough for
 // all class names that I'm actually interested in.  For general use, note that
 // the returned name is truncated to MAX characters.
 const int MAX=64;
 char buf [1+MAX];
 int len= GetClassName (hwnd, buf, 1+MAX);
 if (len==0)  throw "error in get_WC_name";
 return buf;
 }
#endif

}}
ENDWRAP


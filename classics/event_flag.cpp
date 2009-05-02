// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\event_flag.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)

#include "ratwin\tasking\event.h"
#include "ratwin\handle.h"
#include "classics\exception.h"
#include "classics\event_flag.h"
#include "classics\string_ios.h"  //for formatting error messages
#include "classics\win_handle.h"
#include "ratwin\utilities.h"

STARTWRAP
namespace classics {
using classics::wFmt;
using std::endl;
static const char FNAME[]= __FILE__;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

event_flag::event_flag (type tp, bool initial_state)
      : H (ratwin::tasking::CreateEvent(tp, initial_state))
{}

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

ratwin::types::Kernel_HANDLE event_flag::common_create (bool tp, bool initial_state, const ustring& name, const ratwin::types::SECURITY_ATTRIBUTES* sa)
 {
 static bool Unicode= true;
 ratwin::types::Kernel_HANDLE H;
 if (Unicode) {
    wstring s= name;
    const wchar_t* p= s.c_str();
    H= ratwin::tasking::CreateEvent (tp, initial_state, p, *sa);
    if (H)  return H;
    int errorcode= ratwin::util::GetLastError();
    if (errorcode == win_exception::call_not_implemented_error)  {
       Unicode= false;
       goto ANSI;
       }
    throw win_exception ("Classics", FNAME, __LINE__, errorcode);
    }
 ANSI: {
    string s= name;
    const char* p= s.c_str();
    H= ratwin::tasking::CreateEvent (tp, initial_state, p, *sa);
    if (!H)  throw win_exception ("Classics", FNAME, __LINE__);
    return H;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

event_flag::~event_flag()
 {
 ratwin::CloseHandle(H);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void event_flag::set() const 
 {
 if (!ratwin::tasking::SetEvent (h())) {
    win_exception X ("Classics", __FILE__, __LINE__);
    X += L"Error occured trying to set an event_flag.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void event_flag::reset() const 
 { 
 if (!ratwin::tasking::ResetEvent (h())) {
    win_exception X ("Classics", __FILE__, __LINE__);
    X += L"Error occured trying to reset an event_flag.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void event_flag::pulse() const 
 { 
 if (!ratwin::tasking::PulseEvent (h())) { 
    win_exception X ("Classics", __FILE__, __LINE__);
    X += L"Error occured trying to pulse an event_flag.\n";
    throw X;
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool event_flag::wait (unsigned timeout) const 
 {
 try {
    return classics::wait (h(), timeout);
    }
 catch (exception& X) {
    X ("Classics", "event_flag::wait", __FILE__, __LINE__);
    throw;
    }
 return false;  //stupid compiler!
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end classics
ENDWRAP


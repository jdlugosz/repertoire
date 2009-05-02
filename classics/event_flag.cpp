// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\event_flag.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)

#include "ratwin\tasking\event.h"
#include "ratwin\handle.h"
#include "classics\exception.h"
#include "classics\event_flag.h"
#include "classics\string_ios.h"  //for formatting error messages
#include "classics\win_handle.h"

STARTWRAP
namespace classics {
using classics::wFmt;
using std::endl;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

event_flag::event_flag (type tp, bool initial_state, const char* name)
      : H (ratwin::tasking::CreateEvent(tp, initial_state, name))
{}

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


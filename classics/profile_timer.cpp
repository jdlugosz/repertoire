// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\profile_timer.cpp
// Revision: public build 5, shipped on 8-April-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include "classics\profile_timer.h"
#include "ratwin\tasking\thread.h"

STARTWRAP
namespace classics {

using ratwin::tasking::GetThreadTimes;

ratwin::types::HANDLE thread_pseudohandle= ratwin::tasking::GetCurrentThread();

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

profile_timer::profile_timer()
 : User(0), Kernel(0), User_start(0), Kernel_start(0)
 { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void profile_timer::start()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 GetThreadTimes (thread_pseudohandle, x1, x2, Kernel_start, User_start);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void profile_timer::stop()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 __int64 Kernel_stop, User_stop;
 GetThreadTimes (thread_pseudohandle, x1, x2, Kernel_stop, User_stop);
 User += (User_stop - User_start);
 Kernel += (Kernel_stop - Kernel_start);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void profile_timer::snapshot()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 __int64 Kernel_stop, User_stop;
 GetThreadTimes (thread_pseudohandle, x1, x2, Kernel_stop, User_stop);
 User += (User_stop - User_start);
 Kernel += (Kernel_stop - Kernel_start);
 // note the stop time as the new start time, so timing is seamless
 User_start= User_stop;
 Kernel_start= Kernel_stop;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void profile_timer::reset()
 {
 Kernel= User= 0;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end namespace classics
ENDWRAP


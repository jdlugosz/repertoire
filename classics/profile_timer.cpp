// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\profile_timer.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\new.h"
#include "classics\profile_timer.h"
#include "ratwin\tasking\thread.h"
#include "ratwin\datetime.h"
#include "ratwin\tasking\process.h"
#include "ratwin\io\general.h"
#include "classics\exception.h"
#include "ratwin\handle.h"

STARTWRAP
namespace classics {

using ratwin::tasking::GetThreadTimes;
using ratwin::GetSystemTimeAsFileTime;
using ratwin::types::Thread_HANDLE;
using ratwin::CloseHandle;

Thread_HANDLE thread_pseudohandle= ratwin::tasking::GetCurrentThread();
ratwin::types::HANDLE process_pseudohandle= ratwin::tasking::GetCurrentProcess();

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

static Thread_HANDLE get_thread_handle (Thread_HANDLE original= thread_pseudohandle)
 {
 Thread_HANDLE result;
 bool OK= ratwin::io::DuplicateHandle (process_pseudohandle, original, process_pseudohandle, result, 0, false, 2);
 if (!OK)  {
    classics::win_exception X ("Classics", __FILE__, __LINE__);
    throw X;
    }
 return result;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

profile_timer::profile_timer()
 : User(0), Kernel(0), User_start(0), Kernel_start(0), Wall(0), Wall_start(0), thread (get_thread_handle())
 { }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

profile_timer::profile_timer (Thread_HANDLE desired_thread)
 : User(0), Kernel(0), User_start(0), Kernel_start(0), Wall(0), Wall_start(0)
 {
 if (desired_thread == thread_pseudohandle)  desired_thread= get_thread_handle();
 thread= desired_thread;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

 profile_timer::profile_timer (const profile_timer& other)
 : User(other.User), Kernel(other.Kernel), User_start(other.User_start), Kernel_start(other.Kernel_start), Wall(other.Wall), Wall_start(other.Wall_start), thread (get_thread_handle(other.thread))
{ } 

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

profile_timer& profile_timer::operator= (const profile_timer& other)
 {
 if (&other == this)  return *this;
 User= other.User;
 Kernel= other.Kernel;
 User_start= other.User_start;
 Kernel_start= other.Kernel_start;
 Wall= other.Wall;
 Wall_start= other.Wall_start;
 CloseHandle (thread);
 thread= get_thread_handle(other.thread);
 return *this;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

profile_timer::~profile_timer()
 {
 CloseHandle (thread);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void profile_timer::start()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 GetThreadTimes (thread, x1, x2, Kernel_start, User_start);
 Wall_start= GetSystemTimeAsFileTime();
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void profile_timer::stop()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 __int64 Kernel_stop, User_stop, Wall_stop;
 GetThreadTimes (thread, x1, x2, Kernel_stop, User_stop);
 Wall_stop= GetSystemTimeAsFileTime();
 User += (User_stop - User_start);
 Kernel += (Kernel_stop - Kernel_start);
 Wall += (Wall_stop - Wall_start);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void profile_timer::snapshot()
 {
 __int64 x1,x2;  //"out" parameters I don't care about
 __int64 Kernel_stop, User_stop, Wall_stop;
 GetThreadTimes (thread, x1, x2, Kernel_stop, User_stop);
 Wall_stop= GetSystemTimeAsFileTime();
 User += (User_stop - User_start);
 Kernel += (Kernel_stop - Kernel_start);
 Wall += (Wall_stop - Wall_start);
 // note the stop time as the new start time, so timing is seamless
 User_start= User_stop;
 Kernel_start= Kernel_stop;
 Wall_start= Wall_stop;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
 
void profile_timer::reset()
 {
 Kernel= User= Wall= 0;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end namespace classics
ENDWRAP


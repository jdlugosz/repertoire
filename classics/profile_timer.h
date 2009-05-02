// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\profile_timer.h
// Revision: post-public build 6

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "ratwin\base.h"

STARTWRAP
namespace classics {

class profile_timer {
   ratwin::types::Thread_HANDLE thread;
   __int64 User;
   __int64 Kernel;
   __int64 Wall;
   __int64 User_start;
   __int64 Kernel_start;
   __int64 Wall_start;
public:
   CLASSICS_EXPORT profile_timer();
   CLASSICS_EXPORT profile_timer (ratwin::types::Thread_HANDLE thread);
   CLASSICS_EXPORT profile_timer (const profile_timer&);
   CLASSICS_EXPORT profile_timer& operator= (const profile_timer&);
   CLASSICS_EXPORT ~profile_timer();
   CLASSICS_EXPORT void start();
   CLASSICS_EXPORT void stop();
   CLASSICS_EXPORT void reset();
   CLASSICS_EXPORT void snapshot();
   // values are returned in the more familiar millisecond scale
   double get_user() const  { return User / 10000.0; }
   double get_kernel() const  { return Kernel / 10000.0; }
   double get_wall() const  { return Wall / 10000.0; }
   };

} // end namespace classics
ENDWRAP


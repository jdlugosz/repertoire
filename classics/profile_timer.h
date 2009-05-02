// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\profile_timer.h
// Revision: public build 4, shipped on 29-Aug-98

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"

STARTWRAP
namespace classics {

class profile_timer {
   __int64 User;
   __int64 Kernel;
   __int64 User_start;
   __int64 Kernel_start;
public:
   CLASSICS_EXPORT profile_timer();
   CLASSICS_EXPORT void start();
   CLASSICS_EXPORT void stop();
   CLASSICS_EXPORT void reset();
   CLASSICS_EXPORT void snapshot();
   // values are returned in the more familiar millisecond scale
   ulong get_user() const  { return User / 10000; }
   ulong get_kernel() const  { return Kernel / 10000; }
   };

} // end namespace classics
ENDWRAP


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\critical_section.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)

#include "ratwin\tasking\CriticalSection.h"
#include "classics\critical_section.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

critical_section::critical_section()
 {
 ratwin::tasking::InitializeCriticalSection(*this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

critical_section::~critical_section()
 {
 ratwin::tasking::DeleteCriticalSection(*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void critical_section::enter()
 {
 ratwin::tasking::EnterCriticalSection(*this);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void critical_section::leave()
 {
 ratwin::tasking::LeaveCriticalSection(*this);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool critical_section::try_enter()
 {
// return ratwin::tasking::TryEnterCriticalSection(*this);
 return false;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

critical_section::critical_section (bool blocked)
 {
 ratwin::tasking::InitializeCriticalSection(*this);
 if (blocked)  enter();
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace classics
ENDWRAP


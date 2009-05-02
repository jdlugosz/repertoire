// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\trial.cxx
// Revision: public build 9, shipped on 18-Oct-2006
#include "classics\new.h"
#include "classics\pointers.h"
using classics::handle;
using classics::can_handle;

int main()
 {
 handle<can_handle> h (new can_handle());
 return 0;
 }

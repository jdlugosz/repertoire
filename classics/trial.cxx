// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\trial.cxx
// Revision: public build 4, shipped on 29-Aug-98
#include "classics\pointers.h"
using classics::handle;
using classics::can_handle;

int main()
 {
 handle<can_handle> h (new can_handle());
 return 0;
 }

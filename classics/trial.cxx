// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\trial.cxx
// Revision: public build 6, shipped on 28-Nov-1999
#include "classics\new.h"
#include "classics\pointers.h"
using classics::handle;
using classics::can_handle;

int main()
 {
 handle<can_handle> h (new can_handle());
 return 0;
 }

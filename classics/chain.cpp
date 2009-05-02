// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\chain.cpp
// Revision: public build 4, shipped on 29-Aug-98

#define CLASSICS_EXPORT __declspec(dllexport)

#include "classics\chain.h"

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

chain_base* chain_head_nt::first()
 {
 return (Next==this) ? 0 : Next;
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

chain_base* chain_head_nt::next_after (chain_base* p)
 {
 chain_base* next= p->Next;
 return (next==this) ? 0 : Next;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of classics
ENDWRAP


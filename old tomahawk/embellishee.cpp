// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\embellishee.cpp
// Revision: public build 8, shipped on 11-July-2006

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\embellishee.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T, typename P>
void apply (
   classics::vararray_g< classics::baro<embellishment> > list,
   P proc,
   T value)
 {
 const int max= list.elcount();
 for (int loop= 0;  loop < max;  loop++) {
    classics::handle<embellishment> target (list[loop]);
    // can't use ->* on smart pointer!  Work on that later.
    embellishment* object= target.operator->();
    (object->*proc) (value);
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

embellishee::embellishee()
 : Page(0)
 {}
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void embellishee::scrollpos (point p)
 {
 apply (List, &embellishment::scrollpos_changed, p);
 Scrollpos= p;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void embellishee::scrollpos (point p, int page)
 {
 apply (List, &embellishment::scrollpos_changed, p);
 apply (List, &embellishment::pagenumber_changed, page);
 Scrollpos= p;
 Page= page;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void embellishee::pagesize (point p)
 {
 apply (List, &embellishment::pagesize_changed, p);
 Pagesize= p;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void embellishee::viewsize (point p)
 {
 apply (List, &embellishment::viewsize_changed, p);
 Viewsize= p;
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end of tomahawk
ENDWRAP


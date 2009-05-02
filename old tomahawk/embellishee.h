// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: old tomahawk\embellishee.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined TOMAHAWK_EMBELLISHEE_INCLUDED
#define TOMAHAWK_EMBELLISHEE_INCLUDED

#include "classics\vararray.h"
#include "tomahawk\embellishment.h"

STARTWRAP
namespace tomahawk {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

class embellishee {
   point Scrollpos;  //logical visible origin
   int Page;  //another dimention to scrolling
   point Pagesize;  // "full" virtual size
   point Viewsize;  // visible part
   classics::vararray_g< classics::baro<embellishment> > List;
   embellishee (const embellishee&);  //not defined
   void operator= (const embellishee&);  //not defined
public:
   void add (const classics::baro<embellishment>& x)  { List.append(x); }
   TOMAHAWK_EXPORT embellishee();
   TOMAHAWK_EXPORT void scrollpos (point);
   TOMAHAWK_EXPORT void scrollpos (point, int page);  //set both at once
   point scrollpos() const  { return Scrollpos; }
   TOMAHAWK_EXPORT void pagesize (point);
   TOMAHAWK_EXPORT void viewsize (point);
   point pagesize() const  { return Pagesize; }
   point viewsize() const  { return Viewsize; }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */




} // end of tomahawk
ENDWRAP

#endif



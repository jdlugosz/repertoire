// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\autolink.h
// Revision: post-public build 9, shipped on 18-Oct-2006 plus changes
#pragma once


#if _MSC_VER == 1310 //v7.1 (.NET)
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc71.debug{pb9+}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc71{pb9+}.lib")
#endif

#if _MSC_VER == 1400 //v8 (2005)
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc8.debug{pb9+}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc8{pb9+}.lib")
#endif

#else
   #error not configured.
#endif


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\autolink.h
// Revision: public build 5, shipped on 8-April-1999
#pragma once

#if _MSC_VER == 1100  //reported by v5.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc5.debug{pb5}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc5{pb5}.lib")
#endif

#elif _MSC_VER == 1200  //v6.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc6.debug{pb5}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc6{pb5}.lib")
#endif

#else
   #error not configured.
#endif


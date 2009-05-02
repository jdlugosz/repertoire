// The Repertoire Project copyright 2003 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\autolink.h
// Revision: 
#pragma once

#if _MSC_VER == 1100  //reported by v5.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc5.debug{pb6+6}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc5{pb6+6}.lib")
#endif

#elif _MSC_VER == 1200  //v6.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc6.debug{pb6+6}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc6{pb6+6}.lib")
#endif

#elif _MSC_VER == 1300 //v7.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc7.debug{pb6+6}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc7{pb6+6}.lib")
#endif

#elif _MSC_VER == 1310 //v7.1 (.NET)
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc71.debug{pb6+6}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Classics.vc71{pb6+6}.lib")
#endif

#else
   #error not configured.
#endif


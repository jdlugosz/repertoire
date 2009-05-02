// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\autolink.h
// Revision: public build 9, shipped on 18-Oct-2006
#pragma once


#if _MSC_VER == 1100  //reported by v5.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc5.debug{pb9}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc5{pb9}.lib")
#endif


#elif _MSC_VER == 1200  //v6.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc6.debug{pb9}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc6{pb9}.lib")
#endif

#elif _MSC_VER == 1300   //v7.0, ".NET"
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc7.debug{pb9}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc7{pb9}.lib")
#endif

#elif  _MSC_VER == 1310  //v7.1
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc71.debug{pb9}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire RatWin.vc71{pb9}.lib")
#endif

#else
   #error not configured.
#endif



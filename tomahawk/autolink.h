// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\autolink.h
// Revision: public build 8, shipped on 11-July-2006
#pragma once

#if _MSC_VER == 1200  //v6.0
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc6.debug{pb8}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc6{pb8}.lib")
#endif

#elif _MSC_VER == 1300  //v7.0, ".NET"
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc7.debug{pb8}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc7{pb8}.lib")
#endif

#elif _MSC_VER == 1310  //v7.1, ".NET"
#if defined _DEBUG
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc71.debug{pb8}.lib")
#else
   #pragma comment (lib, "Dlugosz Repertoire Tomahawk.vc71{pb8}.lib")
#endif


#else
   #error not configured.
#endif



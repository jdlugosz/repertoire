// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\size_t.h
// Revision: public build 9, shipped on 18-Oct-2006
#pragma once

#if defined _MSC_VER

   #if !defined _SIZE_T_DEFINED

   #if _MSC_VER >= 1310
      #ifdef  _WIN64
      typedef unsigned __int64 size_t;
      #else
      typedef __w64 unsigned int size_t;
      #endif

   #else // compilers prior to VC++ 7.1
      typedef unsigned int size_t;
      #endif

   #define _SIZE_T_DEFINED
   #endif

// ADD MORE CASES HERE.
// #elif ...

#else
#error Include proper definition for size_t here.
#endif


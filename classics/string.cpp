// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string.cpp
// Revision: public build 8, shipped on 11-July-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\string.h"
#include "classics\string.hpp"  //template bodies
#include <cstring>  //strcmp etc.
#include <string>  //std::string interop functions

STARTWRAP
namespace classics {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int len_ (const char* s)  { return s ? strlen(s) : 0; }
inline int len_ (const wchar_t* s)  { return s ? wcslen(s) : 0; }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int compare_ (const char* a, const char* b, int len, bool case_sensitive)
 {
#ifdef _DEBUG
 if (len==0)  return 0;  // strncmp in debug RTL doesn't like zero-length.
#endif
 return (case_sensitive ? strncmp : strnicmp) (a,b,len);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

inline int compare_ (const wchar_t* a, const wchar_t* b, int len, bool case_sensitive)
 {
#ifdef _DEBUG
 if (len==0)  return 0;  // strncmp in debug RTL doesn't like zero-length.
#endif
 return (case_sensitive ? wcsncmp : wcsnicmp) (a,b,len);
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// explicit instantiations
template class generic_string<char>;
template class generic_string<wchar_t>;

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

#if defined (ccfg_SUPPORT_WCHAR_AS_INT)
// be friendly to programs who compiled without /Zc:wchar_t when Classics is compiled with it.

   inline int len_ (const unsigned short* s)  { return s ? wcslen(reinterpret_cast<const wchar_t*>(s)) : 0; }

   inline int compare_ (const unsigned short* a, const unsigned short* b, int len, bool case_sensitive)
    {
    #ifdef _DEBUG
    if (len==0)  return 0;  // strncmp in debug RTL doesn't like zero-length.
    #endif
    return (case_sensitive ? wcsncmp : wcsnicmp) (reinterpret_cast<const wchar_t*>(a),reinterpret_cast<const wchar_t*>(b),len);
    }

   template class generic_string<unsigned short>;  // be friendly to programs who compiled without /Zc:wchar_t
#endif

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end classics
ENDWRAP



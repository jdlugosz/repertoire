// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\string.cpp
// Revision: public build 6, shipped on 28-Nov-1999

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

} // end classics
ENDWRAP



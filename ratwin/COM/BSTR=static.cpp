// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\BSTR=static.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#include "ratwin\COM\BSTR.h"

extern "C" {
   __declspec(dllimport) wchar_t* __stdcall SysAllocString (const wchar_t*);
   __declspec(dllimport) wchar_t* __stdcall SysAllocStringLen (const wchar_t*,int);
   __declspec(dllimport) int __stdcall SysReAllocString (wchar_t**, const wchar_t*);
   __declspec(dllimport) int __stdcall SysReAllocStringLen (wchar_t**, const wchar_t*, int);
   __declspec(dllimport) void __stdcall SysFreeString (wchar_t*);
   __declspec(dllimport) int __stdcall SysStringLen (const wchar_t*);
   }

   
STARTWRAP
namespace ratwin {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

int BSTR::elcount() const
 {
 return ::SysStringLen (p);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void BSTR::alloc (const wchar_t* data)
 {
 free();
 p= ::SysAllocString (data);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void BSTR::alloc (const wchar_t* data, int len)
 {
 free();
 p= ::SysAllocStringLen (data,len);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void BSTR::alloc (int len)
 {
 free();
 p= ::SysAllocStringLen (0,len);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void BSTR::free()
 {
 if (p) {
    ::SysFreeString (p);
    p= 0;
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

void BSTR::realloc (const wchar_t* data, int len)
 {
 ::SysReAllocString (&p, data);
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} //end namespace ratwin
ENDWRAP



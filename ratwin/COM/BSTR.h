// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\BSTR.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
// Note: these are static.  Link with ratwin_static.lib when using these members.

#include "ratwin\COM\HRESULT.h"

STARTWRAP
namespace ratwin {

class BSTR {
   wchar_t* p;
public:
   BSTR() : p(0) {}
   wchar_t* get_data() const { return p; }
   void set (wchar_t* data) { p= data; }
   int elcount() const;  // actual wchar_t elements
   void alloc (const wchar_t*);  //wraps SysAllocString
   void alloc (const wchar_t*, int len);  //wraps SysAllocStringLen
   void alloc (int len);  //wraps SysAllocStringLen, keeps string uninitialized
   void free();  //wraps SysFreeString
   void realloc (const wchar_t*, int len);
   void realloc (int len);
   };

} //end namespace ratwin
ENDWRAP


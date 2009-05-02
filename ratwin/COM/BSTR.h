// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\BSTR.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\HRESULT.h"

STARTWRAP
namespace ratwin {

class BSTR {
   wchar_t* p;
public:
   BSTR() : p(0) {}
   wchar_t* get_data() const { return p; }
   };

} //end namespace ratwin
ENDWRAP


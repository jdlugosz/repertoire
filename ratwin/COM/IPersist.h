// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IPersist.h
// Revision: fresh

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000010c-0000-0000-C000-000000000046"))  __declspec(novtable)
IPersist : public IUnknown {

   virtual HRESULT __stdcall GetClassID (/* [out] */ IID&) = 0;

   };


}
ENDWRAP
   


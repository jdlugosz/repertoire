// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IPersist.h
// Revision: public build 9, shipped on 18-Oct-2006

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
   


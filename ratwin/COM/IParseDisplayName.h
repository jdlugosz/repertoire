// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IParseDisplayName.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000000f-0000-0000-C000-000000000046")) IMoniker;
struct __declspec(uuid("0000000e-0000-0000-C000-000000000046")) IBindCtx;

struct __declspec(uuid("0000011a-0000-0000-C000-000000000046")) __declspec(novtable)
IParseDisplayName : public IUnknown {
   virtual HRESULT __stdcall ParseDisplayName (
      /* [unique][in] */ const IBindCtx* pbc,
      /* [in, string] */ const wchar_t* pszDisplayName,
      /* [out] */ ulong* pchEaten,
      /* [out] */ IMoniker** ppmkOut) = 0;

   };

}
ENDWRAP



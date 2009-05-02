// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IPersistStream.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IPersist.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000109-0000-0000-C000-000000000046"))  __declspec(novtable)
IPersistStream : public IPersist {

   virtual HRESULT __stdcall IsDirty() = 0;
   
   virtual HRESULT __stdcall Load (/* [unique][in] */ IStream* pStm) = 0;
   
   virtual HRESULT __stdcall Save (
      /* [unique][in] */ IStream* pStm,
      /* [in] */ int/*bool*/ fClearDirty) = 0;
   
   virtual HRESULT __stdcall GetSizeMax (/* [out] */ unsigned __int64&) = 0;
   };


}
ENDWRAP
   


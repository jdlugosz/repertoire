// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\ISequentialStream.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0c733a30-2a1c-11ce-ade5-00aa0044773d")) __declspec(novtable)
ISequentialStream : public IUnknown {

   virtual /* [local] */ HRESULT __stdcall Read (
      /* [length_is][size_is][out] */ void* pv,
      /* [in] */ ulong cb,
      /* [out] */ ulong* pcbRead=0) = 0;
        
   virtual /* [local] */ HRESULT __stdcall Write (
      /* [size_is][in] */ const void* pv,
      /* [in] */ ulong cb,
      /* [out] */ ulong* pcbWritten=0) = 0;

   template <typename U>
   inline HRESULT read_bits (U& x)
      { return Read (&x, sizeof(U)); }

   template <typename U>
   inline HRESULT write_bits (const U& x)
      { return Write (&x, sizeof(U)); }

   };  //end of ISequentialStream

} // end of namespace
ENDWRAP


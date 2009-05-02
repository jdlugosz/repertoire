// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IGlobalInterfaceTable.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000323-0000-0000-c000-000000000046")) StdGlobalInterfaceTable;


struct __declspec(uuid("00000146-0000-0000-C000-000000000046")) __declspec(novtable)
IGlobalInterfaceTable : public IUnknown {
   virtual HRESULT __stdcall RegisterInterfaceInGlobal (
      /* [in] */ IUnknown *pUnk,
      /* [in] */ const IID& riid,
      /* [out] */ ulong *pdwCookie) = 0;
        
   template <class Q>
      HRESULT RegisterInterfaceInGlobal (Q* pp, ulong* cookie)
       {
       return RegisterInterfaceInGlobal (pp, __uuidof(Q), cookie);
       }
   
   virtual HRESULT __stdcall RevokeInterfaceFromGlobal (
      /* [in] */ ulong dwCookie) = 0;
        
   virtual HRESULT __stdcall GetInterfaceFromGlobal (
      /* [in] */ ulong dwCookie,
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void** ppv) = 0;
   template <class Q>
      HRESULT GetInterfaceFromGlobal (ulong cookie, Q** pp)
       {
       return GetInterfaceFromGlobal (cookie, __uuidof(Q), (void**)pp);
       }
   };


} // end of namespace
ENDWRAP



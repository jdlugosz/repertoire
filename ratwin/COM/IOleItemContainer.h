// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IOleItemContainer.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IOleContainer.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000011c-0000-0000-C000-000000000046")) __declspec(novtable)
IOleItemContainer : public IOleContainer {
   enum BINDSPEED {
      BINDSPEED_INDEFINITE= 1, BINDSPEED_MODERATE, BINDSPEED_IMMEDIATE };

   virtual HRESULT __stdcall GetObject (
      /* [in, string] */ const wchar_t* pszItem,
      /* [in] */ BINDSPEED dwSpeedNeeded,
      /* [unique][in] */ IBindCtx* pbc,
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void** ppvObject) = 0;
    template <typename Q>
       HRESULT GetObject (const wchar_t* pszItem, BINDSPEED dwSpeedNeeded, const IBindCtx* pbc, Q**pp)
        {
        return GetObject (pszItem, dwSpeedNeeded, pbc, __uuidof(Q), (void**)pp);
        }

   virtual HRESULT __stdcall GetObjectStorage (
      /* [in, string] */ const wchar_t* pszItem,
      /* [unique][in] */ const IBindCtx *pbc,
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void **ppvStorage) = 0;
   template <typename Q>
      HRESULT GetObjectStorage (const wchar_t* pszItem, const IBindCtx *pbc, Q** pp)
       {
       return GetObjectStorage (pszItem, pbc, __uuidof(Q), (void**)pp);
       }

   virtual HRESULT __stdcall IsRunning (
      /* [in, string] */ const wchar_t* pszItem) = 0;

   };

}
ENDWRAP


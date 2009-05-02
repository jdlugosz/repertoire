// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\OleItemContainer_impl.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"
#include "ratwin\COM\IOleItemContainer.h"

STARTWRAP
namespace classics {
namespace COM {

class __declspec(novtable)
OleItemContainer_impl : public ratwin::IOleItemContainer {
protected:
   bool pseudo_always_runs;
   OleItemContainer_impl (bool pseudo_always_runs) : pseudo_always_runs(pseudo_always_runs) {}
   CLASSICS_EXPORT bool QI_contributer (const ratwin::IID& iid, void** ppv);
public:
#if 0
   ratwin::HRESULT __stdcall GetObject (
      /* [in, string] */ const wchar_t* pszItem,
      /* [in] */ BINDSPEED dwSpeedNeeded,
      /* [unique][in] */ const ratwin::IBindCtx* pbc,
      /* [in] */ const ratwin::IID& riid,
      /* [iid_is][out] */ void** ppvObject);
#endif

   CLASSICS_EXPORT ratwin::HRESULT __stdcall GetObjectStorage (
      /* [in, string] */ const wchar_t* pszItem,
      /* [unique][in] */ const ratwin::IBindCtx *pbc,
      /* [in] */ const ratwin::IID& riid,
      /* [iid_is][out] */ void **ppvStorage);

   CLASSICS_EXPORT ratwin::HRESULT __stdcall IsRunning (/* [in, string] */ const wchar_t* pszItem);

   CLASSICS_EXPORT ratwin::HRESULT __stdcall EnumObjects (
      /* [in] */ unsigned long/*OLECONTF*/ grfFlags,
      /* [out] */ ratwin::IEnumUnknown** ppenum);

   CLASSICS_EXPORT ratwin::HRESULT __stdcall LockContainer (/* [in] */ int/*bool*/ fLock);

   CLASSICS_EXPORT ratwin::HRESULT __stdcall ParseDisplayName (
         /* [unique][in] */ const ratwin::IBindCtx* pbc,
         /* [in, string] */ const wchar_t* pszDisplayName,
         /* [out] */ unsigned long* pchEaten,
         /* [out] */ ratwin::IMoniker** ppmkOut);

   };
   
}}
ENDWRAP



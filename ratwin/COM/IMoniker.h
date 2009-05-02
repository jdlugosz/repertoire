// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IMoniker.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "ratwin\COM\IPersistStream.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000000e-0000-0000-C000-000000000046")) IBindCtx;
struct __declspec(uuid("00000102-0000-0000-C000-000000000046")) IEnumMoniker;

struct __declspec(uuid("0000000f-0000-0000-C000-000000000046"))  __declspec(novtable)
IMoniker : public IPersistStream {

   virtual /* [local] */ HRESULT __stdcall BindToObject (
      /* [unique][in] */ const IBindCtx*,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [in] */ const IID& riidResult,
      /* [iid_is][out] */ void** ppvResult) = 0;
   
   virtual /* [local] */ HRESULT __stdcall BindToStorage (
      /* [unique][in] */ const IBindCtx*,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void** ppvObj) = 0;
   
   virtual HRESULT __stdcall Reduce (
      /* [unique][in] */ const IBindCtx* pbc,
      /* [in] */ ulong dwReduceHowFar,
      /* [unique][out][in] */ IMoniker** ppmkToLeft,
      /* [out] */ IMoniker** ppmkReduced) = 0;
   
   virtual HRESULT __stdcall ComposeWith (
      /* [unique][in] */ IMoniker* pmkRight,
      /* [in] */ int /*bool*/ fOnlyIfNotGeneric,
      /* [out] */ IMoniker** ppmkComposite) = 0;
   
   virtual HRESULT __stdcall Enum (
      /* [in] */ int/*bool*/ fForward,
      /* [out] */ IEnumMoniker** ppenumMoniker) = 0;
   
   virtual HRESULT __stdcall IsEqual (
      /* [unique][in] */ IMoniker* pmkOtherMoniker) = 0;
   
   virtual HRESULT __stdcall Hash (
      /* [out] */ ulong* pdwHash) = 0;
   
   virtual HRESULT __stdcall IsRunning (
      /* [unique][in] */ const IBindCtx* pbc,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [unique][in] */ IMoniker* pmkNewlyRunning) = 0;
   
   virtual HRESULT __stdcall GetTimeOfLastChange (
      /* [unique][in] */ const IBindCtx* pbc,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [out] */ __int64& pFileTime) = 0;
   
   virtual HRESULT __stdcall Inverse (
      /* [out] */ IMoniker** ppmk) = 0;
   
   virtual HRESULT __stdcall CommonPrefixWith (
      /* [unique][in] */ IMoniker* pmkOther,
      /* [out] */ IMoniker** ppmkPrefix) = 0;
   
   virtual HRESULT __stdcall RelativePathTo (
      /* [unique][in] */ IMoniker* pmkOther,
      /* [out] */ IMoniker** ppmkRelPath) = 0;
   
   virtual HRESULT __stdcall GetDisplayName (
      /* [unique][in] */ const IBindCtx*,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [out,string] */ wchar_t** ppszDisplayName) = 0;
   
   virtual HRESULT __stdcall ParseDisplayName (
      /* [unique][in] */ const IBindCtx*,
      /* [unique][in] */ IMoniker* pmkToLeft,
      /* [in,string] */ const wchar_t* pszDisplayName,
      /* [out] */ ulong& pchEaten,
      /* [out] */ IMoniker** ppmkOut) = 0;

   virtual HRESULT __stdcall IsSystemMoniker (/* [out] */ ulong* pdwMksys) = 0;
   };


}
ENDWRAP
   



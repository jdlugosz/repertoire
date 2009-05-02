// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IBindCtx.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000101-0000-0000-C000-000000000046")) IEnumString;
struct __declspec(uuid("00000010-0000-0000-C000-000000000046")) IRunningObjectTable;
struct BIND_OPTS;  // found in ratwin\COM\moniker.h, should move.  Also supply BIND_OPTS2, as derived struct.

struct __declspec(uuid("0000000e-0000-0000-C000-000000000046")) __declspec(novtable)
IBindCtx : public IUnknown {

   virtual HRESULT __stdcall  RegisterObjectBound (
      /* [unique][in] */ IUnknown*) = 0;
   
   virtual HRESULT __stdcall RevokeObjectBound (
      /* [unique][in] */ IUnknown*) = 0;
   
   virtual HRESULT __stdcall ReleaseBoundObjects() = 0;
   
   virtual /* [local] */ HRESULT __stdcall SetBindOptions (
      /* [in] */ const BIND_OPTS&) = 0;
   
   virtual /* [local] */ HRESULT __stdcall GetBindOptions (
      /* [out][in] */ BIND_OPTS&) = 0;
   
   virtual HRESULT __stdcall GetRunningObjectTable (
      /* [out] */ IRunningObjectTable**) = 0;
   
   virtual HRESULT __stdcall RegisterObjectParam (
      /* [in,string] */ const wchar_t* pszKey,
      /* [unique][in] */ IUnknown*) = 0;
   
   virtual HRESULT __stdcall GetObjectParam (
      /* [in,string] */ const wchar_t* pszKey,
      /* [out] */ IUnknown**) = 0;
   
   virtual HRESULT __stdcall EnumObjectParam (
      /* [out] */ IEnumString**) = 0;
   
   virtual HRESULT __stdcall RevokeObjectParam (
      /* [in,string] */ const wchar_t*) = 0;

   };

}
ENDWRAP


// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IDispatch.h
// Revision: post- build 9,

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("00020401-0000-0000-C000-000000000046")) ITypeInfo;
struct VARIANT;
struct EXCEPINFO;
typedef long DISPID;

struct DISPPARAMS  {
   VARIANT* rgvarg;
   DISPID* rgdispidNamedArgs;
   unsigned cArgs;
   unsigned cNamedArgs;
   };


struct __declspec(uuid("00020400-0000-0000-C000-000000000046"))  __declspec(novtable)
IDispatch : public IUnknown {

   virtual HRESULT __stdcall GetTypeInfoCount (
      /* [out] */ unsigned* pctinfo) =0;

   virtual HRESULT __stdcall GetTypeInfo (
      /* [in] */ unsigned iTInfo,
      /* [in] */ types::LCID lcid,
      /* [out] */ ITypeInfo** ppTInfo) =0;

   virtual HRESULT __stdcall GetIDsOfNames (
      /* [in] */ IID riid,   // unused, must be NULL
      /* [in] */ wchar_t** rgszNames,
      /* [in] */ unsigned cNames,
      /* [in] */ types::LCID lcid,
      /* [out] */ DISPID* rgDispId) =0;

   virtual /* [local] */ HRESULT __stdcall Invoke (
      /* [in] */ DISPID dispIdMember,
      /* [in] */ IID riid,
      /* [in] */ types::LCID lcid,
      /* [in] */ ushort wFlags,
      /* [out][in] */ DISPPARAMS* pDispParams,
      /* [out] */ VARIANT* pVarResult,
      /* [out] */ EXCEPINFO* pExcepInfo,
      /* [out] */ unsigned* puArgErr) =0;

   };


const DISPID DISPID_UNKNOWN= -1;  // only reserved for data members (properties); reused as a method dispid below
const DISPID DISPID_VALUE= 0;  // The "value" property
const DISPID DISPID_PROPERTYPUT= -3;  // parameter on right-hand-side of a Property Put
const DISPID DISPID_NEWENUM= -4;  // The standard NewEnum method
const DISPID DISPID_EVALUATE= -5;  // The standard Evaluate method
const DISPID DISPID_CONSTRUCTOR= -6;  // C++ constructor
const DISPID DISPID_DESTRUCTOR= -7;  // C++ destructor
const DISPID DISPID_COLLECT= -8;

}
ENDWRAP


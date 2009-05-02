// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\RunningObjectTable.h
// Revision: fresh

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000000f-0000-0000-C000-000000000046")) IMoniker;
struct __declspec(uuid("00000102-0000-0000-C000-000000000046")) IEnumMoniker;

struct __declspec(uuid("00000010-0000-0000-C000-000000000046")) __declspec(novtable)
IRunningObjectTable : public IUnknown {
   
   virtual HRESULT __stdcall Register (
      /* [in] */ ulong grfFlags,
      /* [unique][in] */ IUnknown* punkObject,
      /* [unique][in] */ IMoniker* pmkObjectName,
      /* [out] */ ulong& pdwRegister) = 0;

   virtual HRESULT __stdcall Revoke (
      /* [in] */ ulong dwRegister) = 0;

   virtual HRESULT __stdcall IsRunning (
      /* [unique][in] */ IMoniker* pmkObjectName) = 0;

   virtual HRESULT __stdcall GetObject (
      /* [unique][in] */ IMoniker* pmkObjectName,
      /* [out] */ IUnknown** ppunkObject) = 0;

   virtual HRESULT __stdcall NoteChangeTime (
      /* [in] */ ulong dwRegister,
      /* [in] */ const __int64& pfiletime) = 0;

    virtual HRESULT __stdcall GetTimeOfLastChange (
      /* [unique][in] */ IMoniker* pmkObjectName,
      /* [out] */ __int64& pfiletime) = 0;

    virtual HRESULT __stdcall EnumRunning (
      /* [out] */ IEnumMoniker** ppenumMoniker) = 0;

   };

}
ENDWRAP
   


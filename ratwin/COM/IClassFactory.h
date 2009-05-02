// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IClassFactory.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\IUnknown.h"
//#include "classics\flagword.h"

STARTWRAP
namespace ratwin {

//forward declare needed Interfaces and other types

// types used within the Interface

struct __declspec(uuid("00000001-0000-0000-C000-000000000046")) __declspec(novtable)
IClassFactory : public IUnknown {
   virtual /* [local] */ HRESULT __stdcall CreateInstance (
      /* [unique][in] */ IUnknown* pUnkOuter,
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void** ppvObject) = 0;
        
   virtual /* [local] */ HRESULT __stdcall LockServer (
      /* [in] */ int/*really bool*/ fLock) = 0;
        
    };

} //end namespace ratwin
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IClassFactory.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IUnknown.h"
#include "classics\auto_COM_ptr.h"  // had removed this, but put it back.
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
        
   // simplified form - smart ptr, and "outer" is optional
   // if I re-discover why this "simplified" form had been removed, deal with it.
   template <typename Q>
      inline HRESULT CreateInstance (classics::auto_COM_ptr<Q>& result, IUnknown* outer=0)
       {
       return CreateInstance (outer, __uuidof(Q), result);
       }
   
   virtual /* [local] */ HRESULT __stdcall LockServer (
      /* [in] */ int/*really bool*/ fLock) = 0;
        
    };

} //end namespace ratwin
ENDWRAP


// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\COM\factory.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\IClassFactory.h"
#include "classics\atomic_counter.h"

STARTWRAP
namespace classics {
namespace COM {

class factory_ntbase : public ratwin::IClassFactory {
    classics::atomic_counter<long> refcount;
public:
   factory_ntbase() : refcount(1) {}
   virtual ~factory_ntbase() {}
   CLASSICS_EXPORT ratwin::HRESULT __stdcall QueryInterface (const ratwin::IID& iid, void** ppv);
   ulong __stdcall AddRef() { return ++refcount; }
   CLASSICS_EXPORT ulong __stdcall Release();
   CLASSICS_EXPORT ratwin::HRESULT __stdcall LockServer (int bLock);
   };

template <typename T>  // Factory of what?
class factory : public factory_ntbase {
public:
   ratwin::HRESULT __stdcall CreateInstance (ratwin::IUnknown* pUnknownOuter, const ratwin::IID& iid, void** ppv);
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
ratwin::HRESULT __stdcall factory<T>::CreateInstance (ratwin::IUnknown* pUnknownOuter, const ratwin::IID& iid, void** ppv) 
 {
 if (pUnknownOuter)  return ratwin::CLASS_E_NOAGGREGATION;  //Cannot aggregate (for now)
 T* pA= new T;
 ratwin::HRESULT hr= pA->QueryInterface(iid, ppv);
 pA->Release();
 return hr;
 }

}  //end of COM namespace
}  //end of classics namespace
ENDWRAP


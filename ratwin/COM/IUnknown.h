// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IUnknown.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "ratwin\COM\HRESULT.h"
#include "ratwin\COM\GUID.h"
#include "classics\auto_COM_ptr.h"  // I had removed this, but the VC6 isn't doing an implicit cast.


STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000000-0000-0000-c000-000000000046")) __declspec(novtable)
IUnknown {
   virtual HRESULT __stdcall QueryInterface ( 
      /* [in] */ const IID& riid,
      /* [iid_is][out] */ void** ppvObject) = 0;
        
   virtual ulong __stdcall AddRef() = 0;
        
   virtual ulong __stdcall Release() = 0;

//#if (_MSC_VER >= 1200)  // VC6 or greater
   template <class Q>
      inline HRESULT QueryInterface (Q** pp)
       {
       return QueryInterface(__uuidof(Q), (void**)pp);
       }
   // This second one should not be necessary, but VC6 is not doing an implicit conversion.
   // perhaps it's ambiguous (T** or void**) but it's not giving that error.  Instead, it doesn't
   // see the QueryInterface template at all!
   template <class Q>
      inline HRESULT QueryInterface (classics::auto_COM_ptr<Q>& result)
       {
       return QueryInterface(__uuidof(Q), result);
       }
//#endif
protected:
   inline ~IUnknown() {}  //prevent user from calling delete on an interface pointer.
   };

} // end of namespace
ENDWRAP



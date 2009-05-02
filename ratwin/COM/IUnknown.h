// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IUnknown.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\HRESULT.h"
#include "ratwin\COM\GUID.h"


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
      HRESULT __stdcall QueryInterface (Q** pp)
       {
       return QueryInterface(__uuidof(Q), (void**)pp);
       }
//#endif
protected:
   inline ~IUnknown() {}  //prevent user from calling delete on an interface pointer.
   };

} // end of namespace
ENDWRAP



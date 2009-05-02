// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IEnumSTATSTG.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once

#include "ratwin\COM\IUnknown.h"

STARTWRAP
namespace ratwin {

struct STATSTG {
   wchar_t* pwcsName;
   ulong type;
   __int64 cbSize;
   __int64 mtime;
   __int64 ctime;
   __int64 atime;
   ulong grfMode;
   ulong grfLocksSupported;
   CLSID clsid;
   ulong grfStateBits;
   ulong reserved;
   };


struct __declspec(uuid("0000000d-0000-0000-C000-000000000046")) __declspec(novtable)
IEnumSTATSTG : public IUnknown {
   virtual /* [local] */ HRESULT __stdcall Next ( 
      /* [in] */ ulong celt,
      /* [length_is][size_is][out] */ STATSTG* rgelt,
      /* [out] */ ulong* pceltFetched) = 0;
        
   virtual HRESULT __stdcall Skip ( 
      /* [in] */ ulong celt) = 0;
        
   virtual HRESULT __stdcall Reset () = 0;
        
   virtual HRESULT __stdcall Clone ( 
      /* [out] */ IEnumSTATSTG** ppenum) = 0;
        
    };

} // end of namespace
ENDWRAP


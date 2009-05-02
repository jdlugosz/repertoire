// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\IOleContainer.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "ratwin\COM\IParseDisplayName.h"

STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000100-0000-0000-C000-000000000046")) IEnumUnknown;

struct __declspec(uuid("0000011b-0000-0000-C000-000000000046")) __declspec(novtable)
IOleContainer : public IParseDisplayName {
   enum OLECONTF  {
      OLECONTF_EMBEDDINGS= 1,
       OLECONTF_LINKS= 2,
       OLECONTF_OTHERS= 4,
       OLECONTF_ONLYUSER= 8,
       OLECONTF_ONLYIFRUNNING= 16
       } ;
   virtual HRESULT __stdcall EnumObjects (
      /* [in] */ ulong/*OLECONTF*/ grfFlags,
      /* [out] */ IEnumUnknown** ppenum) = 0;

   virtual HRESULT __stdcall LockContainer (
      /* [in] */ int/*bool*/ fLock) = 0;

   };

}
ENDWRAP



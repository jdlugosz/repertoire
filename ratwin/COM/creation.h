// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\creation.h
// Revision: 

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\creation.h contains globals.
#endif


#include "ratwin\COM\HRESULT.h"
#include "classics\flagword.h"
#include "ratwin\COM\GUID.h"

extern "C" {
__declspec(dllimport) long __stdcall CoCreateInstance (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {

struct __declspec(uuid("00000000-0000-0000-c000-000000000046")) __declspec(novtable)
IUnknown;  //external declaration

enum CLSCTX {
   CLSCTX_INPROC_SERVER= 0x1,
   CLSCTX_INPROC_HANDLER= 0x2,
   CLSCTX_LOCAL_SERVER= 0x4,
   CLSCTX_INPROC_SERVER16= 0x8,
   CLSCTX_REMOTE_SERVER= 0x10,
   CLSCTX_INPROC_HANDLER16= 0x20,
   CLSCTX_INPROC_SERVERX86= 0x40,
   CLSCTX_INPROC_HANDLERX86= 0x80,
   CLSCTX_ESERVER_HANDLER= 0x100
   };


inline
HRESULT CoCreateInstance (const CLSID& classID, IUnknown* aggregate, classics::flagword<CLSCTX> context, const IID& interface, void** result)
 {
 return HRESULT( ::CoCreateInstance (
    reinterpret_cast<arg::carg32>(&classID),
    reinterpret_cast<arg::arg32>(aggregate),
    reinterpret_cast<arg::arg32>(context.validdata()),
    reinterpret_cast<arg::carg32>(&interface),
    reinterpret_cast<arg::arg32>(result)
    ) );
 }

// simplified form
template <typename T>
inline
HRESULT CoCreateInstance (const CLSID& classID, classics::flagword<CLSCTX> context, T** result)
 {
 return CoCreateInstance (classID, 0, context, __uuidof(T), reinterpret_cast<void**>(result));
 }
 

}
ENDWRAP



// The Repertoire Project copyright 2002 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\creation.h
// Revision: updated

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\COM\moniker.h contains globals.
#endif

#include "classics\auto_COM_ptr.h"
#include "ratwin\COM\HRESULT.h"
#include "ratwin\COM\GUID.h"

extern "C" {
__declspec(dllimport) long __stdcall CoGetObject (const wchar_t*, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall CreateItemMoniker (const wchar_t* lpszDelim, const wchar_t* lpszItem, Dlugosz::ratwin::arg::arg32 ppmk);
__declspec(dllimport) long __stdcall CreateClassMoniker (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall  MkParseDisplayName (Dlugosz::ratwin::arg::arg32, const wchar_t*, unsigned long*, void*);
__declspec(dllimport) long __stdcall GetRunningObjectTable (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32);
}

STARTWRAP
namespace ratwin {

struct BIND_OPTS {
   ulong cbStruct;
   ulong Flags;
   ulong Mode;
   ulong TickCountDeadline;
   };

struct __declspec(uuid("0000000f-0000-0000-C000-000000000046")) IMoniker;
struct __declspec(uuid("0000000e-0000-0000-C000-000000000046")) IBindCtx;
struct __declspec(uuid("00000010-0000-0000-C000-000000000046")) IRunningObjectTable;

inline
HRESULT CoGetObject (const wchar_t* moniker_displayname, BIND_OPTS* options, const IID& interface, void** result)
 {
 return HRESULT(::CoGetObject (
    moniker_displayname,
    reinterpret_cast<arg::carg32>(options),
    reinterpret_cast<arg::carg32>(&interface),
    reinterpret_cast<arg::arg32>(result)
    ) );
 }

// simplified form - gets matching UUID and makes options optional.
template <typename T>
inline
HRESULT CoGetObject (const wchar_t* moniker_displayname, classics::auto_COM_ptr<T>& result, BIND_OPTS* options= 0)
 {
 return CoGetObject (moniker_displayname, options, __uuidof(T), result);
 }


inline
HRESULT CreateItemMoniker (const wchar_t* delimiter, const wchar_t* item_name, IMoniker** ppmk)
 {
 return HRESULT(::CreateItemMoniker( delimiter, item_name, reinterpret_cast<arg::arg32>(ppmk)));
 }


inline
HRESULT CreateClassMoniker (const IID& riid, IMoniker** ppmk)
 {
 return HRESULT (::CreateClassMoniker (reinterpret_cast<arg::carg32>(&riid), reinterpret_cast<arg::arg32>(ppmk)));
 }

template <typename T>
HRESULT CreateClassMoniker (IMoniker**ppmk)
 {
 return CreateClassMoniker (__uuidof(T), ppmk);
 }
 
inline
HRESULT MkParseDisplayName (IBindCtx* pbc, const wchar_t* name, ulong* eaten, IMoniker** ppmk)
 {
 return HRESULT (::MkParseDisplayName (reinterpret_cast<arg::arg32>(pbc), name, eaten, ppmk));
 }

inline
HRESULT GetRunningObjectTable (IRunningObjectTable** out)
 {
 return HRESULT( ::GetRunningObjectTable (reinterpret_cast<arg::carg32>(0), reinterpret_cast<arg::arg32>(out)) );
 }
 
}
ENDWRAP



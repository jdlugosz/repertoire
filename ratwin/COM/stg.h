// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\stg.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#include "ratwin\COM\stg=struct.h"
#include "ratwin\COM\HRESULT.h"

extern "C" {
__declspec(dllimport) long __stdcall StgCreateDocfile (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, int reserved, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) long __stdcall StgOpenStorage (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32,  Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);

} // end of cloaked globals

////////

STARTWRAP
namespace ratwin {

struct __declspec(uuid("0000000b-0000-0000-C000-000000000046")) IStorage;
//struct __declspec(uuid("0000000c-0000-0000-C000-000000000046")) IStream;

////////


inline
HRESULT StgCreateDocfile (const wchar_t* name, classics::flagword<STGM> stgm, IStorage** result)
 {
 return HRESULT (::StgCreateDocfile (reinterpret_cast<arg::carg32>(name), reinterpret_cast<arg::arg32>(stgm.validdata()), 0, reinterpret_cast<arg::arg32>(result)) );
 }

inline
HRESULT StgOpenStorage (const wchar_t* name, classics::flagword<STGM> stgm, IStorage** result)
 {
 return HRESULT( ::StgOpenStorage (
    reinterpret_cast<arg::carg32>(name), //root file name
    reinterpret_cast<arg::arg32>(0), // previous "priority" opened IStorage
    reinterpret_cast<arg::arg32>(stgm.validdata()),
    reinterpret_cast<arg::arg32>(0), // SNB, omitted from this simplified signature
    reinterpret_cast<arg::arg32>(0), // reserved, must be zero
    reinterpret_cast<arg::arg32>(result))
    );
 }


} // end of namespace
ENDWRAP


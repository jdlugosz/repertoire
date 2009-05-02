// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\TLS.h
// Revision: public build 5, shipped on 8-April-1999

#pragma once

#include "ratwin\tasking\basic.h"

// DLL imports "cloaked" for overloading
extern "C" {

__declspec(dllimport) unsigned long __stdcall TlsAlloc();  //note: not cloaked
__declspec(dllimport) void* __stdcall TlsGetValue (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall TlsSetValue (Dlugosz::ratwin::arg::arg32,Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) unsigned long __stdcall TlsFree (Dlugosz::ratwin::arg::arg32);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {
namespace tasking {

inline
types::TLS_key TlsAlloc()
 {
 return reinterpret_cast<types::TLS_key>( ::TlsAlloc() );
 }

template<typename T>
inline
T TlsGetValue (types::TLS_key k)
 {
 return reinterpret_cast<T>( ::TlsGetValue (reinterpret_cast<arg::arg32>(k)) );
 }

template<typename T>
inline
bool TlsSetValue (types::TLS_key k, T value)
 {
 return ::TlsSetValue (reinterpret_cast<arg::arg32>(k), reinterpret_cast<arg::arg32>(value));
 }

inline
bool TlsFree (types::TLS_key k)
 {
 return ::TlsFree (reinterpret_cast<arg::arg32>(k));
 }
 
}}
ENDWRAP


// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\housekeeping.h
// Revision:

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\COM\housekeeping.h contains globals.
#endif


#include "ratwin\COM\HRESULT.h"
#include "classics\flagword.h"
#include "ratwin\COM\GUID.h"
#include "ratwin\COM\IUnknown.h"

extern "C" {
__declspec(dllimport) long __stdcall CoInitializeEx (void*, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall CoUninitialize();
__declspec(dllimport) long __stdcall CoRegisterClassObject (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::arg32, unsigned long dwClsContext, unsigned long flags, unsigned long* lpdwRegister);
__declspec(dllimport) long __stdcall CoRevokeClassObject (Dlugosz::ratwin::arg::arg32);
}


STARTWRAP
namespace ratwin {


enum COINIT {
   COINIT_APARTMENTTHREADED  = 0x2,      // Apartment model
   COINIT_MULTITHREADED      = 0x0,      // OLE calls objects on any thread.
   COINIT_DISABLE_OLE1DDE    = 0x4,      // Don't use DDE for Ole1 support.
   COINIT_SPEED_OVER_MEMORY  = 0x8,      // Trade memory for speed.
   };

inline
HRESULT
CoInitialize (classics::flagword<COINIT> flags)
 {
 /* notes:  The Win32 docs say that the default is Apartment, but the code shows
   the default to be multithreaded.  The old (non -EX) form is also documented
   to be Apartment.  So to avoid confusion (should leaving off the parameter be
   apartment or free-thread?) I didn't use a default argument here as originally planned.
   It is best if you are specific about which you want. */
 return HRESULT( ::CoInitializeEx (0/*reserved*/, reinterpret_cast<arg::arg32>(flags.validdata())) );
 }

inline
void CoUninitialize()
 {
 ::CoUninitialize();
 }

inline
HRESULT
CoRegisterClassObject (const CLSID& clsid, IUnknown* pUnk, unsigned long& result)
 {
 return HRESULT( ::CoRegisterClassObject (reinterpret_cast<arg::carg32>(&clsid), reinterpret_cast<arg::arg32>(pUnk), 4, 1, &result) );
 }

inline
HRESULT
CoRevokeClassObject (unsigned long cookie)
 {
 return HRESULT( ::CoRevokeClassObject (reinterpret_cast<arg::arg32>(cookie)) );
 }
 
}
ENDWRAP


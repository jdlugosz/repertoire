// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\basic.h
// Revision: public build 6, shipped on 28-Nov-1999
#error obsolete file.

// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\basic.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "ratwin\base.h"
#include "classics\flagword.h"

extern "C" {
__declspec(dllimport) long __stdcall CoInitializeEx (void*, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) void __stdcall CoUninitialize();
}

// GLOBAL because the compiler has built-in awareness.
// specifically, the intrinsic __guid operator returns a ::_GUID value.
#ifndef GUID_DEFINED
#define GUID_DEFINED
struct _GUID {
    unsigned __int32      time_low;
    unsigned __int16      time_mid;
    unsigned __int16      time_hi : 12;  //low bits
    unsigned __int16      version : 4;  //high bits
    unsigned __int8       clock_seq_hi : 6;  //low bits
    unsigned __int8       reserved : 2; // 2 or 3, depending
    unsigned __int8       clock_seq_low;
    unsigned __int8       node[6];
   };
#endif /* GUID_DEFINED */

STARTWRAP
namespace ratwin {

typedef _GUID GUID;
typedef GUID IID;
typedef GUID CLSID;

namespace internal {

   struct hr_xxx {
      unsigned information_code : 16;
      unsigned facility_code : 13;
      unsigned reserved : 2;
      unsigned severity_code : 1;
      };


   struct HRESULT_struct {
      // no data.  This is not at all a normal class!!!
   private:
      inline static hr_xxx* xxx (HRESULT_struct* const & self)  { return (hr_xxx*)(&self); }
   public:
      unsigned get_i()  { return xxx(this)->information_code; }
      unsigned get_f()  { return xxx(this)->facility_code; }
      unsigned get_r()  { return xxx(this)->reserved; }
      unsigned get_s()  { return xxx(this)->severity_code; }
      __declspec( property(get=get_i) ) unsigned information_code;
      __declspec( property(get=get_f) ) unsigned facility_code;
      __declspec( property(get=get_r) ) unsigned reserved;
      __declspec( property(get=get_s) ) unsigned severity_code;
      unsigned as_number()  { return reinterpret_cast<unsigned>(this); }
      bool failed() { return reinterpret_cast<unsigned>(this) & 0x80000000; }
      bool success() { return !failed(); }
      };
}

typedef internal::HRESULT_struct* HRESULT;


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

}
ENDWRAP


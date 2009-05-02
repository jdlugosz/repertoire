// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\COM\HRESULT.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "ratwin\base.h"

STARTWRAP
namespace ratwin {

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

} // end namespace internal

typedef internal::HRESULT_struct* HRESULT;

inline
HRESULT mk_HRESULT (int s, int f, int i)
 {
 union {
    internal::hr_xxx record; 
    HRESULT hr;
    } x = {i,f,0,s};  
 return x.hr;
 }

} //end namespace ratwin
ENDWRAP


// The Repertoire Project copyright 2007 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File:
// Revision: post-public build 9

#pragma once
#if !defined TOMAHAWK_EXPORT
#define TOMAHAWK_EXPORT __declspec(dllimport)
#endif

#include "ratwin\window=struct.h"
#include "classics\pointers.h"
#include "classics\exception.h"

STARTWRAP
namespace tomahawk {

class HWND_vpapa : public classics::can_handle {
protected:
   ratwin::types::HWND WindowHandle;
   classics::handle <HWND_vpapa> WindowOwnsMe;  // on behalf of the (valid) WindowHandle
   // disable copying
   HWND_vpapa (const HWND_vpapa&);  // never defined
   void operator= (const HWND_vpapa&); // never defined
public:
   TOMAHAWK_EXPORT HWND_vpapa();
   virtual ~HWND_vpapa() {}
   ratwin::types::HWND window_handle() const { return WindowHandle; }
   TOMAHAWK_EXPORT virtual void report_error (const classics::exception&);
   };


}
ENDWRAP


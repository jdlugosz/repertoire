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
#include "classics\nocopy.h"
#include "ratwin\message=struct.h"

STARTWRAP
namespace tomahawk {

class HWND_vpapa : public virtual classics::can_handle, private classics::nocopy {
   classics::handle <HWND_vpapa> WindowOwnsMe;  // on behalf of the (valid) WindowHandle
protected:
   ratwin::types::HWND WindowHandle;
   // disable copying
//   HWND_vpapa (const HWND_vpapa&);  // never defined
//   void operator= (const HWND_vpapa&); // never defined
   void forge_reference() { WindowOwnsMe= this; }
   void release_forged_reference() { WindowOwnsMe= 0; }
public:
   TOMAHAWK_EXPORT HWND_vpapa();
   virtual ~HWND_vpapa() {}
   ratwin::types::HWND window_handle() const { return WindowHandle; }
   virtual long handle_message (ratwin::message::sMSG& msg) =0;
   TOMAHAWK_EXPORT virtual void report_error (const classics::exception&);
   };


}
ENDWRAP


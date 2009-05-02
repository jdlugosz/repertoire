// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\base.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "classics\common.h"
#include "classics\2D_point.h"

#if !defined RATWIN_EXPORT
#define RATWIN_EXPORT __declspec(dllimport)
#endif


namespace Dlugosz {
namespace ratwin {

namespace arg {
   struct arg32_struct {/*empty*/};
   typedef arg32_struct* arg32;
   typedef const arg32_struct* carg32;
   }

}}


STARTWRAP
namespace ratwin {

using classics::ulong;
using classics::ushort;
using classics::byte;

#if !defined DOUBLE_BAGGED
// using namespace Dlugosz;
 namespace arg {
  using namespace Dlugosz::ratwin::arg;
  }
#endif

namespace types {

namespace internal {

   struct HANDLE_struct {/*empty*/};
   struct Kernel_HANDLE_struct : public HANDLE_struct {/*empty*/};

   // Specializations of HANDLE that are not present in WINDOWS.H
   struct Thread_HANDLE_struct : public Kernel_HANDLE_struct {/*empty*/};
   struct IO_HANDLE_struct : public Kernel_HANDLE_struct {/*empty*/};
   struct Heap_struct : public HANDLE_struct { /*empty*/ };

   struct SOCKET_struct : public IO_HANDLE_struct {/*empty*/};
   struct HWND_struct : public HANDLE_struct {/*empty*/};
   struct HGDIOBJ_struct : public HANDLE_struct {/*empty*/};
   struct HBITMAP_struct : public HGDIOBJ_struct {/*empty*/};
   struct HBRUSH_struct : public HGDIOBJ_struct {/*empty*/};
   struct HPEN_struct : public HGDIOBJ_struct {/*empty*/};
   struct HFONT_struct : public HGDIOBJ_struct {/*empty*/};
   struct HREGION_struct : public HGDIOBJ_struct {/*empty*/};
   struct HKEY_struct : public HANDLE_struct {/*empty*/};
   struct HMENU_struct : public HANDLE_struct {/*empty*/};
   struct HICON_struct : public HANDLE_struct {/*empty*/};
   struct HCURSOR_struct : public HANDLE_struct {/*empty*/};

   // don't know what they're related to yet...
   struct HINSTANCE_struct : public HANDLE_struct {/*empty*/};
   struct HDC_struct : public HANDLE_struct {/*empty*/};
   struct HRSRC_struct : public HANDLE_struct {/*empty*/};

   // other handle-like things that don't map directly to Windows.H
   struct TLS_key_struct : public HANDLE_struct {/*empty*/};
   struct PROPSHEETPAGE_struct : public HANDLE_struct {/*empty*/};
   } //end of internal

typedef internal::HANDLE_struct* HANDLE;
typedef internal::Kernel_HANDLE_struct* Kernel_HANDLE;
typedef internal::IO_HANDLE_struct* IO_HANDLE;  // one that works with ReadFile, WriteFile, etc.
typedef internal::Heap_struct* Heap;
typedef internal::SOCKET_struct* SOCKET;
typedef internal::HWND_struct* HWND;
typedef internal::HINSTANCE_struct* HINSTANCE;
typedef internal::HINSTANCE_struct* HMODULE;   //module and instance are same thing
typedef internal::HBITMAP_struct* HBITMAP;
typedef internal::HMENU_struct* HMENU;
typedef internal::HDC_struct* HDC;
typedef internal::HGDIOBJ_struct* HGDIOBJ;
typedef internal::HICON_struct* HICON;
typedef internal::HCURSOR_struct* HCURSOR;
typedef internal::HBRUSH_struct* HBRUSH;
typedef internal::HPEN_struct* HPEN;
typedef internal::HFONT_struct* HFONT;
typedef internal::HREGION_struct* HREGION;
typedef internal::HRSRC_struct* HRSRC;
typedef internal::Thread_HANDLE_struct* Thread_HANDLE;
typedef internal::TLS_key_struct* TLS_key;
typedef internal::HKEY_struct* HKEY;
typedef internal::PROPSHEETPAGE_struct* HPROPSHEETPAGE;


// hsoft<Hwhatever> allows me to define an "in" parameter that accepts
// a strictly-typed Handle subtype, or a plain HANDLE, but not the =wrong=
// strictly-typed Handle.

template <typename T>
struct hsoft {
   arg::arg32 value;
   hsoft (T param) : value (reinterpret_cast<arg::arg32>(param)) {}
   hsoft (HANDLE param) : value (reinterpret_cast<arg::arg32>(param)) {}
   };

typedef unsigned short ATOM;

typedef classics::generic_2D_point<int> POINT;

struct RECT {
   long left;
   long top;
   long right;
   long bottom;
   };


struct SECURITY_ATTRIBUTES {
   ulong nLength;
   void* lpSecurityDescriptor;
   bool bInheritHandle;
   };

struct security_attributes : public SECURITY_ATTRIBUTES {
   security_attributes() { nLength= sizeof(SECURITY_ATTRIBUTES); lpSecurityDescriptor=0; bInheritHandle=false; }
   };

// idea:  (unsigned wMsg, long lEvent) can also be made strict

} // end of types
} // end of ratwin
ENDWRAP


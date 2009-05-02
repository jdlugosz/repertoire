// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\hid=struct.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#include "ratwin\COM\GUID.h"

STARTWRAP
namespace ratwin {
// The following structured comment lists all the WINDOWS macros used here.
// The Perl script MacroCloak adds code after reading this.
/* ## Macro_Cloak_Def (ratwin)
*/
// ## BEGIN MacroCloak Generated Code
// ## END Generated Code

namespace internal {
   struct DevInfo_HANDLE_struct : public ratwin::types::internal::HANDLE_struct {/*empty*/};
   }
typedef internal::DevInfo_HANDLE_struct* DevInfo_HANDLE;


enum DIGCF {
   DIGCF_DEFAULT=           0x00000001,  // only valid with DIGCF_DEVICEINTERFACE
   DIGCF_PRESENT=           0x00000002,
   DIGCF_ALLCLASSES=        0x00000004,
   DIGCF_PROFILE=           0x00000008,
   DIGCF_DEVICEINTERFACE=   0x00000010
   };

struct SP_DEVICE_INTERFACE_DATA {
   unsigned long cbSize;
   GUID  InterfaceClassGuid;
   unsigned long Flags;
   unsigned long Reserved;
   SP_DEVICE_INTERFACE_DATA() : cbSize (sizeof(SP_DEVICE_INTERFACE_DATA)) {}
   };

template <typename CharT>
struct SP_DEVICE_INTERFACE_DETAIL_DATA {
   unsigned long cbSize;
   CharT* DevicePath() { return reinterpret_cast<CharT*>(1+this); }
   };


namespace Hid {
struct ATTRIBUTES {
   unsigned long   Size; // = sizeof (struct _HIDD_ATTRIBUTES)
   unsigned short  VendorID;
   unsigned short  ProductID;
   unsigned short  VersionNumber;
   ATTRIBUTES() : Size (sizeof (ATTRIBUTES)) {}
   };

}

}

ENDWRAP

// ## Macro_Cloak_After
// ## BEGIN MacroCloak Generated Code
// ## END Generated Code


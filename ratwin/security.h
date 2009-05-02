// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\security.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\resource.h contains globals.
#endif

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {
__declspec(dllimport) int __stdcall InitializeSecurityDescriptor (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall SetSecurityDescriptorDacl (Dlugosz::ratwin::arg::arg32, int, void*, int);
}

STARTWRAP
namespace ratwin {
namespace security {

struct SID;  // never defined--SID* (i.e. PSID) is opaque.  VOID* in WINDOWS.H

struct ACL {
 unsigned char AclRevision;
 unsigned char Sbz1;
 unsigned short AclSize;
 unsigned short AceCount;
 unsigned short Sbz2;
 };

struct SECURITY_DESCRIPTOR {
 unsigned char Revision;
 unsigned char Sbz1;
 unsigned short /* SECURITY_DESCRIPTOR_CONTROL */ Control;
 SID* Owner;
 SID* Group;
 ACL* Sacl;
 ACL* Dacl;
 };


inline bool InitializeSecurityDescriptor (SECURITY_DESCRIPTOR& sa)
 {
 const int revision= 1;
 return ::InitializeSecurityDescriptor (reinterpret_cast<arg::arg32>(&sa), reinterpret_cast<arg::arg32>(revision));
 }

inline bool SetSecurityDescriptorDacl (SECURITY_DESCRIPTOR& sa, bool dacl_present, ACL* acl, bool defaulted)
 {
 return ::SetSecurityDescriptorDacl (reinterpret_cast<arg::arg32>(&sa), dacl_present, acl, defaulted);
 }
 
}}
ENDWRAP


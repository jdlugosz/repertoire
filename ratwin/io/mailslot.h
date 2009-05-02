// The Repertoire Project copyright 2001 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\mailslot.h
// Revision: 

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\mailslot.h contains globals.
#endif


#include "ratwin\io\general.h"

extern "C" {
__declspec(dllimport) int __stdcall CreateMailslotW (const wchar_t*, unsigned, unsigned, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall CreateMailslotA (const char*, unsigned, unsigned, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall GetMailslotInfo (Dlugosz::ratwin::arg::arg32, unsigned*, unsigned*, unsigned*, unsigned*);
}

STARTWRAP
namespace ratwin {
namespace io {

inline 
types::HANDLE CreateMailslot (const wchar_t* name, unsigned message_size, unsigned timeout, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::HANDLE> (::CreateMailslotW (name, message_size, timeout, reinterpret_cast<arg::carg32>(&sa)) ); }

inline 
types::HANDLE CreateMailslot (const char* name, unsigned message_size, unsigned timeout, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::HANDLE> (::CreateMailslotA (name, message_size, timeout, reinterpret_cast<arg::carg32>(&sa)) ); }

inline 
types::HANDLE CreateMailslot (const wchar_t* name, unsigned message_size, unsigned timeout)
 { return reinterpret_cast<types::HANDLE> (::CreateMailslotW (name, message_size, timeout, 0) ); }

inline 
types::HANDLE CreateMailslot (const char* name, unsigned message_size, unsigned timeout)
 { return reinterpret_cast<types::HANDLE> (::CreateMailslotA (name, message_size, timeout, 0) ); }

inline
bool GetMailslotInfo (types::HANDLE h, unsigned* max_message_size, unsigned* next_size, unsigned* count, unsigned* timeout)
 { return ::GetMailslotInfo (reinterpret_cast<arg::arg32>(h), max_message_size, next_size, count, timeout); }

} //end io
}
ENDWRAP



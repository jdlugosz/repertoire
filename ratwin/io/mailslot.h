// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\io\mailslot.h
// Revision: public build 9, shipped on 18-Oct-2006

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
types::IO_HANDLE CreateMailslot (const wchar_t* name, unsigned message_size, unsigned timeout, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::IO_HANDLE> (::CreateMailslotW (name, message_size, timeout, reinterpret_cast<arg::carg32>(&sa)) ); }

inline 
types::IO_HANDLE CreateMailslot (const char* name, unsigned message_size, unsigned timeout, const types::SECURITY_ATTRIBUTES& sa)
 { return reinterpret_cast<types::IO_HANDLE> (::CreateMailslotA (name, message_size, timeout, reinterpret_cast<arg::carg32>(&sa)) ); }

inline 
types::IO_HANDLE CreateMailslot (const wchar_t* name, unsigned message_size, unsigned timeout)
 { return reinterpret_cast<types::IO_HANDLE> (::CreateMailslotW (name, message_size, timeout, 0) ); }

inline 
types::IO_HANDLE CreateMailslot (const char* name, unsigned message_size, unsigned timeout)
 { return reinterpret_cast<types::IO_HANDLE> (::CreateMailslotA (name, message_size, timeout, 0) ); }

inline
bool GetMailslotInfo (types::IO_HANDLE h, unsigned* max_message_size, unsigned* next_size, unsigned* count, unsigned* timeout)
 { return ::GetMailslotInfo (reinterpret_cast<arg::arg32>(h), max_message_size, next_size, count, timeout); }

} //end io
}
ENDWRAP



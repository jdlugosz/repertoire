// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\tasking\basic.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once
#if !defined RATWIN_TASKING_BASIC_INCLUDED
#define RATWIN_TASKING_BASIC_INCLUDED

#include "ratwin\base.h"

// DLL imports "cloaked" for overloading
extern "C" {

__declspec(dllimport) unsigned long __stdcall WaitForSingleObject (Dlugosz::ratwin::arg::arg32, unsigned long);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObjectEx (Dlugosz::ratwin::arg::arg32, unsigned long, unsigned alertable);
__declspec(dllimport) unsigned long __stdcall WaitForMultipleObjects (int count, Dlugosz::ratwin::arg::arg32, int, unsigned long);
__declspec(dllimport) unsigned long __stdcall WaitForMultipleObjectsEx (int count, Dlugosz::ratwin::arg::arg32, int, unsigned long, unsigned alertable);
__declspec(dllimport) unsigned long __stdcall SignalObjectAndWait (Dlugosz::ratwin::arg::arg32, Dlugosz::ratwin::arg::arg32, unsigned long, int alertable);
}

///////////////////////////////////////////////////

STARTWRAP
namespace ratwin {

namespace tasking {

const ulong WAIT_TIMEOUT= 0x00000102;
const ulong WAIT_OBJECT_0= 0;
inline ulong WAIT_OBJECT(int index) { return WAIT_OBJECT_0 + index; }
const ulong WAIT_ABANDOND_0= 0x00000080; 
const ulong WAIT_FAILED= 0xffffffff;
const ulong WAIT_IO_COMPLETION= 0x000000C0L;

enum alertable_t { alertable=1, not_alertable=0 };

inline
ulong WaitForSingleObject (types::HANDLE object, ulong time=0xffffffff)
 { return ::WaitForSingleObject (reinterpret_cast<arg::arg32>(object), time); }

inline
ulong WaitForSingleObject (types::HANDLE object, alertable_t alertable, ulong time=0xffffffff)
 { return ::WaitForSingleObjectEx (reinterpret_cast<arg::arg32>(object), time, alertable); }

inline
ulong WaitForMultipleObjects (int count, types::HANDLE* objectlist, bool all, ulong time=0xffffffff)
 { return ::WaitForMultipleObjects (count, reinterpret_cast<arg::arg32>(objectlist), all, time); }

inline
ulong WaitForMultipleObjects (int count, types::HANDLE* objectlist, bool all, alertable_t alertable, ulong time=0xffffffff)
 { return ::WaitForMultipleObjectsEx (count, reinterpret_cast<arg::arg32>(objectlist), all, time, alertable); }

inline
ulong SignalObjectAndWait (types::HANDLE sig, types::HANDLE wait, alertable_t alertable, ulong time= 0xffffffff)
 { return ::SignalObjectAndWait (reinterpret_cast<arg::arg32>(sig), reinterpret_cast<arg::arg32>(wait), time, alertable); }


} //end tasking

}
ENDWRAP
#endif


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\sound.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\sound.h contains globals.
#endif

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) int __stdcall MessageBeep (Dlugosz::ratwin::arg::arg32);
__declspec(dllimport) int __stdcall PlaySoundA (Dlugosz::ratwin::arg::carg32, void*, int);
__declspec(dllimport) int __stdcall PlaySoundW (Dlugosz::ratwin::arg::carg32, void*, int);
}


STARTWRAP
namespace ratwin {
namespace sound {

inline
bool MessageBeep (unsigned options=0)
 { return ::MessageBeep (reinterpret_cast<arg::arg32>(options)); }

enum snd {
   SND_SYNC=            0x0000,  // play synchronously (default)
   SND_ASYNC=           0x0001,  // play asynchronously
   SND_NODEFAULT=       0x0002,  // silence (!default) if sound not found
   SND_MEMORY=          0x0004,  // soundname points to a memory file
   SND_LOOP=            0x0008,  // loop the sound until next PlaySound
   SND_NOSTOP=          0x0010,  // don't stop any currently playing sound
   SND_PURGE=           0x0040,  // purge non-static events for task
   SND_APPLICATION=     0x0080,  // look for application-specific association
   SND_NOWAIT=   0x00002000, // don't wait if the driver is busy
   SND_ALIAS=       0x00010000, // name is a registry alias
   SND_FILENAME=    0x00020000, // name is file name
   SND_RESOURCE=    0x00040004, // name is resource name or atom
   //#define SND_ALIAS_ID 0x00110000L /* alias is a predefined ID */
   // ALIAS_ID's not defined here.  Use ALIAS (name) or call MessageBeep instead.
   };
   
inline
bool PlaySound (const char* soundname, types::HMODULE hmod, classics::flagword<snd> options)
 {
 return ::PlaySoundA (reinterpret_cast<arg::carg32>(soundname), hmod, options.validdata());
 }

inline
bool PlaySound (const wchar_t* soundname, types::HMODULE hmod, classics::flagword<snd> options)
 {
 return ::PlaySoundW (reinterpret_cast<arg::carg32>(soundname), hmod, options.validdata());
 }

}}
ENDWRAP


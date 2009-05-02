// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\virtual_key.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\ustring.h"


STARTWRAP
namespace classics {
namespace VK {

enum VK {
  VK_invalid=0, _high=0x80000000  //force it to take 32 bits unsigned
  };

enum VK_modifier { 
   ShiftKey= 0x100,
   CapLockSet= 0x200,
   ControlKey= 0x400,
   AltKey= 0x800,
   NumLockSet= 0x2000,
   AltOnLeft= 0x4000,
   AltOnRight= 0x8000,
   NumPadKey= 0x1000,
   CtrlOnLeft= 0x10000,
   CtrlOnRight= 0x20000,
   ExtKey= 0x40000
   };

inline VK_modifier operator+ (VK_modifier left, VK_modifier right)
   {
   return VK_modifier (int(left)+int(right));
   }

inline VK operator+ (VK_modifier left, VK right)
 {
 return VK (int(left)+int(right));
 }

CLASSICS_EXPORT ustring as_ustring (VK);
template<typename T> T parse (const ustring&);
template<>
CLASSICS_EXPORT VK parse<VK> (const ustring&);


// take values from ReadConsoleInput's KEY_EVENT_RECORD and produce a VK
CLASSICS_EXPORT VK VKencode (unsigned key, unsigned ControlKeyState);


}}  //end of namespace
ENDWRAP


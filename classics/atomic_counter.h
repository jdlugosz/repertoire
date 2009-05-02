// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter.h
// Revision: public build 6, shipped on 28-Nov-1999

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"


STARTWRAP
namespace classics {

namespace internal {
 // I tried putting these functions here in the header as
 // static (to avoid the extra JMP of the DLL call) but it
 // wasn't any faster.  So, I'll keep the non-standard
 // stuff out of the header.
 // I can't make it inline because the register allocation varies
 // and inline assembly code won't track in Microsoft C++.
 // Watcom could do it, so anyone making a Watcom port ought
 // to put it in the header.
   CLASSICS_EXPORT int __fastcall Xadd (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short __fastcall Xadd (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char __fastcall Xadd (volatile char*,int);  // 1 byte
   inline long Xadd (volatile long* p, int delta)
      { return Xadd ((volatile int*)p, delta); }
   inline unsigned Xadd (volatile unsigned* p, int delta)
      { return Xadd ((volatile int*)p, delta); }
   inline ushort Xadd (volatile ushort* p, int delta)
      { return Xadd ((volatile short*)p, delta); }
   inline ulong Xadd (volatile ulong* p, int delta)
      { return Xadd ((volatile long*)p, delta); }
#if 0
// Microsoft VC++ doesn't like this.  It thinks char and signed char are
// the same thing, not distinct types for overloading.
   inline signed char Xadd (volatile signed char* p, int delta)
      { return Xadd ((volatile char*)p, delta); }
#endif
   inline byte Xadd (volatile byte* p, int delta)
      { return Xadd ((volatile char*)p, delta); }

   CLASSICS_EXPORT int __fastcall Xexchange (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short __fastcall Xexchange (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char __fastcall Xexchange (volatile char*,int);  // 1 byte
   inline long Xexchange (volatile long* p, int newvalue)
      { return Xexchange ((volatile int*)p, newvalue); }
   inline unsigned Xexchange (volatile unsigned* p, int newvalue)
      { return Xexchange ((volatile int*)p, newvalue); }
   inline ushort Xexchange (volatile ushort* p, int newvalue)
      { return Xexchange ((volatile short*)p, newvalue); }
   inline ulong Xexchange (volatile ulong* p, int newvalue)
      { return Xexchange ((volatile long*)p, newvalue); }
   inline byte Xexchange (volatile byte* p, int newvalue)
      { return Xexchange ((volatile char*)p, newvalue); }
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile __int64* dest, int source, int comparend);  // 8 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile int* dest, int source, int comparend);  // 4 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile short* dest, int source, int comparend);  // 2 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile char* dest, int source, int comparend);  // 1 byte
   inline long CompareAndSwap (volatile long* dest, int source, int comparend)
   	{ return CompareAndSwap ((volatile int*)dest, source, comparend); }
   inline long CompareAndSwap (volatile unsigned* dest, int source, int comparend)
   	{ return CompareAndSwap ((volatile int*)dest, source, comparend); }
   inline long CompareAndSwap (volatile ushort* dest, int source, int comparend)
   	{ return CompareAndSwap ((volatile short*)dest, source, comparend); }
   inline long CompareAndSwap (volatile ulong* dest, int source, int comparend)
   	{ return CompareAndSwap ((volatile long*)dest, source, comparend); }
   inline long CompareAndSwap (volatile byte* dest, int source, int comparend)
   	{ return CompareAndSwap ((volatile char*)dest, source, comparend); }
} // end of internal


/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class atomic_counter {
protected:
   T value;
   // >> need a critical section, too.
public:
   operator T() const volatile { return value; }
   T operator= (atomic_counter x) volatile { value = x.value; }
   atomic_counter (T x) : value(x) {}
   atomic_counter() {}
   T operator++() volatile;
   T operator--() volatile;
   T operator++ (int) volatile;
   T operator-- (int) volatile;
   T operator+= (T) volatile;
   T operator-= (T) volatile;
   T exchange (T) volatile;
   bool compare_and_swap (T source, T compare) volatile;
   };

// The implementation of the general case requires a critical
// section.  No implementation is provided at this time.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

template <typename T>
class atomic_integer_xx {
protected:
   T value;
public:
   operator T() const volatile { return value; }
   atomic_integer_xx (T x) : value(x) {}
   atomic_integer_xx() {}
   T operator++() volatile
      { return 1+ internal::Xadd (&value,1); }
   T operator--() volatile
      { return internal::Xadd (&value,-1) -1; }
   T operator++ (int) volatile
      { return internal::Xadd (&value,1); }
   T operator-- (int) volatile
      { return internal::Xadd (&value,-1); }
   T operator+= (T delta) volatile
      { return delta + internal::Xadd (&value,delta); }
   T operator-= (T delta) volatile
      { return internal::Xadd (&value,-delta) - delta; }
   T exchange (T newval) volatile
      { return internal::Xexchange (&value, newval); }
   bool compare_and_swap (T source, T compare) volatile
      { return internal::CompareAndSwap (&value, source, compare); }
   };

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

#pragma warning (disable:4146)
template<>
class atomic_counter<int> : public atomic_integer_xx<int> {
public:
   atomic_counter() {}
   atomic_counter (int x) : atomic_integer_xx<int>(x) {}
   int operator= (atomic_counter x) volatile { return value = x.value; }
   };
 
class atomic_counter<unsigned> : public atomic_integer_xx<unsigned> {
public:
   atomic_counter() {}
   atomic_counter (unsigned x) : atomic_integer_xx<unsigned>(x) {}
   unsigned operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
class atomic_counter<short> : public atomic_integer_xx<short> {
public:
   atomic_counter() {}
   atomic_counter (short x) : atomic_integer_xx<short>(x) {}
   short operator= (atomic_counter x) volatile { return value = x.value; }
   };

class atomic_counter<long> : public atomic_integer_xx<long> {
public:
   atomic_counter() {}
   atomic_counter (long x) : atomic_integer_xx<long>(x) {}
   long operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
class atomic_counter<ulong> : public atomic_integer_xx<ulong> {
public:
   atomic_counter() {}
   atomic_counter (ulong x) : atomic_integer_xx<ulong>(x) {}
   ulong operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
class atomic_counter<ushort> : public atomic_integer_xx<ushort> {
public:
   atomic_counter() {}
   atomic_counter (ushort x) : atomic_integer_xx<ushort>(x) {}
   ushort operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
class atomic_counter<char> : public atomic_integer_xx<char> {
public:
   atomic_counter() {}
   atomic_counter (char x) : atomic_integer_xx<char>(x) {}
   char operator= (atomic_counter x) volatile { return value = x.value; }
   };

#if 0
// MSVC++ strikes again
class atomic_counter<signed char> : public atomic_integer_xx<signed char> {
public:
   atomic_counter() {}
   atomic_counter (signed char x) : atomic_integer_xx<signed char>(x) {}
   signed char operator= (atomic_counter x) volatile { return value = x.value; }
   };
#endif

class atomic_counter<byte> : public atomic_integer_xx<byte> {
public:
   atomic_counter() {}
   atomic_counter (byte x) : atomic_integer_xx<byte>(x) {}
   byte operator= (atomic_counter x) volatile { return value = x.value; }
   };
#pragma warning (default:4146)

}  //end of namespace

ENDWRAP



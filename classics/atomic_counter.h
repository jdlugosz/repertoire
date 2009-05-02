// The Repertoire Project copyright 2003 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter.h
// Revision: post-public build 6, modified 16-September-2003 or later

#pragma once

#if !defined CLASSICS_EXPORT
#define CLASSICS_EXPORT __declspec(dllimport)
#endif

#include "classics\common.h"


STARTWRAP
namespace classics {

namespace internal {
   CLASSICS_EXPORT extern bool SingleCPU;

   // the nf_ functions are the same, but without __fastcall.
   CLASSICS_EXPORT int nf_Xadd (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short nf_Xadd (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char nf_Xadd (volatile char*,int);  // 1 byte
#ifndef _MANAGED
   CLASSICS_EXPORT int __fastcall Xadd (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short __fastcall Xadd (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char __fastcall Xadd (volatile char*,int);  // 1 byte
#else
   inline int Xadd (volatile int* p, int delta)
      { return nf_Xadd (p, delta); }
   inline short Xadd (volatile short* p, int delta)
      { return nf_Xadd (p, delta); }
   inline char Xadd (volatile char* p, int delta)
      { return nf_Xadd (p, delta); }
#endif
   inline long Xadd (volatile long* p, int delta)
      { return Xadd ((volatile int*)p, delta); }
   inline unsigned Xadd (volatile unsigned* p, int delta)
      { return Xadd ((volatile int*)p, delta); }
   inline ushort Xadd (volatile ushort* p, int delta)
      { return Xadd ((volatile short*)p, delta); }
   inline ulong Xadd (volatile ulong* p, int delta)
      { return Xadd ((volatile long*)p, delta); }
#if defined _MSC_VER && _MSC_VER < 1300
// Older versions of Microsoft VC++ doesn't like this.  It thinks char and signed char are
// the same thing, not distinct types for overloading.
   inline signed char Xadd (volatile signed char* p, int delta)
      { return Xadd ((volatile char*)p, delta); }
#endif
   inline byte Xadd (volatile byte* p, int delta)
      { return Xadd ((volatile char*)p, delta); }

   // the nf_ functions are the same, but without __fastcall.
   CLASSICS_EXPORT void nf_Inc (volatile int*);  // 4 bytes
   CLASSICS_EXPORT void nf_Inc (volatile short*);  // 2 bytes
   CLASSICS_EXPORT void nf_Inc (volatile char*);  // 1 byte
#ifndef _MANAGED
   CLASSICS_EXPORT void __fastcall Inc (volatile int*);  // 4 bytes
   CLASSICS_EXPORT void __fastcall Inc (volatile short*);  // 2 bytes
   CLASSICS_EXPORT void __fastcall Inc (volatile char*);  // 1 byte
#else
   inline void Inc (volatile int* p)
      { return nf_Inc (p); }
   inline void Inc (volatile short* p)
      { return nf_Inc (p); }
   inline void Inc (volatile char* p)
      { return nf_Inc (p); }
#endif
   inline void Inc (volatile long* p)      { Inc ((volatile int*)p); }
   inline void Inc (volatile unsigned* p)      { Inc ((volatile int*)p); }
   inline void Inc (volatile ushort* p)      { Inc ((volatile short*)p); }
   inline void Inc (volatile ulong* p)      { Inc ((volatile long*)p); }
#if defined _MSC_VER && _MSC_VER < 1300
   // Older versions of Microsoft VC++ doesn't like this.  It thinks char and signed char are
   // the same thing, not distinct types for overloading.
   inline void Inc (volatile signed char* p)      { Inc ((volatile char*)p); }
#endif
   inline void Inc (volatile byte* p)      { Inc ((volatile char*)p); }

   // the nf_ functions are the same, but without __fastcall.
   CLASSICS_EXPORT bool nf_Dec (volatile int*);  // 4 bytes
   CLASSICS_EXPORT bool nf_Dec (volatile short*);  // 2 bytes
   CLASSICS_EXPORT bool nf_Dec (volatile char*);  // 1 byte
#ifndef _MANAGED
   CLASSICS_EXPORT bool __fastcall Dec (volatile int*);  // 4 bytes
   CLASSICS_EXPORT bool __fastcall Dec (volatile short*);  // 2 bytes
   CLASSICS_EXPORT bool __fastcall Dec (volatile char*);  // 1 byte
#else
   inline bool Dec (volatile int* p)
      { return nf_Dec (p); }
   inline bool Dec (volatile short* p)
      { return nf_Dec (p); }
   inline bool Dec (volatile char* p)
      { return nf_Dec (p); }
#endif
   inline bool Dec (volatile long* p)      { return Dec ((volatile int*)p); }
   inline bool Dec (volatile unsigned* p)      { return Dec ((volatile int*)p); }
   inline bool Dec (volatile ushort* p)      { return Dec ((volatile short*)p); }
   inline bool Dec (volatile ulong* p)      { return Dec ((volatile long*)p); }
#if defined _MSC_VER && _MSC_VER < 1300
      // Older versions of Microsoft VC++ doesn't like this.  It thinks char and signed char are
      // the same thing, not distinct types for overloading.
   inline bool Dec (volatile signed char* p)      { return Dec ((volatile char*)p); }
#endif
   inline bool Dec (volatile byte* p)      { return Dec ((volatile char*)p); }

   // the nf_ functions are the same, but without __fastcall.
   CLASSICS_EXPORT int nf_Xexchange (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short nf_Xexchange (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char nf_Xexchange (volatile char*,int);  // 1 byte
#ifndef _MANAGED
   CLASSICS_EXPORT int __fastcall Xexchange (volatile int*,int);  // 4 bytes
   CLASSICS_EXPORT short __fastcall Xexchange (volatile short*,int);  // 2 bytes
   CLASSICS_EXPORT char __fastcall Xexchange (volatile char*,int);  // 1 byte
#else
   inline int Xexchange (volatile int* p, int newvalue)
      { return nf_Xexchange (p, newvalue); }
   inline short Xexchange (volatile short* p, short newvalue)
      { return nf_Xexchange (p, newvalue); }
   inline char Xexchange (volatile char* p, char newvalue)
      { return nf_Xexchange (p, newvalue); }
#endif
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

   // the nf_ functions are the same, but without __fastcall.
   CLASSICS_EXPORT bool nf_CompareAndSwap (volatile __int64* dest, int source, int comparend);  // 8 bytes
      // Note: 64-bit form is not implemented.
   CLASSICS_EXPORT bool nf_CompareAndSwap (volatile int* dest, int source, int comparend);  // 4 bytes
   CLASSICS_EXPORT bool nf_CompareAndSwap (volatile short* dest, int source, int comparend);  // 2 bytes
   CLASSICS_EXPORT bool nf_CompareAndSwap (volatile char* dest, int source, int comparend);  // 1 byte
#ifndef _MANAGED
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile __int64* dest, int source, int comparend);  // 8 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile int* dest, int source, int comparend);  // 4 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile short* dest, int source, int comparend);  // 2 bytes
   CLASSICS_EXPORT bool __fastcall CompareAndSwap (volatile char* dest, int source, int comparend);  // 1 byte
#else
   inline bool CompareAndSwap (volatile __int64* dest, int source, int comparend)
      { return nf_CompareAndSwap (dest, source, comparend); }
   inline bool CompareAndSwap (volatile int* dest, int source, int comparend)
      { return nf_CompareAndSwap (dest, source, comparend); }
   inline bool CompareAndSwap (volatile short* dest, int source, int comparend)
      { return nf_CompareAndSwap (dest, source, comparend); }
   inline bool CompareAndSwap (volatile char* dest, int source, int comparend)
      { return nf_CompareAndSwap (dest, source, comparend); }
#endif
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
   void inc() volatile;
   bool dec() volatile;  // returns true if it became equal to zero
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
   bool dec() volatile
      { return internal::Dec (&value); }
   void inc() volatile
      { internal::Inc (&value); }
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
 
template<>
class atomic_counter<unsigned> : public atomic_integer_xx<unsigned> {
public:
   atomic_counter() {}
   atomic_counter (unsigned x) : atomic_integer_xx<unsigned>(x) {}
   unsigned operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
template<>
class atomic_counter<short> : public atomic_integer_xx<short> {
public:
   atomic_counter() {}
   atomic_counter (short x) : atomic_integer_xx<short>(x) {}
   short operator= (atomic_counter x) volatile { return value = x.value; }
   };

template<>
class atomic_counter<long> : public atomic_integer_xx<long> {
public:
   atomic_counter() {}
   atomic_counter (long x) : atomic_integer_xx<long>(x) {}
   long operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
template<>
class atomic_counter<ulong> : public atomic_integer_xx<ulong> {
public:
   atomic_counter() {}
   atomic_counter (ulong x) : atomic_integer_xx<ulong>(x) {}
   ulong operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
template<>
class atomic_counter<ushort> : public atomic_integer_xx<ushort> {
public:
   atomic_counter() {}
   atomic_counter (ushort x) : atomic_integer_xx<ushort>(x) {}
   ushort operator= (atomic_counter x) volatile { return value = x.value; }
   };
   
template<>
class atomic_counter<char> : public atomic_integer_xx<char> {
public:
   atomic_counter() {}
   atomic_counter (char x) : atomic_integer_xx<char>(x) {}
   char operator= (atomic_counter x) volatile { return value = x.value; }
   };

#if defined _MSC_VER && _MSC_VER < 1300
// MSVC++ strikes again
template<>
class atomic_counter<signed char> : public atomic_integer_xx<signed char> {
public:
   atomic_counter() {}
   atomic_counter (signed char x) : atomic_integer_xx<signed char>(x) {}
   signed char operator= (atomic_counter x) volatile { return value = x.value; }
   };
#endif

template<>
class atomic_counter<byte> : public atomic_integer_xx<byte> {
public:
   atomic_counter() {}
   atomic_counter (byte x) : atomic_integer_xx<byte>(x) {}
   byte operator= (atomic_counter x) volatile { return value = x.value; }
   };
#pragma warning (default:4146)

}  //end of namespace

ENDWRAP



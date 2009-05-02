// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\atomic_counter.h"

STARTWRAP
namespace classics {
namespace internal {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xadd (volatile int*, int)
 {
 __asm {
    lock xadd dword ptr [ECX], EDX
    mov EAX, EDX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xadd (volatile short*, int)
 {
 __asm {
    lock xadd word ptr [ECX], DX
    mov AX, DX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xadd (volatile char*, int)
 {
 __asm {
    lock xadd byte ptr [ECX], DL
    mov AL, DL
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xexchange (volatile int*, int)
 {
 __asm {
    mov EAX, EDX
    xchg dword ptr [ECX], EAX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xexchange (volatile short*, int)
 {
 __asm {
    mov AX, DX
    xchg word ptr [ECX], AX
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xexchange (volatile char*, int)
 {
 __asm {
    mov AL, DL
    xchg byte ptr [ECX], AL
    ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

// >> add a cmpxchg8 (64-bit) form, too.

 __declspec(naked) bool __fastcall CompareAndSwap (volatile int* dest, int source, int comparend)
 {
 __asm {
    mov EAX, [ESP+4]
    lock cmpxchg dword ptr [ECX], EDX   ;// if([ECX]==EAX){ZF=1;[ECX]=EDX;}else ZF=0;
    setZ AL  // return boolean based on Z flag.
    // that makes more sense than always returning comparend, regardless!
    ret 4
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

 __declspec(naked) bool __fastcall CompareAndSwap (volatile short* dest, int source, int comparend)
 {
 __asm {
    mov EAX, [ESP+4]
    lock cmpxchg word ptr [ECX], DX   ;// if([ECX]==EAX){ZF=1;[ECX]=EDX;}else ZF=0;
    setZ AL  // return boolean based on Z flag.
    // that makes more sense than always returning comparend, regardless!
    ret 4
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

 __declspec(naked) bool __fastcall CompareAndSwap (volatile char* dest, int source, int comparend)
 {
 __asm {
    mov EAX, [ESP+4]
    lock cmpxchg byte ptr [ECX], DL   ;// if([ECX]==EAX){ZF=1;[ECX]=EDX;}else ZF=0;
    setZ AL  // return boolean based on Z flag.
    // that makes more sense than always returning comparend, regardless!
    ret 4
    }
 }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end internal
} // end classics
ENDWRAP


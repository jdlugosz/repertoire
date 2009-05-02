// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\atomic_counter.cpp
// Revision: public build 9, shipped on 18-Oct-2006

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\atomic_counter.h"
#include "ratwin\sysinfo.h"

STARTWRAP
namespace classics {
namespace internal {

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

bool detect_CPUs()
 {
 ratwin::SYSTEM_INFO info;
 ratwin::GetSystemInfo (info);
 return info.dwNumberOfProcessors == 1;  // true for a single-CPU system
 }

bool SingleCPU= detect_CPUs();  // is false before constructor runs, the more general case.

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xadd (volatile int*, int)
 {
 __asm {
    lock xadd dword ptr [ECX], EDX
    mov EAX, EDX
    ret
    }
 }

int nf_Xadd (volatile int* p, int delta)
 { return Xadd (p, delta); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xadd (volatile short*, int)
 {
 __asm {
    lock xadd word ptr [ECX], DX
    mov AX, DX
    ret
    }
 }

short nf_Xadd (volatile short* p, int delta)
 { return Xadd (p, delta); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xadd (volatile char*, int)
 {
 __asm {
    lock xadd byte ptr [ECX], DL
    mov AL, DL
    ret
    }
 }

char nf_Xadd (volatile char* p, int delta)
 { return Xadd (p, delta); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) void __fastcall Inc (volatile int*)
 {
 if (SingleCPU)  __asm {
    inc dword ptr [ECX]
    ret
    }
 else  __asm {
    lock inc dword ptr [ECX]
    ret
    }
 }

void nf_Inc (volatile int* p)
 { Inc (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) void __fastcall Inc (volatile short*)
 {
 if (SingleCPU)  __asm {
    inc word ptr [ECX]
    ret
    }
 else  __asm {
    lock inc word ptr [ECX]
    ret
    }
 }

void nf_Inc (volatile short* p)
 { Inc (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) void __fastcall Inc (volatile char*)
 {
 if (SingleCPU)  __asm {
    inc byte ptr [ECX]
    ret
    }
 else  __asm {
    lock inc byte ptr [ECX]
    ret
    }
 }

void nf_Inc (volatile char* p)
 { Inc (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall Dec (volatile int*)
 {
 if (SingleCPU)  __asm {
    dec dword ptr [ECX]
    setz al
    ret
    }
 else  __asm {
    lock dec dword ptr [ECX]
    setz al
    ret
    }
 }

bool nf_Dec (volatile int* p)
 { return Dec (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall Dec (volatile short*)
 {
 if (SingleCPU)  __asm {
    dec word ptr [ECX]
    setz al
    ret
    }
 else  __asm {
    lock dec word ptr [ECX]
    setz al
    ret
    }
 }

bool nf_Dec (volatile short* p)
 { return Dec (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall Dec (volatile char*)
 {
 if (SingleCPU)  __asm {
    dec byte ptr [ECX]
    setz al
    ret
    }
 else  __asm {
    lock dec byte ptr [ECX]
    setz al
    ret
    }
 }

bool nf_Dec (volatile char* p)
 { return Dec (p); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) __int64 __fastcall Xexchange (volatile __int64* dest, __int64 source)
 {
 /* Caller is generating code to:
    push source-high
    push source-low
    load ECX with dest (the pointer)
    Then, CALL pushes return address
    Caller expects result in EDX:EAX
 */
 __asm {
    // I need comparend in EDX:EAX, source in ECX:EBX
    push EBX  // must preserve register for caller
    push EDI  // preserve
    mov EDI, ECX  // free up ECX.  dest is now [EDI]
    mov EBX, [ESP+12]
    mov ECX, [ESP+16]
    // use original value as comparand, without locking
    mov EAX, [EDI]
    mov EDX, [EDI+4]
    }
 retry:
 __asm {
    lock cmpxchg8b [EDI]
    jnz retry
    pop EDI  // restore
    pop EBX  // restore
    ret 8
    }
 }

__int64 nf_Xexchange (volatile __int64* p, __int64 newvalue)
 { return Xexchange (p, newvalue); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) int __fastcall Xexchange (volatile int*, int)
 {
 __asm {
    mov EAX, EDX
    xchg dword ptr [ECX], EAX
    ret
    }
 }

int nf_Xexchange (volatile int* p, int newvalue)
 { return Xexchange (p, newvalue); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) short __fastcall Xexchange (volatile short*, int)
 {
 __asm {
    mov AX, DX
    xchg word ptr [ECX], AX
    ret
    }
 }

short nf_Xexchange (volatile short* p, int newvalue)
 { return Xexchange (p, newvalue); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) char __fastcall Xexchange (volatile char*, int)
 {
 __asm {
    mov AL, DL
    xchg byte ptr [ECX], AL
    ret
    }
 }

char nf_Xexchange (volatile char* p, int newvalue)
 { return Xexchange (p, newvalue); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall CompareAndSwap (volatile __int64* dest, __int64 source, __int64 comparend)
 {
 // I need comparend in EDX:EAX, source in ECX:EBX
 /* Caller is generating code to:
    push comparend-high
    push comparent-low
    push source-high
    push source-low
    load ECX with dest (the pointer)
    Then, CALL pushes return address
 */
 __asm {
    push EBX  // must preserve for caller
    push EDI  // preserve
    mov EDI, ECX  // free up ECX, now dest is [EDI]
    mov EBX, [ESP+12]
    mov ECX, [ESP+16]
    mov EAX, [ESP+20]
    mov EDX, [ESP+24]
    lock cmpxchg8b [EDI]
    setZ AL
    pop EDI  // restore
    pop EBX  // restore
    ret 16
    }
 }

bool nf_CompareAndSwap (volatile __int64* dest, __int64 source, __int64 comparend)
 { return CompareAndSwap (dest, source, comparend); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

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

bool nf_CompareAndSwap (volatile int* dest, int source, int comparend)
 { return CompareAndSwap (dest, source, comparend); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall CompareAndSwap (volatile short* dest, int source, int comparend)
 {
 __asm {
    mov EAX, [ESP+4]
    lock cmpxchg word ptr [ECX], DX   ;// if([ECX]==AX){ZF=1;[ECX]=DX;}else ZF=0;
    setZ AL  // return boolean based on Z flag.
    // that makes more sense than always returning comparend, regardless!
    ret 4
    }
 }

bool nf_CompareAndSwap (volatile short* dest, int source, int comparend)
 { return CompareAndSwap (dest, source, comparend); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec(naked) bool __fastcall CompareAndSwap (volatile char* dest, int source, int comparend)
 {
 __asm {
    mov EAX, [ESP+4]
    lock cmpxchg byte ptr [ECX], DL   ;// if([ECX]==AL){ZF=1;[ECX]=DL;}else ZF=0;
    setZ AL  // return boolean based on Z flag.
    // that makes more sense than always returning comparend, regardless!
    ret 4
    }
 }

bool nf_CompareAndSwap (volatile char* dest, int source, int comparend)
 { return CompareAndSwap (dest, source, comparend); }

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

} // end internal
} // end classics
ENDWRAP


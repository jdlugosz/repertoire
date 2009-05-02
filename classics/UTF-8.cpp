// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\UTF-8.cpp
// Revision: public build 6, shipped on 28-Nov-1999

#define CLASSICS_EXPORT __declspec(dllexport)
#include "classics\UTF-8.h"

STARTWRAP
namespace classics {

 static const unsigned char size_table[32] = {
    1,1,1,1,1,1,1,
    2,2,2,2,
    3,3,3,3,3,
    4,4,4,4,4,
    5,5,5,5,5,
    6,6,6,6,6,
    7
    };

 static unsigned __int32 jumptable[7];

/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

__declspec (naked)
__int32 __stdcall UCS2_to_UTF8 (const wchar_t* input, int chars, int* chars_processed, char* output, int bufsize)
 {
 __asm {
    // set up function call
    push ebp
    mov ebp,esp
    push esi   ;preserve registers
    push edi
    push ebx
    // create jump table
    lea edi, jumptable
    cmp dword ptr [edi], 0
    jne done_making_table  ; "only need to do this the first time through"
    lea eax, case1
    mov [edi+4], eax
    lea eax, case2
    mov [edi+8], eax
    lea eax, case3
    mov [edi+12], eax
    lea eax, case4
    mov [edi+16], eax
    lea eax, case5
    mov [edi+20], eax
    lea eax, case6
    mov [edi+24], eax
    mov dword ptr [edi], -1
   done_making_table:
    // set up for processing
    mov esi, input    ; source
    mov edi, output   ; destination
    jmp iterate
   looptop:
    movzx eax, word ptr [esi]   ; "Unicode value in eax"
    mov ebx, eax ; "prep for surrogate pair test"
    add esi, 2
    // is it a surrogate pair?
    and ebx, 0d800h  ; "look at these five bits"
    cmp ebx, 0d800h
    je surrogate_pair
   process_char:
    // how many bytes will the encoding take?
    bsr ebx,eax
    jnz l2
    // if value was zero, ebx is undefined but zf is set
    mov ebx, 1  ;"encode as 1 byte"
    jmp l3
   l2:
    movzx ebx, byte ptr size_table[ebx]
   l3:
    // ebx tells me how many bytes the result will take.
    cmp ebx, bufsize  ; "will it fit?"
    ja will_not_fit
    sub bufsize, ebx
    jmp dword ptr jumptable[ebx*4]
   case6:
   case5:
   case4:
   case3:
    mov ebx, eax
    shr eax, 6
    and ebx, 00111111b
    or ebx, 10000000b
    mov [edi+2], bl
    mov ebx, eax
    shr eax, 6
    and ebx, 00111111b
    or ebx, 10000000b
    mov [edi+1], bl
    or eax, 11100000b
    mov [edi], al
    add edi, 3
    jmp iterate
   case2:
    mov ebx, eax
    shr eax, 6
    and ebx, 00111111b
    or ebx, 10000000b
    mov [edi+1], bl
    or eax, 11000000b
    mov [edi], al
    add edi, 2
    jmp iterate
   case1: ; "this is last to save a jmp at the end (common case)"
    mov [edi], al
    inc edi
   iterate:
    dec chars
    jns looptop  ; when 0 decrements to -1 drop through
   exit_ret:
    // computer "chars processed" out parameter
    mov eax, esi
    sub eax, input
    shr eax, 1  ;"number of two-byte chars"
    mov esi, chars_processed
    mov [esi], eax
    // compute return value
    mov eax, edi
    sub eax, output
    // clean up and return
    pop ebx
    pop edi
    pop esi
    leave
    ret 20
    
   surrogate_pair:
    // if this is a LOW surrogate or if there are no more chars to read, note as bad char.
    
    // ...
    // completed USC character in eax
    jmp process_char

   will_not_fit:
    // back up input pointer, adjust return values
    sub esi,2
    cmp eax,0ffffh
    jbe exit_ret
    sub esi,2  ;"for surrogate pair, back up a second value"
    // hmm... won't work for SUB's in some error states.
    // well, maybe it will if I'm careful. Every individual bad code generates a fffd.
    jmp exit_ret
    }
 }
 
/* /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

}
ENDWRAP



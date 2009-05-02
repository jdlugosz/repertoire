// The Repertoire Project copyright 1998 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\thread.h
// Revision: public build 4, shipped on 29-Aug-98

#pragma once

#include "classics\common.h"
#include "ratwin\tasking\thread.h"

// Note:  need to encapsulate thread type, and define a ratwin specialized form.
// For now, just using HANDLE.

STARTWRAP
namespace classics {

template <typename T>
struct dummy {
   static ulong __stdcall launch_thread_helper (void* raw)
    {
    T* p= static_cast<T*>(raw);
    p->start();
    return 0;
    }
   };

template <typename T>
ratwin::types::HANDLE launch_thread (T& x)
 {
 ulong id;
 ratwin::tasking::THREAD_START_ROUTINE start= &dummy<T>::launch_thread_helper;
 return ratwin::tasking::CreateThread (0, start, &x, 0, id);
 }


} // end of classics
ENDWRAP





// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: classics\thread.h
// Revision: public build 9, shipped on 18-Oct-2006

#pragma once

#include "classics\common.h"
#include "ratwin\tasking\thread.h"

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
ratwin::types::Thread_HANDLE launch_thread (T& x)
 {
 ulong id;
 ratwin::tasking::THREAD_START_ROUTINE start= &dummy<T>::launch_thread_helper;
 return ratwin::tasking::CreateThread (0, start, &x, 0, id);
 }


} // end of classics
ENDWRAP





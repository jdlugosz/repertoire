// The Repertoire Project copyright 1999 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: tomahawk\global.cpp
// Revision: public build 5, shipped on 8-April-1999

#define TOMAHAWK_EXPORT __declspec(dllexport)
#include "tomahawk\global.h"


int __stdcall premain_hook (ratwin::types::HINSTANCE h, unsigned long Reason, void*)
 {
 if (Reason == 1/*DLL_PROCESS_ATTACH*/)
    tomahawk::module_handle= h;
 return true;
 }

extern "C" int (__stdcall* _pRawDllMain)(ratwin::types::HINSTANCE, unsigned long, void*) = &premain_hook;

namespace tomahawk {

ratwin::types::HINSTANCE module_handle;

}


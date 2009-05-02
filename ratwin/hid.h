// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\hid.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\hid.h contains globals.  Include hid=struct.h instead.
#endif

#include "ratwin\COM\GUID.h"
#include "ratwin\hid=struct.h"

extern "C" {
__declspec(dllimport) void __stdcall HidD_GetHidGuid (void*);


__declspec(dllimport)
void*
__stdcall
SetupDiGetClassDevsA(
    const void* ClassGuid,
    const void*  Enumerator,
    void*   hwndParent,
    unsigned long  Flags
    );

__declspec(dllimport)
void*
__stdcall
SetupDiGetClassDevsW(
    const void* ClassGuid,
    const void* Enumerator,
    void*   hwndParent,
    unsigned long  Flags
    );

__declspec(dllimport)
unsigned long
__stdcall
SetupDiEnumDeviceInterfaces(
    void*                  DeviceInfoSet,
    void*          DeviceInfoData,
    const void*                    InterfaceClassGuid,
    unsigned long                     MemberIndex,
    void* DeviceInterfaceData
    );

__declspec(dllimport)
unsigned long
__stdcall
SetupDiGetDeviceInterfaceDetailA(
    void* DeviceInfoSet,
    const void*          DeviceInterfaceData,
    void* DeviceInterfaceDetailData,
    unsigned long                              DeviceInterfaceDetailDataSize,
    unsigned long*                             RequiredSize,
    void*                   DeviceInfoData
    );

__declspec(dllimport)
unsigned long
__stdcall
SetupDiGetDeviceInterfaceDetailW(
    void* DeviceInfoSet,
    const void*          DeviceInterfaceData,
    void* DeviceInterfaceDetailData,
    unsigned long                              DeviceInterfaceDetailDataSize,
    unsigned long*                             RequiredSize,
    void*                   DeviceInfoData
    );


__declspec(dllimport)
unsigned long
__stdcall
HidD_GetAttributes (void*, void*);
}


STARTWRAP
namespace ratwin {

inline
DevInfo_HANDLE SetupDiGetClassDevs (const _GUID& guid, const char* enumerator, types::HWND parent, unsigned long flags)
 {
 return reinterpret_cast<DevInfo_HANDLE>( ::SetupDiGetClassDevsA (&guid, enumerator, parent, flags) );
 }

inline
DevInfo_HANDLE SetupDiGetClassDevs (const _GUID& guid, const wchar_t* enumerator, types::HWND parent, unsigned long flags)
 {
 return reinterpret_cast<DevInfo_HANDLE>( ::SetupDiGetClassDevsW (&guid, enumerator, parent, flags) );
 }


inline
bool SetupDiEnumDeviceInterfaces (DevInfo_HANDLE DeviceInfoSet, const _GUID& guid, int index, SP_DEVICE_INTERFACE_DATA& DeviceInterfaceData)
 {
 return ::SetupDiEnumDeviceInterfaces (DeviceInfoSet, 0, &guid, index, &DeviceInterfaceData);
 }

inline
bool SetupDiGetDeviceInterfaceDetail (DevInfo_HANDLE DeviceInfoSet, SP_DEVICE_INTERFACE_DATA& DeviceInterfaceData, SP_DEVICE_INTERFACE_DETAIL_DATA<wchar_t>* DeviceInterfaceDetailData,
   unsigned long DeviceInterfaceDetailDataSize, unsigned long* RequiredSize)
 {
 return ::SetupDiGetDeviceInterfaceDetailW (DeviceInfoSet, &DeviceInterfaceData, DeviceInterfaceDetailData, DeviceInterfaceDetailDataSize, RequiredSize, 0);
 }

inline
bool SetupDiGetDeviceInterfaceDetail (DevInfo_HANDLE DeviceInfoSet, SP_DEVICE_INTERFACE_DATA& DeviceInterfaceData, SP_DEVICE_INTERFACE_DETAIL_DATA<char>* DeviceInterfaceDetailData,
   unsigned long DeviceInterfaceDetailDataSize, unsigned long* RequiredSize)
 {
 return ::SetupDiGetDeviceInterfaceDetailA (DeviceInfoSet, &DeviceInterfaceData, DeviceInterfaceDetailData, DeviceInterfaceDetailDataSize, RequiredSize, 0);
 }



namespace Hid {

inline ratwin::GUID GetHidGuid()
 {
 _GUID retval;
 HidD_GetHidGuid (&retval);
 return retval;
 }

inline bool GetAttributes (ratwin::types::HANDLE HidDeviceObject,    ATTRIBUTES& Attributes)
 {
 return ::HidD_GetAttributes (HidDeviceObject, &Attributes);
 }

}}
ENDWRAP


// The Repertoire Project copyright 2006 by John M. Dlugosz : see <http://www.dlugosz.com/Repertoire/>
// File: ratwin\printer\driver.h
// Revision: public build 8, shipped on 11-July-2006

#pragma once
#if defined RATWIN_NoGlobals
   #error ratwin\driver.h contains globals.
#endif

#include "ratwin\base.h"

extern "C" {
__declspec(dllimport) int __stdcall GetPrinterDriverDirectoryA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned, void*, int, int*);
__declspec(dllimport) int __stdcall GetPrinterDriverDirectoryW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned, void*, int, int*);
__declspec(dllimport) int __stdcall GetPrintProcessorDirectoryA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned, void*, int, int*);
__declspec(dllimport) int __stdcall GetPrintProcessorDirectoryW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, unsigned, void*, int, int*);
__declspec(dllimport) int __stdcall AddPrintProcessorA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall AddPrintProcessorW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32);
__declspec(dllimport) int __stdcall EnumPrintProcessorsA (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int, void*, int, void*, void*);
__declspec(dllimport) int __stdcall EnumPrintProcessorsW (Dlugosz::ratwin::arg::carg32, Dlugosz::ratwin::arg::carg32, int, void*, int, void*, void*);
__declspec(dllimport) int __stdcall AddPrinterDriverA (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall AddPrinterDriverW (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall AddMonitorA (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall AddMonitorW (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall DeleteMonitorA (Dlugosz::ratwin::arg::carg32, const char*, const char*);
__declspec(dllimport) int __stdcall DeleteMonitorW (Dlugosz::ratwin::arg::carg32, const wchar_t*, const wchar_t*);
__declspec(dllimport) int __stdcall AddPrinterA (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall AddPrinterW (Dlugosz::ratwin::arg::carg32, int, const void*);
__declspec(dllimport) int __stdcall EnumPortsA (Dlugosz::ratwin::arg::carg32, unsigned, void*, unsigned, int*, int*);
__declspec(dllimport) int __stdcall EnumPortsW (Dlugosz::ratwin::arg::carg32, unsigned, void*, unsigned, int*, int*);
}


STARTWRAP
namespace ratwin {


// Note:  Under NT, the ANSI form returns a much larger value for "needed" than is actually
// used by the result string.  So truncate the result at the '\0' instead of using this length.

inline bool
GetPrinterDriverDirectory (const char* name, const char* environment, char* result, int bufsize, int& needed)
 {
 return ::GetPrinterDriverDirectoryA (reinterpret_cast<arg::carg32>(name), reinterpret_cast<arg::carg32>(environment), 1, result, bufsize, &needed);
 }
 
inline bool
GetPrinterDriverDirectory (const wchar_t* name, const wchar_t* environment, wchar_t* result, int bufsize, int& needed)
 {
 return ::GetPrinterDriverDirectoryW (reinterpret_cast<arg::carg32>(name), reinterpret_cast<arg::carg32>(environment), 1, result, bufsize, &needed);
 }

inline bool
GetPrintProcessorDirectory (const char* name, const char* environment, char* result, int bufsize, int& needed)
 {
 return ::GetPrintProcessorDirectoryA (reinterpret_cast<arg::carg32>(name), reinterpret_cast<arg::carg32>(environment), 1, result, bufsize, &needed);
 }
 
inline bool
GetPrintProcessorDirectory (const wchar_t* name, const wchar_t* environment, wchar_t* result, int bufsize, int& needed)
 {
 return ::GetPrintProcessorDirectoryW (reinterpret_cast<arg::carg32>(name), reinterpret_cast<arg::carg32>(environment), 1, result, bufsize, &needed);
 }
 
inline bool
AddPrintProcessor (const wchar_t* server_name, const wchar_t* environment_name, const wchar_t* filename, const wchar_t* print_processor_name)
 {
 return ::AddPrintProcessorW (reinterpret_cast<arg::carg32>(server_name), reinterpret_cast<arg::carg32>(environment_name), reinterpret_cast<arg::carg32>(filename), reinterpret_cast<arg::carg32>(print_processor_name));
 }
 
inline bool
AddPrintProcessor (const char* server_name, const char* environment_name, const char* filename, const char* print_processor_name)
 {
 return ::AddPrintProcessorA (reinterpret_cast<arg::carg32>(server_name), reinterpret_cast<arg::carg32>(environment_name), reinterpret_cast<arg::carg32>(filename), reinterpret_cast<arg::carg32>(print_processor_name));
 }
 

template <typename CharType>
struct DRIVER_INFO_2 {
   unsigned long Version;  //0:Win9x, 1:NT 3.51, 2:NT 4, 3:Win 2000
   const CharType* Name;
   const CharType* Environment;
   const CharType* DriverPath;
   const CharType* DataFile;
   const CharType* ConfigFile;
   };

template <typename CharType>
struct DRIVER_INFO_3 {
   unsigned long Version;  //0:Win9x, 1:NT 3.51, 2:NT 4, 3:Win 2000
   const CharType* Name;
   const CharType* Environment;
   const CharType* DriverPath;
   const CharType* DataFile;
   const CharType* ConfigFile;
   const CharType* HelpFile;
   const CharType* DependantFiles;
   const CharType* MonitorName;
   const CharType* DefaultDataType;
   };

inline bool
AddPrinterDriver (const wchar_t* Name, const DRIVER_INFO_2<wchar_t>& info)
 {
 return ::AddPrinterDriverW (reinterpret_cast<arg::carg32>(Name), 2, &info);
 }

inline bool
AddPrinterDriver (const char* Name, const DRIVER_INFO_2<char>& info)
 {
 return ::AddPrinterDriverA (reinterpret_cast<arg::carg32>(Name), 2, &info);
 }

inline bool
AddPrinterDriver (const wchar_t* Name, const DRIVER_INFO_3<wchar_t>& info)
 {
 return ::AddPrinterDriverW (reinterpret_cast<arg::carg32>(Name), 3, &info);
 }

inline bool
AddPrinterDriver (const char* Name, const DRIVER_INFO_3<char>& info)
 {
 return ::AddPrinterDriverA (reinterpret_cast<arg::carg32>(Name), 3, &info);
 }


inline bool
EnumPrintProcessors (const wchar_t* server_name, const wchar_t* environment, wchar_t** results, int results_size_in_bytes, int& bytes_needed, int& elements_returned)
 {
 return ::EnumPrintProcessorsW (reinterpret_cast<arg::carg32>(server_name), reinterpret_cast<arg::carg32>(environment), 1, results, results_size_in_bytes, &bytes_needed, &elements_returned);
 }


inline bool
EnumPrintProcessors (const char* server_name, const char* environment, char** results, int results_size_in_bytes, int& bytes_needed, int& elements_returned)
 {
 return ::EnumPrintProcessorsA (reinterpret_cast<arg::carg32>(server_name), reinterpret_cast<arg::carg32>(environment), 1, results, results_size_in_bytes, &bytes_needed, &elements_returned);
 }


template<typename CharType>
struct MONITOR_INFO_2 {
   const CharType* Name;
   const CharType* Environment;
   const CharType* DLLName;
   };

inline bool
AddMonitor (const char* server_name, const MONITOR_INFO_2<char>& info)
 {
 return ::AddMonitorA (reinterpret_cast<arg::carg32>(server_name), 2, &info);
 }
 
inline bool
AddMonitor (const wchar_t* server_name, const MONITOR_INFO_2<wchar_t>& info)
 {
 return ::AddMonitorW (reinterpret_cast<arg::carg32>(server_name), 2, &info);
 }

inline bool
DeleteMonitor (const wchar_t* server_name, const wchar_t* environment, const wchar_t* monitor)
 {
 return ::DeleteMonitorW (reinterpret_cast<arg::carg32>(server_name), environment, monitor);
 }

inline bool
DeleteMonitor (const char* server_name, const char* environment, const char* monitor)
 {
 return ::DeleteMonitorA (reinterpret_cast<arg::carg32>(server_name), environment, monitor);
 }

struct DEVMODE;

template<typename CharType>
struct PRINTER_INFO_2 {
   const CharType* ServerName; 
   const CharType* PrinterName; 
   const CharType* ShareName; 
   const CharType* PortName; 
   const CharType* DriverName; 
   const CharType* Comment; 
   const CharType* Location; 
   const DEVMODE* DevMode; 
   const CharType* SepFile; 
   const CharType* PrintProcessor; 
   const CharType* Datatype; 
   const CharType* Parameters; 
   const void* SecurityDescriptor; 
   unsigned Attributes; 
   unsigned Priority; 
   unsigned DefaultPriority; 
   unsigned StartTime; 
   unsigned UntilTime; 
   unsigned Status; 
   unsigned cJobs; 
   unsigned AveragePPM; 
   };

types::HANDLE AddPrinter (const wchar_t* server_name, const PRINTER_INFO_2<wchar_t>& info)
 {
 return reinterpret_cast<types::HANDLE>( ::AddPrinterW (reinterpret_cast<arg::carg32>(server_name), 2, &info) );
 }

types::HANDLE AddPrinter (const char* server_name, const PRINTER_INFO_2<char>& info)
 {
 return reinterpret_cast<types::HANDLE>( ::AddPrinterA (reinterpret_cast<arg::carg32>(server_name), 2, &info) );
 }

template <typename CharType>
struct PORT_INFO_2 { 
   const CharType* PortName; 
   const CharType* MonitorName;
   const CharType* Description; 
   unsigned PortType;
   unsigned Reserved; 
   };

bool EnumPorts (const char* server_name, int level, void* buffer, int bufsize, int&needed_out, int&returned_out)
 {
 return ::EnumPortsA (reinterpret_cast<arg::carg32>(server_name), level, buffer, bufsize, &needed_out, &returned_out);
 }

bool EnumPorts (const wchar_t* server_name, int level, void* buffer, int bufsize, int&needed_out, int&returned_out)
 {
 return ::EnumPortsW (reinterpret_cast<arg::carg32>(server_name), level, buffer, bufsize, &needed_out, &returned_out);
 }

} //end namespace ratwin
ENDWRAP


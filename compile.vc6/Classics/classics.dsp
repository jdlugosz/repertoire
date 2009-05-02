# Microsoft Developer Studio Project File - Name="classics" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=classics - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "classics.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "classics.mak" CFG="classics - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "classics - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "classics - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/repertoire/classics", DAAAAAAA"
# PROP Scc_LocalPath "..\..\classics"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "classics - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zi /Ot /Oi /Oy /Ob1 /I "..\.." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /Ox /YX
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib advapi32.lib ole32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Release/Dlugosz Repertoire Classics.vc6{pb6+}.dll"

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir "."
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir "."
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /c
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib advapi32.lib ole32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"..\Debug/Dlugosz Repertoire Classics.vc6.debug{pb6+}.dll"

!ENDIF 

# Begin Target

# Name "classics - Win32 Release"
# Name "classics - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\classics\APC_server.cpp
DEP_CPP_APC_S=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\APC_server.h"\
	"..\..\classics\command_object.h"\
	"..\..\classics\common.h"\
	"..\..\classics\new.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\thread.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\thread.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\atomic_counter.cpp
DEP_CPP_ATOMI=\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\portability.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\chain.cpp
DEP_CPP_CHAIN=\
	"..\..\classics\chain.h"\
	"..\..\classics\common.h"\
	"..\..\classics\portability.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\closure.cpp
DEP_CPP_CLOSU=\
	"..\..\classics\closure.h"\
	"..\..\classics\common.h"\
	"..\..\classics\portability.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\crc32.cpp
DEP_CPP_CRC32=\
	"..\..\classics\crc32.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\critical_section.cpp
DEP_CPP_CRITI=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\portability.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\debug.cpp
DEP_CPP_DEBUG=\
	"..\..\classics\common.h"\
	"..\..\classics\debug.h"\
	"..\..\classics\portability.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\directory_list.cpp
DEP_CPP_DIREC=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\directory_list.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\filename_t.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\misc_types.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\io\file.h"\
	"..\..\ratwin\io\file=struct.h"\
	"..\..\ratwin\io\general=struct.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\event_flag.cpp
DEP_CPP_EVENT=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\event_flag.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\classics\win_handle.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\handle.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\tasking\event.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\exception.cpp
DEP_CPP_EXCEP=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\string_marker.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\COM\factory.cpp
DEP_CPP_FACTO=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\COM\factory.h"\
	"..\..\classics\COM\server_lifetime_manager.h"\
	"..\..\classics\common.h"\
	"..\..\classics\event_flag.h"\
	"..\..\classics\portability.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\com\guid.h"\
	"..\..\ratwin\com\hresult.h"\
	"..\..\ratwin\COM\IClassFactory.h"\
	"..\..\ratwin\COM\IUnknown.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\file_factory.cpp
DEP_CPP_FILE_=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\file_factory.h"\
	"..\..\classics\filename_t.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\handle.h"\
	"..\..\ratwin\io\file.h"\
	"..\..\ratwin\io\file=struct.h"\
	"..\..\ratwin\io\general=struct.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\filename_t.cpp
DEP_CPP_FILEN=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\directory_list.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\file_factory.h"\
	"..\..\classics\filename_t.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\misc_types.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\charset.h"\
	"..\..\ratwin\handle.h"\
	"..\..\ratwin\INI_file.h"\
	"..\..\ratwin\io\file.h"\
	"..\..\ratwin\io\file=struct.h"\
	"..\..\ratwin\io\general=struct.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\fixed_memory_pool.cpp
DEP_CPP_FIXED=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\new.h"\
	"..\..\classics\portability.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\inst_count.cpp
DEP_CPP_INST_=\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\inst_count.h"\
	"..\..\classics\portability.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\MFC_CString.cpp
DEP_CPP_MFC_C=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\misc_API.cpp
DEP_CPP_MISC_=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\misc_API.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\com\guid.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\tasking\process.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\mutex.cpp
DEP_CPP_MUTEX=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\mutex.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\classics\win_handle.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\handle.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\tasking\Mutex.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\new.cpp
DEP_CPP_NEW_C=\
	"..\..\classics\common.h"\
	"..\..\classics\new.h"\
	"..\..\classics\portability.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\pointers.cpp
DEP_CPP_POINT=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\profile_timer.cpp
DEP_CPP_PROFI=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\profile_timer.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\datetime.h"\
	"..\..\ratwin\handle.h"\
	"..\..\ratwin\io\general.h"\
	"..\..\ratwin\io\general=struct.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\tasking\process.h"\
	"..\..\ratwin\tasking\thread.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\COM\prothonotary.cpp
DEP_CPP_PROTH=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\COM\prothonotary.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\misc_API.h"\
	"..\..\classics\misc_types.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\registry.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\com\guid.h"\
	"..\..\ratwin\com\hresult.h"\
	"..\..\ratwin\MessageBox.h"\
	"..\..\ratwin\registry.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\registry.cpp
DEP_CPP_REGIS=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\misc_types.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\registry.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\registry.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\COM\server_lifetime_manager.cpp
DEP_CPP_SERVE=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\COM\server_lifetime_manager.h"\
	"..\..\classics\common.h"\
	"..\..\classics\event_flag.h"\
	"..\..\classics\new.h"\
	"..\..\classics\portability.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\utilities.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\string.cpp
DEP_CPP_STRIN=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string.hpp"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\string_ios.cpp
DEP_CPP_STRING=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\string_marker.cpp
DEP_CPP_STRING_=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_marker.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\ustring.cpp
DEP_CPP_USTRI=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\flagword.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\charset.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# Begin Source File

SOURCE="..\..\classics\UTF-8.cpp"
DEP_CPP_UTF_8=\
	"..\..\classics\portability.h"\
	"..\..\classics\UTF-8.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\vararray.cpp
DEP_CPP_VARAR=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\new.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	

!IF  "$(CFG)" == "classics - Win32 Release"

# SUBTRACT CPP /Z<none>

!ELSEIF  "$(CFG)" == "classics - Win32 Debug"

# ADD CPP /Zi

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\classics\virtual_key.cpp
DEP_CPP_VIRTU=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\classics\virtual_key.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# Begin Source File

SOURCE=..\..\classics\win_handle.cpp
DEP_CPP_WIN_H=\
	"..\..\classics\2d_point.h"\
	"..\..\classics\atomic_counter.h"\
	"..\..\classics\common.h"\
	"..\..\classics\critical_section.h"\
	"..\..\classics\dynalloc_reservation.h"\
	"..\..\classics\exception.h"\
	"..\..\classics\fixed_memory_pool.h"\
	"..\..\classics\MFC_CString.h"\
	"..\..\classics\pointers.h"\
	"..\..\classics\pointers=baro.h"\
	"..\..\classics\pointers=can_handle.h"\
	"..\..\classics\pointers=casts.h"\
	"..\..\classics\pointers=const_baro.h"\
	"..\..\classics\pointers=const_handle.h"\
	"..\..\classics\pointers=cow.h"\
	"..\..\classics\pointers=handle.h"\
	"..\..\classics\pointers=infrastructure.h"\
	"..\..\classics\portability.h"\
	"..\..\classics\std_forward_declare.h"\
	"..\..\classics\string.h"\
	"..\..\classics\string_ios.h"\
	"..\..\classics\ustring.h"\
	"..\..\classics\vararray.h"\
	"..\..\classics\win_handle.h"\
	"..\..\ratwin\base.h"\
	"..\..\ratwin\tasking\basic.h"\
	"..\..\ratwin\tasking\CriticalSection=struct.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\classics\atomic_counter.h
# End Source File
# Begin Source File

SOURCE=..\..\classics\debug.h
# End Source File
# Begin Source File

SOURCE=..\..\classics\pointers.h
# End Source File
# Begin Source File

SOURCE=..\..\classics\string.h
# End Source File
# Begin Source File

SOURCE=..\..\classics\vararray.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

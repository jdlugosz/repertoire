# Microsoft Developer Studio Project File - Name="ratwin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ratwin - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ratwin.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ratwin.mak" CFG="ratwin - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ratwin - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ratwin - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/repertoire/ratwin", PAAAAAAA"
# PROP Scc_LocalPath "..\..\ratwin"
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ratwin - Win32 Release"

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
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\Release/Dlugosz Repertoire Ratwin.vc6{pb8}.dll"

!ELSEIF  "$(CFG)" == "ratwin - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /GR /GX /Zi /Od /I "..\.." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib comdlg32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"..\Debug/Dlugosz Repertoire Ratwin.vc6.debug{pb8}.dll"

!ENDIF 

# Begin Target

# Name "ratwin - Win32 Release"
# Name "ratwin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=..\..\ratwin\base.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\COM\GUID.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\tasking\thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\utilities.cpp
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\window.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=..\..\ratwin\atom.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\base.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\bitmap.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\charset.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\color.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\GDI.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\handle.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\keyboard.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\menu.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\message.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\mouse.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\resource.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\socket.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\socket2.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\text.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\tasking\thread.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\utilities.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\window.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\windowsx.h
# End Source File
# Begin Source File

SOURCE=..\..\ratwin\WM_constants.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project

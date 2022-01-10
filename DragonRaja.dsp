# Microsoft Developer Studio Project File - Name="DragonRaja" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DragonRaja - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DragonRaja.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DragonRaja.mak" CFG="DragonRaja - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DragonRaja - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DragonRaja - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/AutoPatch", IHLAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DragonRaja - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:".\exe\Dragonraja.exe"

!ELSEIF  "$(CFG)" == "DragonRaja - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x417 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /map /debug /machine:I386 /out:"C:\Program Files (x86)\Dragonraja Phoenix\DragonRaja.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DragonRaja - Win32 Release"
# Name "DragonRaja - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DebugLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DragonRaja.cpp
# End Source File
# Begin Source File

SOURCE=.\DragonRaja.rc
# End Source File
# Begin Source File

SOURCE=.\DragonRajaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FTPMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\SmallWindow1.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DebugLog.h
# End Source File
# Begin Source File

SOURCE=.\DragonRaja.h
# End Source File
# Begin Source File

SOURCE=.\DragonRajaDlg.h
# End Source File
# Begin Source File

SOURCE=.\FTPMgr.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerSelect.h
# End Source File
# Begin Source File

SOURCE=.\SmallWindow1.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\b_cancel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_home.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_newid.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\b_update.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\CN DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\CN DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\CN NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\CN NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\CN UP.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\CN UP.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\CN_DW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\CN_NO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\CN_UP.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Now Connect\Connect.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Now Connect\Connect2.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\DownLoad\DownLoad BG.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\DragonRaja.ico
# End Source File
# Begin Source File

SOURCE=.\res_korea\DragonRaja.ico
# End Source File
# Begin Source File

SOURCE=".\res\HP DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\HP DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\HP NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\HP NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\HP UP.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\HP UP.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\NI_DN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\NI_NO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\NI_UP.bmp
# End Source File
# Begin Source File

SOURCE=".\res\OK DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\OK DN.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\OK NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\OK NO.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\OK UP.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\OK UP.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\SelectServer BG.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ServerSelect\SelectServer BG.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\ST_DN.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\ST_NO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\ST_UP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\UD_DW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\UD_NO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DownLoad\UD_UP.bmp
# End Source File
# End Group
# End Target
# End Project


SET VersionFile_In="%1"
SET VersionFile_Out="%2"
SET VersionFile_tmp="version.h.tmp"
SET VersionFile_tmp2="version.h.tmp2"

if exist Version_Path.bat (
	call Version_Path.bat
)

if "%APP_SubWCRev%"=="" (
	SET APP_SubWCRev=D:\Program Files\TortoiseSVN\bin\SubWCRev.exe
)

if %VersionFile_In% == "" (
	echo no input version file
	goto exit
)

if %VersionFile_tmp% == "" (
	echo no output version header file
	goto exit
)

REM �]�w�Ҧ��ѨϥΪ̳]�w�������Ѽ�
call %VersionFile_In%

SET UseSvnBuildNumber_org=%UseSvnBuildNumber%

REM �Y�q���S���w��TortoiseSVN�A�h���ϥ�UseSvnBuildNumber
if NOT EXIST "%APP_SubWCRev%" (
	if "%UseSvnBuildNumber_org%" == "1" (
		echo Version_Create: "%APP_SubWCRev%" NOT EXIST. Please Install TortoiseSVN or setup TortoiseSVN PATH in Version_PreBuildEvent.bat>& 2
		echo Version_Create: %VersionFile_Out% Can not use [SET UseSvnBuildNumber=1] >& 2
	)
	SET UseSvnBuildNumber=
)

REM �Y���ؿ��S��.svn��svn�u�@�ؿ��A�h���ϥ�UseSvnBuildNumber
if NOT EXIST "%Svn_WorkingCopyPath%\.svn" (
	if "%UseSvnBuildNumber_org%" == "1" (
		echo Version_Create: "%Svn_WorkingCopyPath%\.svn" NOT EXIST. Please use svn to check out this project.>& 2
		echo Version_Create: %VersionFile_Out% Can not use [SET UseSvnBuildNumber=1] >& 2
	)
	SET UseSvnBuildNumber=
)

if "%UseSvnBuildNumber%" == "1" (
	SET BuildNumber=$WCREV$
	SET BuildNumber_Date=$WCDATE$
)

REM ���� version.h���Ȧs��

REM echo #pragma once > %VersionFile_tmp%

echo //Generated from Version_Create.bat %VersionFile_In% >> %VersionFile_tmp%


REM echo #pragma once > %Update_File_Path%
REM �����������X��update.txt
if exist %Update_File_Path% (
	del /f /q %Update_File_Path%
)
echo %MajorVersion%.%MinorVersion%.%PatchLevel%. > %Update_File_Path%

echo // >> %VersionFile_tmp%
echo #define FILEVER            %MajorVersion%,%MinorVersion%,%PatchLevel%,%BuildNumber% >> %VersionFile_tmp%
echo #define FILEVER_STRA       "%MajorVersion%,%MinorVersion%,%PatchLevel%,%BuildNumber%\0" >> %VersionFile_tmp%
echo #define FILEVER_DOT_STRA       "%MajorVersion%.%MinorVersion%.%PatchLevel%.%BuildNumber%\0" >> %VersionFile_tmp%
echo #define FILEVER_DOT_STRW       L"%MajorVersion%.%MinorVersion%.%PatchLevel%.%BuildNumber%\0" >> %VersionFile_tmp%

echo // >> %VersionFile_tmp%
echo #define PRODUCTVER         %MajorVersion%,%MinorVersion%,%PatchLevel%,%BuildNumber% >> %VersionFile_tmp%
echo #define PRODUCTVER_STRA    "%MajorVersion%,%MinorVersion%,%PatchLevel%,%BuildNumber%\0" >> %VersionFile_tmp%
echo #define PRODUCTVER_DOT_STRA    "%MajorVersion%.%MinorVersion%.%PatchLevel%.%BuildNumber%\0" >> %VersionFile_tmp%
echo #define PRODUCTVER_DOT_STRW    L"%MajorVersion%.%MinorVersion%.%PatchLevel%.%BuildNumber%\0" >> %VersionFile_tmp%

echo // >> %VersionFile_tmp%
echo #define Version_Major %MajorVersion% >> %VersionFile_tmp%
echo #define Version_Minor %MinorVersion% >> %VersionFile_tmp%
echo #define Version_PatchLevel %PatchLevel% >> %VersionFile_tmp%
echo #define Version_BuildNumber   %BuildNumber% >> %VersionFile_tmp%

echo // >> %VersionFile_tmp%
echo #define Version_RevDateA   "%BuildNumber_Date%" >> %VersionFile_tmp%
echo #define Version_RevDateW   "%BuildNumber_Date%" >> %VersionFile_tmp%

echo // >> %VersionFile_tmp%
if "%UseSvnBuildNumber%" == "1" (
	echo #define Version_UseSvnBuildNumber   1 >> %VersionFile_tmp%
) else (
	echo #define Version_UseSvnBuildNumber   0 >> %VersionFile_tmp%
)

echo // >> %VersionFile_tmp%
echo #define Version_CompanyNameA   %CompanyName% >> %VersionFile_tmp%
echo #define Version_CompanyNameW   L%CompanyName% >> %VersionFile_tmp%
echo #define Version_ProductNameA   %ProductName% >> %VersionFile_tmp%
echo #define Version_ProductNameW   L%ProductName% >> %VersionFile_tmp%
echo #define Version_InternalNameA   %InternalName% >> %VersionFile_tmp%
echo #define Version_InternalNameW   L%InternalName% >> %VersionFile_tmp%
echo #define Version_LegalCopyrightA   %LegalCopyright% >> %VersionFile_tmp%
echo #define Version_LegalCopyrightW   L%LegalCopyright% >> %VersionFile_tmp%
echo #define Version_OriginalFilenameA   %OriginalFilename% >> %VersionFile_tmp%
echo #define Version_OriginalFilenameW   L%OriginalFilename% >> %VersionFile_tmp%
echo #define Version_FileDescriptionA   %FileDescription% >> %VersionFile_tmp%
echo #define Version_FileDescriptionW   L%FileDescription% >> %VersionFile_tmp%
echo #define Version_CommentsA   %Comments% >> %VersionFile_tmp%
echo #define Version_CommentsW   L%Comments% >> %VersionFile_tmp%


REM �Y�O�ϥ�SVN  �h�b�o�̰���SubWCRev.exe�Ө��N$WCREV$ $WCDATE$ �o�ǰѼ�
if "%UseSvnBuildNumber%" == "1" (
	"%APP_SubWCRev%" %Svn_WorkingCopyPath% %VersionFile_tmp% %VersionFile_tmp2%
REM	if "%ERRORLEVEL%"=="0" (
		copy /y %VersionFile_tmp2% %VersionFile_tmp%
REM	)
)

REM ���s��version.h �A�Y�O���@�ˡA�~copy�L�h
fc %VersionFile_tmp% %VersionFile_Out% 2>&1
if not "%ERRORLEVEL%"=="0" (
	copy /y %VersionFile_tmp% %VersionFile_Out%
)

:exit

if exist %VersionFile_tmp% (
	del /f /q %VersionFile_tmp%
)

if exist %VersionFile_tmp2% (
	del /f /q %VersionFile_tmp2%
)


SET MajorVersion=
SET MinorVersion=
SET PatchLevel=
SET BuildNumber=
SET CompanyName=
SET ProductName=
SET InternalName=
SET OriginalFilename=
SET FileDescription=
SET LegalCopyright=
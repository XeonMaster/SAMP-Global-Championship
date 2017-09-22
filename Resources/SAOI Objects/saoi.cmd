@ECHO OFF
TITLE SAOI File Generator v1.6.0
COLOR 9F

IF EXIST "%CD%\samp_core\server_log.txt" DEL /Q /A "%CD%\samp_core\server_log.txt"

SET PATH=%PATH%;%CD%\samp_core\pawno

ECHO.
ECHO SAOI File Generator v1.6.0
ECHO.

:FILE_SET
SET /P FILE=File Name: 

IF NOT EXIST "%CD%\pawn_code\%FILE%" (
	ECHO File \pawn_code\%FILE% not exist
	GOTO :FILE_SET
)

CALL :FILE_STORE "%FILE%"

SET /P AUTHOR=Author: 
SET /P VERSION=Version: 
SET /P DESCRIPTION=Description: 
ECHO.
ECHO Create executable amx file.
ECHO.

ECHO //SAOI Meta > "%CD%\saoi_fs\tmp_fs.raw"
ECHO #define MY_SAOI_FILE	"%FILE_NAME%" >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO #define SAOI_AUTHOR	"%AUTHOR%" >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO #define SAOI_VERSION	"%VERSION%" >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO #define SAOI_DESCRIPTION	"%DESCRIPTION%" >> "%CD%\saoi_fs\tmp_fs.raw"

TYPE "%CD%\saoi_fs\generator_start" >> "%CD%\saoi_fs\tmp_fs.raw"

ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"
ECHO PutObjectHere(){ >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"
ECHO new playerid; >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"
TYPE "%CD%\pawn_code\%FILE%" >> "%CD%\saoi_fs\tmp_fs.raw" 
ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"
ECHO #pragma unused playerid >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"
ECHO } >> "%CD%\saoi_fs\tmp_fs.raw"
ECHO.>> "%CD%\saoi_fs\tmp_fs.raw"

TYPE "%CD%\saoi_fs\generator_end" >> "%CD%\saoi_fs\tmp_fs.raw"

"%CD%\samp_core\pawno\pawncc.exe" "%CD%\saoi_fs\tmp_fs.raw" -i"%CD%/samp_core/pawno/include" -(+ -;+

IF NOT EXIST "%CD%\tmp_fs.amx" (
	ECHO.
	ECHO Compile Error: Please write correct pawn code!
	ECHO.
	PAUSE > nul
	GOTO ON_EXIT
)

MOVE /Y "%CD%\tmp_fs.amx" "%CD%\samp_core\filterscripts\generator.amx" > nul
TITLE Create %FILE_NAME%
ECHO.
ECHO Run SA:MP Server.
ECHO.
CD "%CD%\samp_core" 
samp-server.exe
CD ..
IF NOT EXIST "%CD%\samp_core\scriptfiles\%FILE_NAME%" (
	ECHO.
	ECHO Error converting file
) ELSE (
	ECHO.
	ECHO Conversion completed successfully
	REM MOVE /Y "%CD%\samp_core\scriptfiles\%FILE_NAME%" "%CD%\%FILE_NAME%" > nul
	MOVE /Y "%CD%\samp_core\scriptfiles\%FILE_NAME%" "%CD%\..\..\scriptfiles\SAOI\%FILE_NAME%" > nul
)
ECHO.
ECHO The End
ECHO. 
PAUSE > nul
GOTO ON_EXIT

:FILE_STORE
SET FILE_NAME=%~n1.saoi
GOTO :eof

:ON_EXIT
IF EXIST "%CD%\saoi_fs\tmp_fs.raw" DEL /Q /A "%CD%\saoi_fs\tmp_fs.raw"
IF EXIST "%CD%\samp_core\filterscripts\generator.amx" DEL /Q /A "%CD%\samp_core\filterscripts\generator.amx"
GOTO :eof

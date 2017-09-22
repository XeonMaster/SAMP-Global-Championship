@ECHO OFF

COLOR 9F
SET PATH=%PATH%;%CD%\samp_core\pawno

SET i=0
SET total=0

IF EXIST "%CD%\saoi.log" DEL /Q /A "%CD%\saoi.log"

FOR /F "tokens=*" %%s IN (object.lst) DO CALL :GET_SAOI %%s

PAUSE
GOTO :eof

:GET_SAOI
IF EXIST "%CD%\samp_core\server_log.txt" DEL /Q /A "%CD%\samp_core\server_log.txt"

IF "%~1" == "" GOTO :eof
IF "%~2" == "" GOTO :eof
IF "%~3" == "" GOTO :eof

CALL :_TOTAL
TITLE Convert: %~1 (%i%/%total%)

SET FILE=%~1

IF NOT EXIST "%CD%\pawn_code\%FILE%" (
	ECHO File not exist %FILE% >> "%CD%\saoi.log"
	GOTO :eof
)

CALL :FILE_STORE "%FILE%"

SET AUTHOR=%~2
SET VERSION=%~3
SET DESCRIPTION=%~4

ECHO Create file %FILE% >> "%CD%\saoi.log"
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
ECHO.
ECHO Run SA:MP Server.
ECHO.
CD "%CD%\samp_core" 
samp-server.exe
CD ..
IF EXIST "%CD%\samp_core\scriptfiles\%FILE_NAME%" CALL :_UPP
IF NOT EXIST "%CD%\samp_core\scriptfiles\%FILE_NAME%" (
	ECHO.
	ECHO Error converting file
	ECHO Error converting file %FILE% >> "%CD%\saoi.log"
) ELSE (
	ECHO.
	ECHO Conversion completed successfully
	REM MOVE /Y "%CD%\samp_core\scriptfiles\%FILE_NAME%" "%CD%\%FILE_NAME%" > nul
	MOVE /Y "%CD%\samp_core\scriptfiles\%FILE_NAME%" "%CD%\..\..\scriptfiles\SAOI\%FILE_NAME%" > nul
	ECHO Conversion successfully %FILE% >> "%CD%\saoi.log"
	ECHO. >> "%CD%\saoi.log"
)

ECHO.
ECHO The End
ECHO. 
TITLE Convert: %~1 (%i%/%total%)
GOTO ON_EXIT

:_UPP
SET /A i=%i%+1
GOTO :eof

:_TOTAL
SET /A total=%total%+1
GOTO :eof

:FILE_STORE
SET FILE_NAME=%~n1.saoi
GOTO :eof

:ON_EXIT
IF EXIST "%CD%\saoi_fs\tmp_fs.raw" DEL /Q /A "%CD%\saoi_fs\tmp_fs.raw"
IF EXIST "%CD%\samp_core\filterscripts\generator.amx" DEL /Q /A "%CD%\samp_core\filterscripts\generator.amx"
GOTO :eof

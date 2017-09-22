@ECHO OFF
SET i=0
SET c=0
COLOR 9F
ECHO Starting sequence...

SET PATH=%PATH%;%CD%\..\gamemodes
REM FOR /F "tokens=*" %%s IN ('ProtVar 5') DO SET ProtVar=%%s
REM IF NOT DEFINED ProtVar ECHO ProtVar Error ! & PAUSE > nul & EXIT

REM echo /* Config */ > conf.inc
REM echo #define ENABLE_PROTECTION_VARIABLES >> conf.inc
REM echo #define ProtVar::	p%ProtVar%v >> conf.inc

CD .
FOR /F "tokens=*" %%G IN ('DIR /B /A "*.pwn"') DO (
	ECHO Building %%G
	..\pawno\pawncc.exe -i"..\pawno\include" -i"..\pawno\include\samp" -i"..\pawno\include\plugin" -i"..\pawno\include\SAOI" %%G  -(+ -;+ -r
	CALL :MOV "%%G"
	CALL :AAA
)
ECHO Sequence completed!
ECHO Compiled %c%/%i% script
TITLE Compiled %c%/%i% script
REM IF EXIST "%CD%\conf.inc" DEL /Q /A "%CD%\conf.inc"
pause
GOTO :eof

:AAA
SET /A i=%i%+1
GOTO :eof

:BBB
SET /A c=%c%+1
GOTO :eof

:MOV
IF EXIST "%~n1.amx" (
	CALL :BBB
	MOVE /Y "%CD%\%~n1.amx" "%CD%\..\filterscripts\%~n1.amx" > nul
)
IF EXIST "%~n1.xml" DEL /Q /A "%~n1.xml"
GOTO :eof
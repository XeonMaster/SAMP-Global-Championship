@echo off
TITLE %~n0
COLOR 9F
time /T

REM setlocal enabledelayedexpansion
FOR /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set DATE=%%c-%%a-%%b)
FOR /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set TIME=%%a:%%b)

REM FOR /F "tokens=*" %%s IN ('ProtVar 5') DO SET ProtVar=%%s
REM IF NOT DEFINED ProtVar ECHO ProtVar Error ! & PAUSE > nul & EXIT
FOR /F "tokens=*" %%s IN (revision) DO SET REVISION=%%s
FOR /F "tokens=*" %%s IN (version.txt) DO SET VERSION=%%s
SET /A REVISION=%REVISION%+1

set USER=%username%
set WHERE=%userdomain%

echo /* Version */ > ../pawno/include/main/meta/version.inc

echo #define GMVERSION "%VERSION%r%REVISION%" >> ../pawno/include/main/meta/version.inc
echo #define GMCOMPILED "skompilowana %DATE% %TIME% przez %USER%@%WHERE%" >> ../pawno/include/main/meta/version.inc

REM echo #define ENABLE_PROTECTION_VARIABLES >> ../pawno/include/main/meta/version.inc
REM echo #define ProtVar::	p%ProtVar%v >> ../pawno/include/main/meta/version.inc
echo #define ProtDialog (1%RANDOM:~-1,1%%RANDOM:~-1,1%%RANDOM:~-1,1%%RANDOM:~-1,1%) >> ../pawno/include/main/meta/version.inc
REM endlocal

echo Please wait...
ECHO.
..\pawno\pawncc.exe -r -i"..\pawno\include" -i"..\pawno\include\samp" championship.pwn -(+ -;+ -d3
DEL /Q /A "..\pawno\include\main\meta\version.inc"
IF EXIST "%CD%\championship.xml" DEL /Q /A "%CD%\championship.xml" > nul
IF EXIST "%CD%\championship.amx" ECHO %REVISION% > revision
ECHO.
time /T
pause
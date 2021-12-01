@echo off

set /p year="Enter year: "
set /p day="Enter day: "

setlocal EnableDelayedExpansion
for /L %%i in (%day%,1,%day%) do (
    set "dayNumber=0%%i"
    echo Downloading Day !dayNumber:~-2!...
    aocd %%i %year% > Day!dayNumber:~-2!.txt
)

pause
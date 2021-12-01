@echo off
set year = 2020
setlocal EnableDelayedExpansion
for /l %%i in (1,1,25) do (
    set "dayNumber=0%%i"
    echo Downloading Day !dayNumber:~-2!...
    aocd %%i %year% > Day!dayNumber:~-2!.txt
)
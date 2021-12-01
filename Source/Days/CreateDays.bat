@echo off
for /l %%a in (1,1,25) do (
    mkdir Day%%a
    cd Day%%a
    >>Day%%a.h echo #pragma once
    >>Day%%a.cpp echo #include "Day%%a.h"
    cd ..
)
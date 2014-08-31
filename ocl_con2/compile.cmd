@echo off
if exist ocl_con2.exe del ocl_con2.exe >nul
icc /Gm+ /Gd+ /O+ /B" /pmtype:pm" ocl_con2.cpp
if exist ocl_con2.exe start ocl_con2.exe

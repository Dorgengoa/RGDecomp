@echo off
rem Build + run the vtable probes with MSVC x86 (VS2019).  Output goes to .\out\
setlocal
set "PATH=%PATH:"=%"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars32.bat" >nul || exit /b 1
cd /d "%~dp0"
if not exist out mkdir out
cl /nologo /W3 /O1 /TC test_vcall.c /Foout\ /Feout\test_vcall_msvc.exe || exit /b 1
cl /nologo /W3 /O1 /EHsc test_devirt.cpp /Foout\ /Feout\test_devirt_msvc.exe || exit /b 1
out\test_vcall_msvc.exe || exit /b 1
out\test_devirt_msvc.exe || exit /b 1

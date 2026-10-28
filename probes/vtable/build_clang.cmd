@echo off
rem Build + run the vtable probes with clang (i686, MSVC target).  Output goes to .\out\
rem Needs the MSVC x86 libs for linking, so vcvars32 first.
setlocal
set "PATH=%PATH:"=%"
set "CLANG=../tools\llvm\bin\clang.exe"
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars32.bat" >nul || exit /b 1
cd /d "%~dp0"
if not exist out mkdir out
set "FLAGS=--target=i686-pc-windows-msvc -msse2 -mfpmath=sse -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks -O1 -Wall"
"%CLANG%" %FLAGS% -std=c11 test_vcall.c -o out\test_vcall_clang.exe || exit /b 1
"%CLANG%" %FLAGS% -std=c++14 -Wno-invalid-offsetof test_devirt.cpp -o out\test_devirt_clang.exe || exit /b 1
out\test_vcall_clang.exe || exit /b 1
out\test_devirt_clang.exe || exit /b 1

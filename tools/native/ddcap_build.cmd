@echo off
rem SPDX-License-Identifier: CC0-1.0
rem Build tools\native\ddcap.cpp (DXGI Desktop Duplication grab) as an x64 exe:
rem   tools\native\ddcap_build.cmd [OUT.exe]      (default out\tools\ddcap.exe)
setlocal
set "OUT=%~1"
if "%OUT%"=="" set "OUT=%~dp0..\..\out\tools\ddcap.exe"
for %%V in (BuildTools Community Enterprise) do (
  if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\%%V\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\%%V\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul 2>&1
    goto :have
  )
)
echo ddcap_build: vcvarsall.bat not found & exit /b 1
:have
for %%F in ("%OUT%") do if not exist "%%~dpF" mkdir "%%~dpF"

"../tools\llvm\bin\clang-cl.exe" /nologo /O2 /EHsc /W3 "%~dp0ddcap.cpp" /Fe:"%OUT%" /Fo:"%OUT%.obj" /link d3d11.lib dxgi.lib user32.lib || exit /b 1
echo ddcap_build: built %OUT%

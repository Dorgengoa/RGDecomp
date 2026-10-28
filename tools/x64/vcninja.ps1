# SPDX-License-Identifier: CC0-1.0
# vcninja.ps1 DIR ARCH [targets...]: vcvarsall ARCH (x86 | x64) + ninja in an existing build
# dir (re-runs CMake when ninja wants to).  Run detached for long builds:
#   Start-Process powershell -ArgumentList '-File','tools\x64\vcninja.ps1','build\x64-windows','x64' ...
param([string]$Dir, [string]$Arch, [Parameter(ValueFromRemainingArguments=$true)] $Targets)
$vc = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
$env:PATH = ($env:PATH -replace '"', '')
$env:PATH = "C:\Windows\system32;C:\Windows;C:\Program Files (x86)\Microsoft Visual Studio\Installer;" + $env:PATH
cmd /c "`"$vc`" $Arch >nul && set" | ForEach-Object { if ($_ -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] } }
$env:PATH = "../tools\llvm\bin;../tools\ninja;" + $env:PATH
& ../tools\ninja\ninja.exe -C $Dir @Targets
exit $LASTEXITCODE

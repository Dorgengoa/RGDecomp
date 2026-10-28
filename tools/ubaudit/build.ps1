<#
.SYNOPSIS
  Configure (once, or -Reconfigure) and build targets in a UB-audit build dir
  (docs/UB-AUDIT.md).  Same toolchain as tools\build.ps1 (Release, clang i686,
  Ninja), -j 4 (shared PC), plus extra cache definitions.

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\ubaudit\build.ps1 -BuildDir build\o2-i686\o1
  powershell -ExecutionPolicy Bypass -File tools\ubaudit\build.ps1 -BuildDir build\o2-i686\ubsan -Defs RG_UBSAN=ON -Targets rg-game
  powershell -ExecutionPolicy Bypass -File tools\ubaudit\build.ps1 -BuildDir build\o2-i686\o2 -Defs RG_GAME_OPT=-O2 -Targets all,rg-game
#>
param(
    [Parameter(Mandatory = $true)][string]$BuildDir,
    [string[]]$Targets = @("all", "rg-game"),
    [string[]]$Defs = @(),
    [int]$Jobs = 4,
    [string]$LlvmRoot = $(if ($env:LLVM_ROOT) { $env:LLVM_ROOT } else { "../tools\llvm" }),
    [string]$Ninja   = "../tools\ninja\ninja.exe",
    [string]$CMake   = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe",
    [switch]$Reconfigure,
    [switch]$KeepGoing
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not [System.IO.Path]::IsPathRooted($BuildDir)) { $BuildDir = Join-Path $Root $BuildDir }
$cands = @(
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat")
if (-not $env:RG_VCVARS_DONE) {
    $VcVars = $cands | Where-Object { Test-Path $_ } | Select-Object -First 1
    if (-not $VcVars) { throw "vcvarsall.bat not found" }
    $env:PATH = $env:PATH -replace '"', ''
    $dump = & cmd.exe /c "`"$VcVars`" x86 >nul 2>&1 && set"
    if ($LASTEXITCODE -ne 0) { throw "vcvarsall x86 failed" }
    foreach ($line in $dump) {
        if ($line -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] }
    }
    $env:RG_VCVARS_DONE = "1"
}
$env:PATH = "$LlvmRoot\bin;" + (Split-Path $Ninja) + ";" + $env:PATH
if ($Reconfigure -or -not (Test-Path (Join-Path $BuildDir "build.ninja"))) {
    $dargs = @($Defs | ForEach-Object { $_ -split "," } | Where-Object { $_ } | ForEach-Object { "-D$_" })
    & $CMake -S $Root -B $BuildDir -G Ninja `
        "-DCMAKE_MAKE_PROGRAM=$Ninja" `
        "-DCMAKE_TOOLCHAIN_FILE=$Root\cmake\toolchain-i686-windows-clang.cmake" `
        "-DLLVM_ROOT=$($LlvmRoot.Replace('\','/'))" `
        "-DCMAKE_BUILD_TYPE=Release" @dargs
    if ($LASTEXITCODE -ne 0) { throw "cmake configure failed" }
}
$k = @()
if ($KeepGoing) { $k = @("--", "-k", "0") }
foreach ($t in $Targets) {
    & $CMake --build $BuildDir --target $t -j $Jobs @k
    if ($LASTEXITCODE -ne 0) { throw "build of $t failed" }
}

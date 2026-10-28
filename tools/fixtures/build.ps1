<#
.SYNOPSIS
  Configure (once) and build targets in the fixtures build dir (docs/TEST-FIXTURES.md).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\fixtures\build.ps1                     # rg-game
  powershell -ExecutionPolicy Bypass -File tools\fixtures\build.ps1 -Targets rg-game,rg-savestate-tests
  powershell -ExecutionPolicy Bypass -File tools\fixtures\build.ps1 -BuildDir build\other-i686

  Same toolchain and configuration as tools\build.ps1 (Release, clang i686, Ninja).
#>
param(
    [string[]]$Targets = @("rg-game"),
    [string]$BuildDir = "",
    [string]$LlvmRoot = $(if ($env:LLVM_ROOT) { $env:LLVM_ROOT } else { "../tools\llvm" }),
    [string]$Ninja   = "../tools\ninja\ninja.exe",
    [string]$CMake   = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe",
    [string]$VcVars  = "",
    [switch]$Reconfigure   # re-run cmake configure (needed after adding/removing an override)
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not $BuildDir) { $BuildDir = Join-Path $Root "build\fixtures-i686" }
if (-not $VcVars) {
    $cands = @(
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat")
    $VcVars = $cands | Where-Object { Test-Path $_ } | Select-Object -First 1
    if (-not $VcVars) { throw "vcvarsall.bat not found; pass -VcVars" }
}
if (-not $env:RG_VCVARS_DONE) {
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
    & $CMake -S $Root -B $BuildDir -G Ninja `
        "-DCMAKE_MAKE_PROGRAM=$Ninja" `
        "-DCMAKE_TOOLCHAIN_FILE=$Root\cmake\toolchain-i686-windows-clang.cmake" `
        "-DLLVM_ROOT=$($LlvmRoot.Replace('\','/'))" `
        "-DCMAKE_BUILD_TYPE=Release"
    if ($LASTEXITCODE -ne 0) { throw "cmake configure failed" }
}
foreach ($t in $Targets) {
    & $CMake --build $BuildDir --target $t -j 4
    if ($LASTEXITCODE -ne 0) { throw "build of $t failed" }
}

<#
.SYNOPSIS
  Build the native-CPU lane's targets (docs/NATIVE-CPU.md) with a chosen VU0 mode
  (Release, clang i686, ninja -j4; the configuration of tools\fixtures\build.ps1 plus
  -DRG_VU0_MODE).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\native\vu0_build.ps1 -Mode native
  powershell -ExecutionPolicy Bypass -File tools\native\vu0_build.ps1 -Mode model -BuildDir build\nvu0m-i686
  powershell -ExecutionPolicy Bypass -File tools\native\vu0_build.ps1 -Targets rg-vu0native-tests

  -Mode (model | local | native) re-runs the configure step with -DRG_VU0_MODE=<mode>;
  without it the build dir keeps its mode (a new dir gets the CMakeLists default).
#>
param(
    [string]$Mode = "",
    [string[]]$Targets = @("rg-vu0native-tests", "rg-game"),
    [string]$BuildDir = "",
    [string]$LlvmRoot = $(if ($env:LLVM_ROOT) { $env:LLVM_ROOT } else { "../tools\llvm" }),
    [string]$Ninja   = "../tools\ninja\ninja.exe",
    [string]$CMake   = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe",
    [switch]$Reconfigure,
    [switch]$KeepGoing      # ninja -k 0: build everything that can be built
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not $BuildDir) { $BuildDir = Join-Path $Root "build\nvu0-i686" }
$Targets = @($Targets | ForEach-Object { $_ -split "," } | Where-Object { $_ })
if ($Mode -and $Mode -notin @("model", "local", "native")) { throw "-Mode must be model, local or native" }
$cands = @(
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
    "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat")
$VcVars = $cands | Where-Object { Test-Path $_ } | Select-Object -First 1
if (-not $VcVars) { throw "vcvarsall.bat not found" }
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
if ($Mode -or $Reconfigure -or -not (Test-Path (Join-Path $BuildDir "build.ninja"))) {
    $extra = @()
    if ($Mode) { $extra += "-DRG_VU0_MODE=$Mode" }
    & $CMake -S $Root -B $BuildDir -G Ninja `
        "-DCMAKE_MAKE_PROGRAM=$Ninja" `
        "-DCMAKE_TOOLCHAIN_FILE=$Root\cmake\toolchain-i686-windows-clang.cmake" `
        "-DLLVM_ROOT=$($LlvmRoot.Replace('\','/'))" `
        "-DCMAKE_BUILD_TYPE=Release" @extra
    if ($LASTEXITCODE -ne 0) { throw "cmake configure failed" }
}
foreach ($t in $Targets) {
    if ($KeepGoing) { & $CMake --build $BuildDir --target $t -j 4 -- -k 0 }
    else { & $CMake --build $BuildDir --target $t -j 4 }
    if ($LASTEXITCODE -ne 0) { throw "build of $t failed" }
}

<#
.SYNOPSIS
  Configure and build the port (i686, clang + CMake + Ninja) into build\.
  -Arch x64: the P7 x64 build (docs/X64-PLAN.md): vcvarsall x64, the x64
  toolchain, default dir build\x64-windows, game sources from the tree that
  tools/x64/derive.py writes (-X64Src, default build\x64-src).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\build.ps1            # configure + build + run smoke
  powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Clean
  powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Config RelWithDebInfo
  powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Arch x64 -X64Src build\x64-src

  Tool locations default to $env:RG_TOOLS, else <repo>\..\tools, as
  {llvm,ninja,cmake-*}; override with -LlvmRoot / -Ninja / -CMake or $env:LLVM_ROOT.
#>
param(
    [string]$Config  = "Release",
    [string]$BuildDir = "",
    [string]$LlvmRoot = "",
    [string]$Ninja   = "",
    [string]$CMake   = "",
    [string]$VcVars  = "",
    [ValidateSet("x86", "x64")] [string]$Arch = "x86",
    [string]$X64Src  = "",
    [switch]$Clean,
    [switch]$NoSmoke
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent $PSScriptRoot
$Tools = if ($env:RG_TOOLS) { $env:RG_TOOLS } else { Join-Path (Split-Path -Parent $Root) "tools" }
if (-not $LlvmRoot) { $LlvmRoot = if ($env:LLVM_ROOT) { $env:LLVM_ROOT } else { Join-Path $Tools "llvm" } }
if (-not $Ninja) { $Ninja = Join-Path $Tools "ninja\ninja.exe" }
if (-not $CMake) { $CMake = Join-Path $Tools "cmake-3.31.7-windows-x86_64\bin\cmake.exe" }
if (-not $BuildDir) {
    $BuildDir = Join-Path $Root $(if ($Arch -eq "x64") { "build\x64-windows" } else { "build\i686-windows" })
}

foreach ($t in @("$LlvmRoot\bin\clang.exe", $Ninja, $CMake)) {
    if (-not (Test-Path $t)) { throw "missing tool: $t (see docs/TOOLCHAIN.md)" }
}

# --- MSVC x86 environment (CRT + Windows SDK libs/headers for i686-pc-windows-msvc)
if (-not $VcVars) {
    $cands = @(
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat",
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat",
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvarsall.bat")
    $VcVars = $cands | Where-Object { Test-Path $_ } | Select-Object -First 1
    if (-not $VcVars) { throw "vcvarsall.bat not found; pass -VcVars" }
}
# RG_VCVARS_DONE: "1" = the x86 environment (as before), "x64" = the x64 one
$want = $(if ($Arch -eq "x86") { "1" } else { $Arch })
if ($env:RG_VCVARS_DONE -and $env:RG_VCVARS_DONE -ne $want) {
    throw "this shell already holds another vcvars environment ($env:RG_VCVARS_DONE); use a new shell for -Arch $Arch"
}
if (-not $env:RG_VCVARS_DONE) {
    # The user PATH carries embedded quotes that break vcvars' batch parsing.
    $env:PATH = $env:PATH -replace '"', ''
    $dump = & cmd.exe /c "`"$VcVars`" $Arch >nul 2>&1 && set"
    if ($LASTEXITCODE -ne 0) { throw "vcvarsall $Arch failed" }
    foreach ($line in $dump) {
        if ($line -match '^([^=]+)=(.*)$') {
            Set-Item -Path "env:$($Matches[1])" -Value $Matches[2]
        }
    }
    if (-not $env:LIB -or $env:LIB -notmatch $Arch) { throw "vcvars did not set an $Arch LIB" }
    $env:RG_VCVARS_DONE = $want
}
$env:PATH = "$LlvmRoot\bin;" + (Split-Path $Ninja) + ";" + $env:PATH

if ($Clean -and (Test-Path $BuildDir)) { Remove-Item -Recurse -Force $BuildDir }

$Toolchain = $(if ($Arch -eq "x64") { "toolchain-x64-windows-clang.cmake" } else { "toolchain-i686-windows-clang.cmake" })
$Extra = @()
if ($Arch -eq "x64") {
    if (-not $X64Src) { $X64Src = Join-Path $Root "build\x64-src" }
    $Extra += "-DRG_X64_SRC=$($X64Src -replace '\\','/')"
}
& $CMake -S $Root -B $BuildDir -G Ninja `
    "-DCMAKE_MAKE_PROGRAM=$Ninja" `
    "-DCMAKE_TOOLCHAIN_FILE=$Root\cmake\$Toolchain" `
    "-DLLVM_ROOT=$($LlvmRoot -replace '\\','/')" `
    "-DCMAKE_BUILD_TYPE=$Config" @Extra
if ($LASTEXITCODE -ne 0) { throw "cmake configure failed" }

& $CMake --build $BuildDir
if ($LASTEXITCODE -ne 0) { throw "build failed" }

if (-not $NoSmoke) {
    & (Join-Path $BuildDir "rg-smoke.exe")
    if ($LASTEXITCODE -ne 0) { throw "smoke test failed" }
    # port headers: u128 substitute, VU0 model/headers, vu0asm stage (docs/PORT-HEADERS.md)
    foreach ($t in @("rg-test-u128.exe", "rg-test-vu0.exe")) {
        & (Join-Path $BuildDir $t)
        if ($LASTEXITCODE -ne 0) { throw "$t failed" }
    }
}

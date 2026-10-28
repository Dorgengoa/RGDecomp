<#
.SYNOPSIS
  Configure (once, -DRG_NATIVE_ONLY=ON) and build targets in the native-only build dir
  (docs/NATIVE-ONLY.md): Release, clang i686, Ninja, -j4 (same toolchain as
  tools\fixtures\build.ps1, which this delegates the build to).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\native\nonly_build.ps1                       # rg-game
  powershell -ExecutionPolicy Bypass -File tools\native\nonly_build.ps1 -Targets rg-game,rg-sif-tests
  powershell -ExecutionPolicy Bypass -File tools\native\nonly_build.ps1 -Reconfigure          # after adding an override
  powershell -ExecutionPolicy Bypass -File tools\native\nonly_build.ps1 -BuildDir build\x -NativeOnly OFF   # a default-config twin
#>
param(
    [string[]]$Targets = @("rg-game"),
    [string]$BuildDir = "",
    [string]$NativeOnly = "ON",
    [switch]$Reconfigure
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not $BuildDir) { $BuildDir = Join-Path $Root "build\nonly-i686" }
$Targets = @($Targets | ForEach-Object { $_ -split "," } | Where-Object { $_ })
$cache = Join-Path $BuildDir "CMakeCache.txt"
$want = "RG_NATIVE_ONLY:BOOL=$NativeOnly"
$have = (Test-Path $cache) -and (Select-String -Path $cache -SimpleMatch $want -Quiet)
if (-not $have) {
    # seed the option into the cache (bytes otherwise untouched); tools\fixtures\build.ps1
    # -Reconfigure then keeps it
    New-Item -ItemType Directory -Force $BuildDir | Out-Null
    if (Test-Path $cache) {
        $t = [IO.File]::ReadAllText($cache)
        if ($t -match '(?m)^RG_NATIVE_ONLY:BOOL=\w+') { $t = $t -replace '(?m)^RG_NATIVE_ONLY:BOOL=\w+', $want }
        else { $t = $t + "`n" + $want + "`n" }
        [IO.File]::WriteAllText($cache, $t)
    } else {
        [IO.File]::WriteAllText($cache, $want + "`n")
    }
    $Reconfigure = $true
}
if (-not (Test-Path (Join-Path $BuildDir "build.ninja"))) { $Reconfigure = $true }
if ($Reconfigure) {
    & (Join-Path $Root "tools\fixtures\build.ps1") -BuildDir $BuildDir -Targets $Targets -Reconfigure
} else {
    & (Join-Path $Root "tools\fixtures\build.ps1") -BuildDir $BuildDir -Targets $Targets
}

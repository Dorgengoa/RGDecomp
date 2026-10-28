<#
.SYNOPSIS
  Build the native audio lane's targets (docs/NATIVE-AUDIO.md) in build\naudio-i686
  (Release, clang i686, ninja -j4; same configuration as tools\fixtures\build.ps1).

.EXAMPLE
  powershell -ExecutionPolicy Bypass -File tools\native\audio_build.ps1                 # tests + rg-game
  powershell -ExecutionPolicy Bypass -File tools\native\audio_build.ps1 -Targets native-audio-tests
  powershell -ExecutionPolicy Bypass -File tools\native\audio_build.ps1 -Reconfigure    # after adding an override
#>
param(
    [string[]]$Targets = @("native-audio-tests", "rg-game"),
    [string]$BuildDir = "",
    [switch]$Reconfigure
)
$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $PSScriptRoot)
if (-not $BuildDir) { $BuildDir = Join-Path $Root "build\naudio-i686" }
if ($Reconfigure -and (Test-Path (Join-Path $BuildDir "build.ninja"))) { Remove-Item (Join-Path $BuildDir "build.ninja") }
# -Targets a,b from cmd/bash arrives as one string: split it
$Targets = @($Targets | ForEach-Object { $_ -split "," } | Where-Object { $_ })
& (Join-Path $Root "tools\fixtures\build.ps1") -BuildDir $BuildDir -Targets $Targets

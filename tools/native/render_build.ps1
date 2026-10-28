# Build tree for the native renderer lane (docs/NATIVE-RENDER.md): build/nrender-i686, -j4 (-Jobs N).
param([string]$BuildDir = "build/nrender-i686", [string]$Target = "rg-game", [switch]$Configure, [int]$Jobs = 4)
$ErrorActionPreference = "Stop"
$VcVars = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
if (-not (Test-Path $VcVars)) { $VcVars = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" }
$env:PATH = $env:PATH -replace '"', ''
$dump = & cmd.exe /c "`"$VcVars`" x86 >nul 2>&1 && set"
foreach ($line in $dump) { if ($line -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] } }
$env:PATH = "../tools\llvm\bin;../tools\ninja;" + $env:PATH
$cm = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe"
if ($Configure) {
  & $cm -S . -B $BuildDir -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-i686-windows-clang.cmake "-DRG_FXC=C:/Program Files (x86)/Windows Kits/10/bin/10.0.19041.0/x64/fxc.exe" -DRG_GPU_REPLAY_DIR=out/p3/gsrec -DRG_FFMPEG=C:/FFmpeg/bin/ffmpeg.exe -DRG_PYTHON=python -DRG_SDL3_ARCHIVE=../tools/dl/SDL3-3.4.18.tar.gz -DRG_VU0_MODE=native -DRG_NATIVE_ONLY=ON -DRG_GAME_OPT=-O2
  if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
& $cm --build $BuildDir -j $Jobs --target $Target.Split(",")
exit $LASTEXITCODE

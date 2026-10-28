# SPDX-License-Identifier: CC0-1.0
# The Khronos validation layer (VK_LAYER_KHRONOS_validation) for the 32-bit (i686) rg-game
# (docs/NATIVE-VULKAN.md "Validation"): the Vulkan SDK ships 64-bit layers only on Windows.
# Builds Vulkan-ValidationLayers (Apache-2.0) and its pinned dependencies (Vulkan-Headers,
# Vulkan-Utility-Libraries, SPIRV-Headers, SPIRV-Tools: Apache-2.0 / MIT, fetched by the layer's
# own scripts/update_deps.py from scripts/known_good.json) with clang-cl -m32 + lld-link + Ninja
# and the MSVC x86 libraries (vcvarsall x86): no GPL code.  A build tool, not shipped.
#   powershell -ExecutionPolicy Bypass -File tools\native\build_vvl_x86.ps1 [-Tag vulkan-sdk-1.4.363.0] [-Jobs 8]
# Output: ../tools\vvl-x86\bin\VkLayer_khronos_validation.{dll,json}.  Use:
#   VK_ADD_LAYER_PATH=../tools\vvl-x86\bin RG_VK_VALIDATE=1 rg-game.exe ...
# (tools/native/vk_validate.sh does that).  Sources in ../tools\dl\vvl-src (own directory).
param([string]$Tag = "vulkan-sdk-1.4.363.0", [int]$Jobs = 8,
      [string]$Src = "../tools\dl\vvl-src", [string]$Out = "../tools\vvl-x86")
$ErrorActionPreference = "Stop"
$VcVars = "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat"
if (-not (Test-Path $VcVars)) { $VcVars = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" }
$env:PATH = $env:PATH -replace '"', ''
$dump = & cmd.exe /c "`"$VcVars`" x86 >nul 2>&1 && set"
foreach ($line in $dump) { if ($line -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] } }
# our CMake first: update_deps.py runs `cmake` from PATH (vcvars puts an older one there)
$env:PATH = "../tools\cmake-3.31.7-windows-x86_64\bin;../tools\llvm\bin;../tools\ninja;" + $env:PATH
$cm = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe"
if (-not (Test-Path "$Src\.git")) {
  New-Item -ItemType Directory -Force (Split-Path $Src) | Out-Null
  git clone --depth 1 -b $Tag https://github.com/KhronosGroup/Vulkan-ValidationLayers.git $Src
  if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
}
$bd = "$Src\build-x86"
& $cm -S $Src -B $bd -G Ninja -DCMAKE_BUILD_TYPE=Release `
  "-DCMAKE_TOOLCHAIN_FILE=$($PSScriptRoot -replace '\\','/')/vvl_x86_toolchain.cmake" "-DCMAKE_MAKE_PROGRAM=../tools/ninja/ninja.exe" `
  -DUPDATE_DEPS=ON -DUPDATE_DEPS_SKIP_EXISTING_INSTALL=ON -DBUILD_TESTS=OFF -DBUILD_WERROR=OFF `
  "-DCMAKE_INSTALL_PREFIX=$Out"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $cm --build $bd -j $Jobs
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& $cm --install $bd
exit $LASTEXITCODE

#!/bin/bash
# SPDX-License-Identifier: CC0-1.0
# native_build.sh [BUILD_DIR] [ninja target]   (docs/LINUX.md "Native build on the Linux machine")
# The windowed i686 build ON the Linux machine, from a source copy at $RG/port
# (tools/linux/remote.py sync-src): clang + the no-root i386 sysroot of noble_sysroot.sh
# (X11 + Wayland + ALSA + PulseAudio + PipeWire + libdecor headers); clang-20 + lld-20 unpacked
# in $RG/hosttools/usr/lib/llvm-20 and wayland-scanner in $RG/hosttools/bin (apt-get download +
# dpkg -x, no root).  The game flags need clang >= 20 (-fwrapv-pointer, cmake/game.cmake);
# Ubuntu 24.04's default clang 18 rejects it.  dxc from $RG/tools/dxc (fetch_dxc.py --linux).
# With gcc-multilib + the i386 -dev packages + clang-20 installed system-wide: RG_CLANG_ROOT=/usr/lib/llvm-20/bin
# and drop RG_LINUX_SYSROOT.
#
# RG_ARCH=x64 (docs/LINUX.md "x64 Linux"): the x86-64 build instead -- toolchain-linux-x64.cmake,
# the amd64 sysroot ($RG/sysroot-noble-amd64: noble_sysroot.sh DIR amd64), the derived game tree
# $RG/port/x64src (tools/x64/derive.py, shipped by remote.py --arch x64 sync-src) and the x64
# overlay registry $RG/port/pregen/overlay-gen-x64; default build dir $RG/build/native-x64.
# RG_CMAKE_EXTRA: more configure arguments for a fresh build dir (e.g. the RG_ASAN check build,
# docs/UB-AUDIT.md "Local-size check": "-DRG_ASAN=ON -DCMAKE_C_FLAGS=-resource-dir=..").
set -e
RG=${RG:-$HOME/rgport}
A=${RG_ARCH:-i686}
if [ "$A" = x64 ]; then
  B=${1:-$RG/build/native-x64}
  TC=toolchain-linux-x64.cmake
  SR=${RG_LINUX_SYSROOT:-$RG/sysroot-noble-amd64}
  EXTRA="-DRG_X64_SRC=$RG/port/x64src"
else
  B=${1:-$RG/build/native-vk}
  TC=toolchain-linux-i686.cmake
  SR=${RG_LINUX_SYSROOT:-$RG/sysroot-noble-i386}
  EXTRA=""
fi
T=${2:-rg-game}
CR=${RG_CLANG_ROOT:-$RG/hosttools/usr/lib/llvm-20/bin}
DXC=${RG_DXC:-$RG/tools/dxc/bin/dxc}
export PATH="$CR:$RG/hosttools/bin:$PATH"
if [ ! -f "$B/CMakeCache.txt" ]; then
  cmake -S "$RG/port" -B "$B" -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE="$RG/port/cmake/$TC" \
    -DRG_LINUX_SYSROOT="$SR" -DRG_CLANG_ROOT="$CR" \
    -DRG_DXC="$DXC" -DRG_PYTHON="$(command -v python3)" \
    -DCMAKE_BUILD_TYPE=Release -DSDL_UNIX_CONSOLE_BUILD=OFF -DRG_LINUX_NATIVE_DEVICE=ON \
    -DSDL_WAYLAND=ON -DSDL_X11=ON -DSDL_ALSA=ON -DSDL_PULSEAUDIO=ON -DSDL_PIPEWIRE=ON \
    -DRG_GAME_OPT=-O2 -DRG_NATIVE_ONLY=ON -DRG_NATIVE_OVL=ON -DRG_VU0_MODE=native $EXTRA $RG_CMAKE_EXTRA
fi
ninja -C "$B" -k 0 -j"${RG_JOBS:-10}" "$T"

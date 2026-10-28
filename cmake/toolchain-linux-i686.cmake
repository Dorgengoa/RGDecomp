# SPDX-License-Identifier: CC0-1.0
# i686 (32-bit) Linux toolchain: clang with -m32.  PLAN.md D1/D2, docs/LINUX.md.
#
# Two ways to use it:
#
#  * Native, on an x86-64 Linux host (or WSL) with a 32-bit multilib:
#      Debian/Ubuntu: clang lld cmake ninja-build gcc-multilib g++-multilib
#      cmake -S . -B build/linux-i686 -G Ninja \
#            -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-i686.cmake
#
#  * Cross, from any host clang can run on (e.g. the Windows LLVM release),
#    against a Debian i386 sysroot (docs/LINUX.md says how to make one):
#      -DRG_LINUX_SYSROOT=../tools/sysroot-i386-bookworm
#    Binaries link but cannot run on the build host, so ctest is Linux-only.
#
# Optional cache variables: RG_LINUX_SYSROOT (cross sysroot), RG_CLANG_ROOT
# (directory holding clang/clang++, searched first).

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR i686)

# Toolchain files run again for try_compile projects; forward our variables.
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES RG_LINUX_SYSROOT RG_CLANG_ROOT)

set(_rg_hints)
if(RG_CLANG_ROOT)
  list(APPEND _rg_hints "${RG_CLANG_ROOT}")
endif()
if(CMAKE_HOST_WIN32)
  # Same LLVM the Windows build uses (docs/TOOLCHAIN.md).
  list(APPEND _rg_hints "${CMAKE_CURRENT_LIST_DIR}/../../tools/llvm/bin")
endif()
find_program(RG_CLANG   NAMES clang   HINTS ${_rg_hints} REQUIRED)
find_program(RG_CLANGXX NAMES clang++ HINTS ${_rg_hints} REQUIRED)
set(CMAKE_C_COMPILER   "${RG_CLANG}")
set(CMAKE_CXX_COMPILER "${RG_CLANGXX}")
get_filename_component(_rg_llvm_bin "${RG_CLANG}" DIRECTORY)
find_program(RG_LLVM_AR     NAMES llvm-ar     HINTS "${_rg_llvm_bin}" NO_DEFAULT_PATH)
find_program(RG_LLVM_RANLIB NAMES llvm-ranlib HINTS "${_rg_llvm_bin}" NO_DEFAULT_PATH)
if(RG_LLVM_AR)
  set(CMAKE_AR "${RG_LLVM_AR}" CACHE FILEPATH "" FORCE)
endif()
if(RG_LLVM_RANLIB)
  set(CMAKE_RANLIB "${RG_LLVM_RANLIB}" CACHE FILEPATH "" FORCE)
endif()

set(RG_TARGET_TRIPLE i686-linux-gnu)
set(CMAKE_C_COMPILER_TARGET   ${RG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${RG_TARGET_TRIPLE})
set(CMAKE_LIBRARY_ARCHITECTURE i386-linux-gnu)

# Non-PIC, non-PIE, like the Windows i686 build: i386 PIC costs %ebx in every
# function, and the overlay import trampolines (src/ps2/overlay/ovl_asm.h)
# push absolute table addresses (R_386_32 in .text, rejected in a PIE).
# -march=pentium4: the CPU baseline clang uses by default for the Windows
# i686 target (i686-pc-windows-msvc), so both platforms generate code for the
# same CPU (CMPXCHG8B, SSE2); i686-linux-gnu alone means a plain i686.
# (It does NOT make 64-bit atomics inline by itself: the i386 SysV ABI aligns
# uint64_t to 4, so __atomic_load_n on a plain uint64_t is still a libatomic
# call; docs/LINUX.md "Open items".)
set(CMAKE_C_FLAGS_INIT   "-m32 -march=pentium4 -fno-pic")
set(CMAKE_CXX_FLAGS_INIT "-m32 -march=pentium4 -fno-pic")
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# lld when it is there (always next to the Windows LLVM release); else the
# system linker (GNU ld handles -m32 through the multilib too).
find_program(RG_LD_LLD NAMES ld.lld HINTS "${_rg_llvm_bin}")
if(RG_LD_LLD)
  set(_rg_ld "-fuse-ld=lld")
else()
  set(_rg_ld "")
endif()
set(CMAKE_EXE_LINKER_FLAGS_INIT    "-m32 -no-pie ${_rg_ld}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-m32 ${_rg_ld}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-m32 ${_rg_ld}")

if(RG_LINUX_SYSROOT)
  set(CMAKE_SYSROOT "${RG_LINUX_SYSROOT}")
  set(CMAKE_FIND_ROOT_PATH "${RG_LINUX_SYSROOT}")
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
  # No pkg-config for the target: keep SDL from picking up host .pc files.
  set(ENV{PKG_CONFIG_LIBDIR} "${RG_LINUX_SYSROOT}/usr/lib/i386-linux-gnu/pkgconfig:${RG_LINUX_SYSROOT}/usr/share/pkgconfig")
  set(ENV{PKG_CONFIG_SYSROOT_DIR} "${RG_LINUX_SYSROOT}")
else()
  # Native multilib: let pkg-config find the i386 .pc files (SDL3's X11 /
  # Wayland / ALSA / PulseAudio probes), not the x86-64 ones.
  set(ENV{PKG_CONFIG_LIBDIR} "/usr/lib/i386-linux-gnu/pkgconfig:/usr/lib32/pkgconfig:/usr/share/pkgconfig")
endif()

# SPDX-License-Identifier: CC0-1.0
# x86-64 Linux toolchain (P7 strategy A on Linux: docs/LINUX.md "x64 Linux", docs/X64-PLAN.md 0.13/0.16).
#
# The game keeps every pointer it stores in 4 bytes (the derived tree, tools/x64/derive.py), so
# every address game code can see must be below 2 GB.  Windows does that process-wide
# (LAA:NO + a low base); here:
#   * the image: non-PIE ET_EXEC at 0x400000 (-no-pie -fno-pic, small code model).  ld.lld
#     itself rejects an R_X86_64_32 that does not fit (no pecheck / linkgate needed);
#   * game RAM, fiber stacks, the start-up check: src/runtime/crt0.c, fiber_ucontext.c,
#     src/x64/lowmem_linux.c (cmake/x64.cmake);
#   * everything else (SDL, Vulkan, X11 / Wayland, their heaps) may live high.
#
#  * Native on an x86-64 Linux host with clang >= 20 + lld:
#      cmake -S . -B build/linux-x64 -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-x64.cmake \
#            -DRG_X64_SRC=<derived tree> [-DRG_LINUX_SYSROOT=<amd64 sysroot>] [-DRG_CLANG_ROOT=<llvm bin>]
#    (tools/linux/native_build.sh x64 does this with the no-root sysroot of noble_sysroot.sh DIR amd64)
#  * Cross from Windows: -DRG_LINUX_SYSROOT=<amd64 sysroot> (binaries link but cannot run here)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES RG_LINUX_SYSROOT RG_CLANG_ROOT)

set(_rg_hints)
if(RG_CLANG_ROOT)
  list(APPEND _rg_hints "${RG_CLANG_ROOT}")
endif()
if(CMAKE_HOST_WIN32)
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

set(RG_TARGET_TRIPLE x86_64-linux-gnu)
set(CMAKE_C_COMPILER_TARGET   ${RG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${RG_TARGET_TRIPLE})
set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)

# -fno-pic / -no-pie: absolute 32-bit addresses (data-layer .long sym, __ptr32 stores) need a
# low non-PIE image.  -fms-extensions: __ptr32 / __uptr (RG_P32, SCE_P32, CRT_P32) are Microsoft
# keywords; the MSVC target has them on by default.
set(CMAKE_C_FLAGS_INIT   "-fno-pic -fms-extensions")
set(CMAKE_CXX_FLAGS_INIT "-fno-pic -fms-extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

find_program(RG_LD_LLD NAMES ld.lld HINTS "${_rg_llvm_bin}")
if(RG_LD_LLD)
  set(_rg_ld "-fuse-ld=lld")
else()
  message(FATAL_ERROR "x64 Linux: ld.lld is required (--image-base, the R_X86_64_32 range check)")
endif()
# the image at 0x400000 as the Windows x64 exe (/BASE:0x00400000); ld.lld's default is 0x200000
set(CMAKE_EXE_LINKER_FLAGS_INIT    "-no-pie ${_rg_ld} -Wl,--image-base=0x400000")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${_rg_ld}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${_rg_ld}")

if(RG_LINUX_SYSROOT)
  set(CMAKE_SYSROOT "${RG_LINUX_SYSROOT}")
  set(CMAKE_FIND_ROOT_PATH "${RG_LINUX_SYSROOT}")
  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
  set(ENV{PKG_CONFIG_LIBDIR} "${RG_LINUX_SYSROOT}/usr/lib/x86_64-linux-gnu/pkgconfig:${RG_LINUX_SYSROOT}/usr/share/pkgconfig")
  set(ENV{PKG_CONFIG_SYSROOT_DIR} "${RG_LINUX_SYSROOT}")
  set(CMAKE_PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/linux-sysroot-find.cmake")
endif()

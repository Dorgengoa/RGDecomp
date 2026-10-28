# i686 (32-bit) Windows toolchain: clang (GNU-style driver) targeting
# i686-pc-windows-msvc, linked with lld-link against the MSVC x86 CRT and the
# Windows SDK.  PLAN.md D1/D2.
#
# The MSVC/SDK library and include paths come from the environment
# (INCLUDE / LIB, as set by `vcvarsall.bat x86`).  tools/build.ps1 does that.
#
# LLVM_ROOT may be passed with -DLLVM_ROOT=... ; it defaults to
# <repo>/../tools/llvm (the workspace layout in README.md).

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

if(NOT LLVM_ROOT)
  if(DEFINED ENV{LLVM_ROOT})
    set(LLVM_ROOT "$ENV{LLVM_ROOT}")
  else()
    get_filename_component(LLVM_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../tools/llvm" ABSOLUTE)
  endif()
endif()
set(LLVM_ROOT "${LLVM_ROOT}" CACHE PATH "LLVM install root")

set(CMAKE_C_COMPILER   "${LLVM_ROOT}/bin/clang.exe")
set(CMAKE_CXX_COMPILER "${LLVM_ROOT}/bin/clang++.exe")
set(CMAKE_RC_COMPILER  "${LLVM_ROOT}/bin/llvm-rc.exe")
set(CMAKE_AR           "${LLVM_ROOT}/bin/llvm-ar.exe" CACHE FILEPATH "")
set(CMAKE_LINKER       "${LLVM_ROOT}/bin/lld-link.exe" CACHE FILEPATH "")

set(RG_TARGET_TRIPLE i686-pc-windows-msvc)
set(CMAKE_C_COMPILER_TARGET   ${RG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${RG_TARGET_TRIPLE})

# lld instead of link.exe
set(CMAKE_EXE_LINKER_FLAGS_INIT    "-fuse-ld=lld")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")

# Release CRT everywhere (no debug CRT dependency on the dev box).
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)

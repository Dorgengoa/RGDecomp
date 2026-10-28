# x64 (x86_64-pc-windows-msvc) toolchain: SCRATCH, for the P7 probe only
# (docs/X64-PLAN.md).  Not a supported build yet: CMakeLists.txt still refuses
# a non-4-byte pointer (PLAN.md D1) and RG_COMMON_FLAGS still carries -m32, so
# configuring with this file stops at that guard by design.  The probe compile
# (tools/census/x64_probe.py) does not configure: it rewrites an i686 build's
# compile_commands.json to this triple.
#
# What this file records for P7 step 1 (strategy A, a 32-bit game address
# space on x64; docs/X64-PLAN.md section 4):
#   * the triple and the same LLVM install as the i686 toolchain;
#   * the link flags that keep EVERY address of the process below 2 GB:
#     /LARGEADDRESSAWARE:NO (Windows then caps the 64-bit process's user space
#     at 2 GB: heap, stacks, DLLs, VirtualAlloc), /DYNAMICBASE:NO + a low /BASE
#     (image and its statics below 2 GB; ADDR32 relocations of the data layer
#     resolve; lld-link does NOT diagnose an ADDR32 relocation that overflows
#     with the default 0x140000000 base -- probe t4b crashed), /HIGHENTROPYVA:NO.
#   * MSVC/SDK paths come from `vcvarsall.bat x64` (INCLUDE / LIB), as
#     tools/build.ps1 does for x86.
#
# Usage once CMakeLists.txt is arch-aware (P7 step 1):
#   cmake -G Ninja -S . -B build/x64-windows -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-x64-windows-clang.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR AMD64)

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

set(RG_TARGET_TRIPLE x86_64-pc-windows-msvc)
set(CMAKE_C_COMPILER_TARGET   ${RG_TARGET_TRIPLE})
set(CMAKE_CXX_COMPILER_TARGET ${RG_TARGET_TRIPLE})

# Strategy A: one 32-bit game address space (every host address < 2 GB).
set(RG_X64_LOWMEM_LINK "-fuse-ld=lld -Wl,/LARGEADDRESSAWARE:NO,/DYNAMICBASE:NO,/HIGHENTROPYVA:NO,/BASE:0x00400000")
set(CMAKE_EXE_LINKER_FLAGS_INIT    "${RG_X64_LOWMEM_LINK}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-fuse-ld=lld")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-fuse-ld=lld")

set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)

# SPDX-License-Identifier: CC0-1.0
# Toolchain of tools/native/build_vvl_x86.ps1: clang-cl -m32 + lld-link (i686-pc-windows-msvc,
# the MSVC x86 libraries from vcvarsall x86).  A toolchain file, because the validation layer's
# update_deps.py passes it on to every dependency build (the flags alone would not be).
# no CMAKE_SYSTEM_NAME: a cross-compiling build makes the dependencies search CMAKE_FIND_ROOT_PATH
# only and they do not find each other
# LLVM: $LLVM_ROOT, else <repo>/../tools/llvm
if(DEFINED ENV{LLVM_ROOT})
  set(_rg_llvm "$ENV{LLVM_ROOT}")
else()
  get_filename_component(_rg_llvm "${CMAKE_CURRENT_LIST_DIR}/../../../tools/llvm" ABSOLUTE)
endif()
set(CMAKE_C_COMPILER ${_rg_llvm}/bin/clang-cl.exe)
set(CMAKE_CXX_COMPILER ${_rg_llvm}/bin/clang-cl.exe)
set(CMAKE_C_COMPILER_TARGET i686-pc-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET i686-pc-windows-msvc)
set(CMAKE_LINKER ${_rg_llvm}/bin/lld-link.exe)
set(CMAKE_AR ${_rg_llvm}/bin/llvm-lib.exe)
set(CMAKE_RC_COMPILER ${_rg_llvm}/bin/llvm-rc.exe)
set(CMAKE_MT ${_rg_llvm}/bin/llvm-mt.exe)
set(CMAKE_C_FLAGS_INIT "-m32")
set(CMAKE_CXX_FLAGS_INIT "-m32")
set(CMAKE_EXE_LINKER_FLAGS_INIT "/machine:x86")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "/machine:x86")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "/machine:x86")

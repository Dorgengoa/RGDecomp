# SPDX-License-Identifier: CC0-1.0
# Native IOP lane (docs/NATIVE-IOP.md): RG_IOP mode switch + census counters.
# A leaf library: the HLE layers (src/ps2/sif, src/ps2/iop, src/ps2/padmc) and the
# SDK surface (src/sce/sif, src/sce/padmc) link it to count themselves.
add_library(rg_native_iop STATIC rg_iop.h rg_iop.c rg_iop_fio.h rg_iop_fio.c)
target_include_directories(rg_native_iop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_iop PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_native_iop PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_iop PRIVATE -Wall -Wextra)
endif()

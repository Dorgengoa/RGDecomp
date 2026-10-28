# SPDX-License-Identifier: CC0-1.0
# SIF HLE core: registers, SIF0/SIF1 DMA, RPC registry and calls, commands.
# Kernel-agnostic (hooks); src/sce/sif wires it to ps2k. See sif.h, docs/SIF.md.
add_library(rg_ps2_sif STATIC sif.h sif.c)
target_include_directories(rg_ps2_sif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_sif PUBLIC rg_ps2_iop PRIVATE rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_sif PRIVATE -Wall -Wextra)
endif()

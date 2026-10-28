# SPDX-License-Identifier: CC0-1.0
# EE SIF SDK surface (sifcmd/sifrpc/DMA/iopheap/loadfile/iopcontrol/fileio/libsdr)
# over rg_ps2_sif + the HLE IOP servers, wired to the EE kernel through its public
# header only. See libsif.h, docs/SIF.md.
add_library(rg_sce_sif STATIC
  libsif.h
  sif_internal.h
  sif_ee.c
  fileio.c
  libsdr.c
  game_names.c)
target_include_directories(rg_sce_sif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_sce_sif PUBLIC rg_ps2_iop_hle rg_ps2_sif rg_ps2_iop rg_ps2_kernel PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_sce_sif PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_sif PRIVATE -Wall -Wextra)
endif()

# tests/sif (CTest, label sif)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/sif ${CMAKE_BINARY_DIR}/tests/sif)

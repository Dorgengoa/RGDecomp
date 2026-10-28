# SPDX-License-Identifier: CC0-1.0
# EE libpad + libmc over the padman/mcserv HLE (src/ps2/padmc). See docs/PADMC.md.
add_library(rg_sce_padmc STATIC
  libpad.h libpad.c
  libmc.h libmc.c)
target_include_directories(rg_sce_padmc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_sce_padmc PUBLIC rg_native_input rg_native_saves rg_native_iop
  rg_ps2_padmc rg_sce_sif rg_ps2_sif rg_ps2_kernel PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_sce_padmc PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_padmc PRIVATE -Wall -Wextra)
endif()

# tests/padmc (CTest, label padmc)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/padmc ${CMAKE_BINARY_DIR}/tests/padmc)

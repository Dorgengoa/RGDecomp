# SPDX-License-Identifier: CC0-1.0
# IOP-side pad and memory-card HLE (the RG_IOP=hle oracle, docs/NATIVE-IOP.md): padman
# (DS2 model + DMA buffer writer, SIF 0x80000100/101) and mcserv (SIF 0x80000400 over
# the native save service).  See docs/PADMC.md.  The save service (mccard, card time)
# and the pad I/O (input source, rumble, scripts) are native libraries both paths use.
add_subdirectory(${PROJECT_SOURCE_DIR}/src/native/saves ${CMAKE_BINARY_DIR}/src/native/saves)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/native/input ${CMAKE_BINARY_DIR}/src/native/input)
add_library(rg_ps2_padmc STATIC
  padman.h padman.c
  mcserv.h mcserv.c)
target_include_directories(rg_ps2_padmc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_padmc PUBLIC rg_ps2_sif rg_native_saves rg_native_input PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_ps2_padmc PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_padmc PRIVATE -Wall -Wextra)
endif()

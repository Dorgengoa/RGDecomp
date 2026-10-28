# SPDX-License-Identifier: CC0-1.0
# libdma / libgraph / libpkt SDK surface over the DMAC + GS models
# (docs/DMAC.md "SDK surface").
add_library(rg_sce_graphics STATIC
  libdma.h libgraph.h libpkt.h graphics_internal.h
  libdma.c libgraph.c libpkt.c graphics_game_names.c)
target_include_directories(rg_sce_graphics PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(rg_sce_graphics PUBLIC rg_ps2_dmac rg_ps2_gs rg_ps2_vif rg_ps2_kernel rg_native_threads rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_graphics PRIVATE -Wall -Wextra)
endif()

# The same SDK surface without the DMAC / VIF / VU models (docs/NATIVE-RENDER.md "DMA without
# the DMAC"): what an RG_NATIVE_ONLY rg-game links instead (cmake/native_only.cmake
# RG_NONLY_REPLACE).  Model headers only (types and constants), the GS model still linked.
add_library(rg_sce_graphics_native STATIC
  libdma.h libgraph.h libpkt.h graphics_internal.h
  libdma_native.c libgraph.c libpkt.c graphics_game_names.c)
target_compile_definitions(rg_sce_graphics_native PRIVATE RG_GRAPHICS_NATIVE=1)
target_include_directories(rg_sce_graphics_native PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:rg_ps2_dmac,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:rg_ps2_vif,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:rg_ps2_vu,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(rg_sce_graphics_native PUBLIC rg_ps2_gs rg_ps2_vif rg_ps2_kernel rg_native_threads rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_graphics_native PRIVATE -Wall -Wextra)
endif()

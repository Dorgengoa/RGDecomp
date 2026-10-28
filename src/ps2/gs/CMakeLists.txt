# SPDX-License-Identifier: CC0-1.0
# GS core: GIF, registers, local memory, software reference rasterizer,
# display read-out (docs/GS.md).  Independent of the game build.
add_library(rg_ps2_gs STATIC
  gs.h
  gs_internal.h
  gs_core.c
  gs_mem.c
  gs_tex.c
  gs_raster.c
  gs_display.c
  gs_rec.c
  gs_async.c
  gs_census.c)
# Hot platform code (original port code, not the decompiled game): -O2.
# PLAN.md D2's -O1 is for the game sources until their UB audit; source
# options come after rg_flags' -O1 on the command line (docs/PERF-3D.md).
set_source_files_properties(gs_core.c gs_mem.c gs_tex.c gs_raster.c gs_display.c gs_rec.c gs_async.c PROPERTIES COMPILE_OPTIONS -O2)
target_include_directories(rg_ps2_gs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_gs PUBLIC rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_gs PRIVATE -Wall -Wextra)
endif()
if(NOT WIN32)
  target_link_libraries(rg_ps2_gs PUBLIC m pthread)
endif()

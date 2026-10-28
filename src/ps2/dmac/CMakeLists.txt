# SPDX-License-Identifier: CC0-1.0
# EE DMA controller model (docs/DMAC.md).  Independent of the game build.
add_library(rg_ps2_dmac STATIC dmac.h dmac.c)
# Hot platform code (original port code, not the decompiled game): -O2.
# PLAN.md D2's -O1 is for the game sources until their UB audit; source
# options come after rg_flags' -O1 on the command line (docs/PERF-3D.md).
set_source_files_properties(dmac.c PROPERTIES COMPILE_OPTIONS -O2)
target_include_directories(rg_ps2_dmac PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_dmac PUBLIC rg_ps2_vif rg_ps2_gs rg_ps2_kernel rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_dmac PRIVATE -Wall -Wextra)
endif()

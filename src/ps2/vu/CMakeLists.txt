# SPDX-License-Identifier: CC0-1.0
# VU0 (micro mode) / VU1 interpreter + disassembler (docs/VU.md).
add_library(rg_ps2_vu STATIC
  vu.h
  vu_decode.h
  vu_float_inl.h
  vu_internal.h
  vu.c
  vu_block.c
  vu_float.c
  vu_decode.c
  vu_disasm.c)
# Hot platform code (original port code, not the decompiled game): -O2.
# PLAN.md D2's -O1 is for the game sources until their UB audit; source
# options come after rg_flags' -O1 on the command line (docs/PERF-3D.md).
set_source_files_properties(vu.c vu_block.c vu_float.c vu_decode.c PROPERTIES COMPILE_OPTIONS -O2)
target_include_directories(rg_ps2_vu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_vu PUBLIC rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_vu PRIVATE -Wall -Wextra)
endif()

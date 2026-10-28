# SPDX-License-Identifier: CC0-1.0
# SPU2 voice engine (docs/SOUND.md). No host or IOP dependency.
add_library(rg_ps2_spu STATIC spu2.h spu2.c)
target_include_directories(rg_ps2_spu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_spu PRIVATE rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_spu PRIVATE -Wall -Wextra)
endif()

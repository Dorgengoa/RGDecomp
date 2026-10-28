# SPDX-License-Identifier: CC0-1.0
# rg_savestate: port save states (docs/TEST-FIXTURES.md).  Linked into rg-game
# only: ss_heap.c replaces malloc & co. for the whole executable it is linked
# into (i686 Windows; elsewhere rg_ss_init fails and nothing is replaced).
if(NOT TARGET rg_runtime)
  return()
endif()
add_library(rg_savestate STATIC
  rg_savestate.h ss_internal.h
  ss_map.c ss_heap.c ss_core.c ss_hooks.c)
target_include_directories(rg_savestate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_savestate PUBLIC rg_runtime rg_ps2_kernel rg_flags)
if(WIN32)
  target_compile_definitions(rg_savestate PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_savestate PRIVATE -Wall -Wextra)
endif()

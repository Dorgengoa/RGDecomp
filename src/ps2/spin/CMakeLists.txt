# SPDX-License-Identifier: CC0-1.0
# rg_spin: runtime side of ingest stage `spin` (docs/SPIN.md).  Tests:
# tests/spin/CMakeLists.txt (ctest -L spin).
add_library(rg_ps2_spin STATIC spin.h spin.c)
target_include_directories(rg_ps2_spin PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_spin PUBLIC rg_ps2_kernel rg_native_threads rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_spin PRIVATE -Wall -Wextra)
endif()

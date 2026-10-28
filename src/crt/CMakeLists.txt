# SPDX-License-Identifier: CC0-1.0
# The C/C++ runtime under the game's names (newlib libc/libm, libgcc,
# soft-double, mwcc runtime, MSL C++): docs/BINDINGS.md.  sbrk and
# rg_ps2_exit come from src/runtime in the game link.
add_library(rg_crt STATIC
  crt.h
  crt_libc.c
  crt_heap.c
  crt_math.c
  crt_eelibm.c
  crt_msl.c
  crt_mslstr.c)
# (FlushCache: src/sce/kernel/eekernel.c)
target_include_directories(rg_crt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_crt PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_crt PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_crt PRIVATE -Wall -Wextra)
endif()

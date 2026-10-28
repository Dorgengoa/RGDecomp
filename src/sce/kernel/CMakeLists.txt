# SPDX-License-Identifier: CC0-1.0
# EE kernel SDK surface (sceKernel / libkernl names) over rg_ps2_kernel.
add_library(rg_sce_kernel STATIC
  eekernel.h
  eekernel.c
  kcensus.h
  kcensus.c)
target_include_directories(rg_sce_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_sce_kernel PUBLIC rg_ps2_kernel rg_native_threads rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_kernel PRIVATE -Wall -Wextra)
endif()

# RG_NATIVE_ONLY (docs/NATIVE-ONLY.md, docs/NATIVE-THREADS.md "Native-only"): the SDK surface
# over the native kernel table, without the census recorder; replaces rg_sce_kernel in rg-game
if(RG_NATIVE_ONLY)
  add_library(rg_sce_kernel_native STATIC eekernel.h eekernel.c)
  target_include_directories(rg_sce_kernel_native PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(rg_sce_kernel_native PUBLIC rg_native_threads PRIVATE rg_flags)
  target_compile_definitions(rg_sce_kernel_native PRIVATE RG_NATIVE_ONLY=1)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(rg_sce_kernel_native PRIVATE -Wall -Wextra)
  endif()
endif()

# native threads (docs/NATIVE-THREADS.md): the game reaches it through this library
add_subdirectory(${PROJECT_SOURCE_DIR}/src/native/threads ${CMAKE_BINARY_DIR}/src/native/threads)

# tests/kernel (CTest)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests/kernel ${CMAKE_BINARY_DIR}/tests/kernel)

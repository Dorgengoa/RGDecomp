# SPDX-License-Identifier: CC0-1.0
# IOP model (RAM, heap, module log) and the HLE IOP servers. See iop.h, docs/SIF.md.
# Native IOP lane (docs/NATIVE-IOP.md): the RG_IOP switch + census counters, the native
# save service (memory card on host files) and the native pad service.  Configured
# here because every IOP/SIF/pad/card library below links them.
add_subdirectory(${PROJECT_SOURCE_DIR}/src/native/iop ${CMAKE_BINARY_DIR}/src/native/iop)
add_library(rg_ps2_iop STATIC iop.h iop.c)
target_include_directories(rg_ps2_iop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_iop PUBLIC rg_native_iop PRIVATE rg_flags)

# Servers registered with the SIF core (rg_ps2_sif, src/ps2/sif).
add_library(rg_ps2_iop_hle STATIC iop_hle.c)
target_link_libraries(rg_ps2_iop_hle PUBLIC rg_ps2_sif rg_ps2_iop PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_ps2_iop_hle PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_iop PRIVATE -Wall -Wextra)
  target_compile_options(rg_ps2_iop_hle PRIVATE -Wall -Wextra)
endif()

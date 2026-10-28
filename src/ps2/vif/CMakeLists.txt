# SPDX-License-Identifier: CC0-1.0
# VIF0/VIF1 command processor (docs/VU.md).
add_library(rg_ps2_vif STATIC vif.h vif.c)
# Hot platform code (original port code, not the decompiled game): -O2.
# PLAN.md D2's -O1 is for the game sources until their UB audit; source
# options come after rg_flags' -O1 on the command line (docs/PERF-3D.md).
set_source_files_properties(vif.c PROPERTIES COMPILE_OPTIONS -O2)
target_include_directories(rg_ps2_vif PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_vif PUBLIC rg_ps2_vu rg_flags)

# Retail-ELF microcode access: census tool and smoke tests only.
add_library(rg_vu_retail STATIC vu_retail.h vu_retail.c)
target_include_directories(rg_vu_retail PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_vu_retail PUBLIC rg_flags)

add_executable(rg-vucensus vucensus.c)
target_link_libraries(rg-vucensus PRIVATE rg_ps2_vif rg_vu_retail rg_flags)
target_compile_definitions(rg-vucensus PRIVATE RG_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

if(WIN32)
  target_compile_definitions(rg_vu_retail PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_definitions(rg-vucensus PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_vif PRIVATE -Wall -Wextra)
endif()

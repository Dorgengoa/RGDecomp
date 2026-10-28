# SPDX-License-Identifier: CC0-1.0
# EE hardware register bus: HW_R*/HW_W* router, PS2_SPR base, RG_OVL_DATA
# backing (docs/HWBUS.md).  Independent of the game build.
# RG_OVL_DATA backing: not hardware (MAIN reading overlay memory through the
# overlay manager's resolver), so its own library, which a build without the
# bus can link (docs/NATIVE-CPU.md "hwbus").
add_library(rg_ovl_data STATIC hwbus.h ovldata.c)
target_include_directories(rg_ovl_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ovl_data PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_ovl_data PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
add_library(rg_ps2_hwbus STATIC hwbus.h hwbus.c)
target_include_directories(rg_ps2_hwbus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_hwbus PUBLIC rg_ovl_data rg_ps2_dmac rg_ps2_gs rg_ps2_vif rg_ps2_sif rg_ps2_kernel rg_flags)
if(WIN32)
  target_compile_definitions(rg_ps2_hwbus PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_hwbus PRIVATE -Wall -Wextra)
endif()

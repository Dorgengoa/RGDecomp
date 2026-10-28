# SPDX-License-Identifier: CC0-1.0
# libcdvd (EE) over the CDVD model in src/ps2/cdvd. See docs/CDVD.md.
add_library(rg_sce_cdvd STATIC
  libcdvd.h
  libcdvd.c
  libcdvd_game_names.c)
target_include_directories(rg_sce_cdvd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_sce_cdvd PUBLIC rg_ps2_cdvd PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_sce_cdvd PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# RG_NATIVE_ONLY (docs/NATIVE-ONLY.md): the same entry points with no sector / drive model
# (searches by name through rg_fs, sector reads refused); rg-game links it in place of
# rg_sce_cdvd.  rg_native_fs is defined later by the top CMakeLists (fine for linking).
if(RG_NATIVE_ONLY)
  add_library(rg_sce_cdvd_native STATIC libcdvd.h libcdvd_native.c libcdvd_game_names.c)
  target_include_directories(rg_sce_cdvd_native PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(rg_sce_cdvd_native PUBLIC rg_native_fs PRIVATE rg_flags)
  target_compile_definitions(rg_sce_cdvd_native PRIVATE RG_NATIVE_ONLY=1)
  if(WIN32)
    target_compile_definitions(rg_sce_cdvd_native PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(rg_sce_cdvd_native PRIVATE -Wall -Wextra)
  endif()
endif()

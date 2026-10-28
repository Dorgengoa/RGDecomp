# SPDX-License-Identifier: CC0-1.0
# CDVD model: disc sectors served from data/ via MANIFEST.tsv, plus the async drive.
# See cdvd.h and docs/CDVD.md.
add_library(rg_ps2_cdvd STATIC
  cdvd.h
  cdvd_disc.c
  cdvd_drive.c)
target_include_directories(rg_ps2_cdvd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_cdvd PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_ps2_cdvd PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

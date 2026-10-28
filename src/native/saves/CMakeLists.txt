# SPDX-License-Identifier: CC0-1.0
# Native save service (docs/NATIVE-IOP.md, docs/SAVES.md): the PS2 memory card on host
# files (mccard.c) and the card time model (mc_time.c).  libmc calls it directly in
# RG_IOP=native; the mcserv HLE (src/ps2/padmc, the oracle) calls the same functions.
add_library(rg_native_saves STATIC mccard.h mccard.c mc_time.c)
target_include_directories(rg_native_saves PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_saves PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_native_saves PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_saves PRIVATE -Wall -Wextra)
endif()

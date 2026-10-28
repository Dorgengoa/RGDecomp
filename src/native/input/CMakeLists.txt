# SPDX-License-Identifier: CC0-1.0
# Native pad service (docs/NATIVE-IOP.md): the DS2 the game reads through libpad,
# answered from host input (rg_npad.c), and the pad I/O shared with the padman HLE
# oracle (rg_pad_io.c: input source, latched reports, rumble hook, scripted replay).
add_library(rg_native_input STATIC rg_pad_io.h rg_pad_io.c rg_npad.h rg_npad.c)
target_include_directories(rg_native_input PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_input PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_native_input PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_input PRIVATE -Wall -Wextra)
endif()

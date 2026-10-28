# SPDX-License-Identifier: CC0-1.0
# libmpeg entry points the (never-run) game movie decoder layer names; the
# movie service replaces libmpeg (docs/MOVIE.md, docs/BINDINGS.md).
add_library(rg_sce_mpeg STATIC libmpeg_unreached.c)
target_link_libraries(rg_sce_mpeg PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_sce_mpeg PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_sce_mpeg PRIVATE -Wall -Wextra)
endif()

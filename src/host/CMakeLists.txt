# SPDX-License-Identifier: CC0-1.0
# Host shell (docs/HOST.md): SDL3 window / input / audio / pacing / PNG.
# Independent of the game build.  src/host/smoke.c belongs to the top-level
# rg-smoke target and is not part of this library.

# ---- SDL3 (zlib license, THIRD_PARTY_NOTICES.md), built from the official
# release source archive, pinned by version and SHA-256.  The archive is taken
# from RG_SDL3_ARCHIVE when that file exists (offline builds), else downloaded
# from the GitHub release.  Either way the hash must match.
include(FetchContent)
set(RG_SDL3_VERSION 3.4.18)
set(RG_SDL3_SHA256 9c75cf16330322c217dedd2e0609f1124f1b54b8633e763467b4684d0f4334a3)
set(RG_SDL3_ARCHIVE "${CMAKE_SOURCE_DIR}/../tools/dl/SDL3-${RG_SDL3_VERSION}.tar.gz"
    CACHE FILEPATH "Local copy of the SDL3 release source archive (optional)")
if(EXISTS "${RG_SDL3_ARCHIVE}")
  get_filename_component(_rg_sdl_urls "${RG_SDL3_ARCHIVE}" ABSOLUTE)
else()
  set(_rg_sdl_urls
    "https://github.com/libsdl-org/SDL/releases/download/release-${RG_SDL3_VERSION}/SDL3-${RG_SDL3_VERSION}.tar.gz")
endif()
message(STATUS "SDL3 ${RG_SDL3_VERSION} source: ${_rg_sdl_urls}")

set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDL_CAMERA OFF CACHE BOOL "" FORCE)
FetchContent_Declare(SDL3
  URL ${_rg_sdl_urls}
  URL_HASH SHA256=${RG_SDL3_SHA256}
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  EXCLUDE_FROM_ALL)
FetchContent_MakeAvailable(SDL3)
# The top level strips -O from the per-config flags (it owns optimisation for
# port code); SDL is third-party code and gets a normal optimised build.
target_compile_options(SDL3-static PRIVATE -O2)

# ---- the host library
add_library(rg_host STATIC
  host.h
  host_internal.h
  host_pad.c
  rg_input.h
  host_input.c
  host_script.c
  host_png.c
  host_pace.c
  host_audio.c
  host_scale.c
  host_sdl.c)
target_include_directories(rg_host PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_host PUBLIC rg_flags rg_settings SDL3::SDL3-static)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_host PRIVATE -Wall -Wextra)
endif()
if(WIN32)
  target_compile_definitions(rg_host PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(NOT WIN32)
  target_link_libraries(rg_host PUBLIC m)
endif()

# ---- demo: GS software rasterizer -> display read-out -> window
add_executable(rg-host-demo demo/host_demo.c)
target_link_libraries(rg-host-demo PRIVATE rg_host rg_ps2_gs rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-host-demo PRIVATE -Wall -Wextra)
endif()
if(WIN32)
  target_compile_definitions(rg-host-demo PRIVATE _CRT_SECURE_NO_WARNINGS)
  # A console-subsystem exe, so --headless runs print to the terminal/CTest.
endif()

# SPDX-License-Identifier: CC0-1.0
# rg-extract: first-run disc image verifier and unpacker (PLAN.md D8).
# Builds standalone (cmake -S src/extract) or via add_subdirectory(src/extract).
cmake_minimum_required(VERSION 3.20)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  project(rg_extract LANGUAGES CXX)
  enable_testing()
endif()

find_package(Threads REQUIRED)

add_library(rg_extract_core STATIC
  extract.cpp
  extract.h
  hash.cpp
  hash.h
  iso9660.cpp
  iso9660.h
  mvi.cpp
  mvi.h)
target_compile_features(rg_extract_core PUBLIC cxx_std_17)
target_include_directories(rg_extract_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_extract_core PUBLIC Threads::Threads)
if(WIN32)
  target_compile_definitions(rg_extract_core PUBLIC _CRT_SECURE_NO_WARNINGS UNICODE _UNICODE NOMINMAX)
else()
  target_compile_definitions(rg_extract_core PUBLIC _FILE_OFFSET_BITS=64)
endif()
if(MSVC)
  target_compile_options(rg_extract_core PUBLIC /W4 /utf-8)
else()
  target_compile_options(rg_extract_core PUBLIC -Wall -Wextra)
endif()
# std::filesystem needs libstdc++fs on GCC < 9.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
  target_link_libraries(rg_extract_core PUBLIC stdc++fs)
endif()

add_executable(rg-extract main.cpp)
target_link_libraries(rg-extract PRIVATE rg_extract_core)
if(MINGW)
  target_link_options(rg-extract PRIVATE -municode)
endif()

# rg-setup: the published build's one-step first run (unpack + rebuild rg-game.exe,
# docs/RELEASE.md); shipped as Setup.exe.
add_executable(rg-setup setup_main.cpp)
target_link_libraries(rg-setup PRIVATE rg_extract_core)
if(MINGW)
  target_link_options(rg-setup PRIVATE -municode)
endif()

add_executable(rg-extract-tests tests/extract_tests.cpp)
target_link_libraries(rg-extract-tests PRIVATE rg_extract_core)
add_test(NAME rg-extract-tests COMMAND rg-extract-tests)

add_executable(rg-extract-mvi-tests tests/mvi_tests.cpp)
target_link_libraries(rg-extract-mvi-tests PRIVATE rg_extract_core)
add_test(NAME rg-extract-mvi-tests COMMAND rg-extract-mvi-tests)

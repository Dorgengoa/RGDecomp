# SPDX-License-Identifier: CC0-1.0
# Native host file service (docs/NATIVE-FS.md): files by name / byte offset from
# data/, sync + async reads.  No CDVD sector model.
add_library(rg_native_fs STATIC rg_fs.h rg_fs.c)
target_include_directories(rg_native_fs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_fs PRIVATE rg_flags)
if(NOT WIN32)
  find_package(Threads REQUIRED)
  target_link_libraries(rg_native_fs PUBLIC Threads::Threads)
endif()

# Check mode only: compares native reads with the old CDVD sector model.
add_library(rg_native_fs_oracle STATIC rg_fs_oracle.h rg_fs_oracle.c)
target_include_directories(rg_native_fs_oracle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_fs_oracle PUBLIC rg_native_fs PRIVATE rg_ps2_cdvd rg_flags)

foreach(t rg_native_fs rg_native_fs_oracle)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

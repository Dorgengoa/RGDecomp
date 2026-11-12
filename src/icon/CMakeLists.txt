# SPDX-License-Identifier: CC0-1.0
# The exe / window icon from the player's own data/ (docs/ICON.md).  No game art in the
# tree or the build: the icon is made from data/ at run time (window), by Setup.exe (the
# player's exe) or by `rg-icon embed` (maintainer copies).  src/extract's rg-setup compiles
# rg_icon.cpp directly (it builds standalone).
add_library(rg_icon STATIC rg_icon.h rg_icon.cpp)
target_include_directories(rg_icon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(rg_icon PUBLIC cxx_std_17)
target_link_libraries(rg_icon PRIVATE rg_flags)

add_executable(rg-icon rg_icon_tool.cpp)
target_link_libraries(rg-icon PRIVATE rg_icon rg_flags)

add_executable(rg-icon-tests tests/icon_tests.cpp)
target_link_libraries(rg-icon-tests PRIVATE rg_icon rg_flags)
set(_out ${CMAKE_CURRENT_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${_out})
foreach(t resample layout sources embed)
  add_test(NAME icon.${t} COMMAND rg-icon-tests ${t} ${_out})
  set_tests_properties(icon.${t} PROPERTIES TIMEOUT 60 LABELS icon)
endforeach()
# the real textures, when this checkout has an extracted disc
if(EXISTS ${CMAKE_SOURCE_DIR}/data/DATA0_0.HD6)
  add_test(NAME icon.data COMMAND rg-icon-tests data ${_out})
  set_tests_properties(icon.data PROPERTIES TIMEOUT 60 LABELS icon
    ENVIRONMENT "RG_ICON_DATA=${CMAKE_SOURCE_DIR}/data")
endif()

foreach(t rg_icon rg-icon rg-icon-tests)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

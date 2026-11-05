# SPDX-License-Identifier: CC0-1.0
# Typed settings registry + settings-menu model (docs/SETTINGS.md).  Pure C,
# no SDL: src/host links it for the overlay and the input settings.
add_library(rg_settings STATIC
  rg_settings.h rg_settings.c rg_settings_core.c
  rg_menu.h rg_menu.c rg_menu_priv.h rg_menu_saves.c
  rg_aspect.h rg_aspect.c
  rg_display.h rg_display.c
  rg_layout.h rg_layout.c
  rg_prompts.h rg_prompts.c
  rg_texpatch.h rg_texpatch.c rg_texpatch_tab.c)
target_include_directories(rg_settings PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# port/vcall.h only (rg_aspect.c: the TaskUpdateDrawInfo_2f6ff0 override's shake step)
target_include_directories(rg_settings PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rg_settings PUBLIC rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_settings PRIVATE -Wall -Wextra)
endif()
if(WIN32)
  target_compile_definitions(rg_settings PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(NOT WIN32)
  target_link_libraries(rg_settings PUBLIC m)
endif()

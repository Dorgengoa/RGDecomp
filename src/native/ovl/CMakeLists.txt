# SPDX-License-Identifier: CC0-1.0
# Native module table for the five overlays (docs/OVERLAY.md section 8, PLAN.md D9).
#   rg_native_ovl        the manager (ovl.h interface: bind / load / active module /
#                        import dispatch / reports) + the OverlayLoadFile_100410 binding
#                        and the runtime service hook.  No retail addresses, no arena.
#   rg_ovl_native_game   the generated table (tools/gen_overlay_registry.py ->
#                        ovl_native_gen.c: per-overlay data segments with their labels,
#                        .data images, import x module table, trampolines) + the lifted
#                        ctors; OBJECT, linked only by a native-only rg-game
#                        (cmake/game_link.cmake, RG_NATIVE_OVL)
# RG_NATIVE_ONLY maps rg_ps2_overlay -> rg_native_ovl and drops rg_ps2_overlay_bind /
# rg_ovl_arena (cmake/native_only.cmake).
add_library(rg_native_ovl STATIC ovl.h ovl_gen.h ovl_native.c ovl_native_bind.c)
target_include_directories(rg_native_ovl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_ovl PUBLIC rg_flags)
if(WIN32)
  target_compile_definitions(rg_native_ovl PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_ovl PRIVATE -Wall -Wextra)
endif()

if(RG_OVL_GEN_OK AND TARGET rg_ovl_gen)
  add_library(rg_ovl_native_game OBJECT
    ${RG_OVL_GEN_DIR}/ovl_native_gen.c ${RG_OVL_GEN_DIR}/ovl_ctors_gen.c)
  set_source_files_properties(${RG_OVL_GEN_DIR}/ovl_native_gen.c PROPERTIES GENERATED TRUE)
  target_include_directories(rg_ovl_native_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(rg_ovl_native_game PRIVATE rg_flags)
  target_compile_options(rg_ovl_native_game PRIVATE -Wno-unused-variable)
  add_dependencies(rg_ovl_native_game rg_ovl_gen)
endif()

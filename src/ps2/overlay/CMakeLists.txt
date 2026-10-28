# SPDX-License-Identifier: CC0-1.0
# Overlay manager, arena form (docs/OVERLAY.md): the bring-up manager on the shared
# retail-address arena (default builds, rg-game-oracle, tests).  A native-only
# rg-game links the native module table instead (src/native/ovl, section 8); the
# generator below writes both.
#   rg_ps2_overlay        the manager core (no dependencies)
#   rg_ps2_overlay_bind   OverlayLoadFile_100410 binding + service init (hwbus resolver)
#   rg_ovl_registry_table generated registry, RG_OVL_TABLE_ONLY (no game symbols; tests)
#   rg_ovl_registry_game  generated registry + arena + lifted ctors + import
#                         trampolines, for the game link (OBJECT; references game symbols)
add_library(rg_ps2_overlay STATIC ovl.h ovl.c ovl_asm.h)
# ovl.h forwards to the shared interface in src/native/ovl (docs/OVERLAY.md section 8)
target_include_directories(rg_ps2_overlay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src/native/ovl)
target_link_libraries(rg_ps2_overlay PUBLIC rg_flags)

add_library(rg_ps2_overlay_bind STATIC ovl_bind.c)
target_link_libraries(rg_ps2_overlay_bind PUBLIC rg_ps2_overlay rg_ps2_hwbus)

foreach(t rg_ps2_overlay rg_ps2_overlay_bind)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

# ---- generated registry (tools/gen_overlay_registry.py) --------------------
# Needs Python, game/ (MANIFEST.tsv + SNAPSHOT.txt) and the snapshot repo named
# in game/SNAPSHOT.txt (git objects at its rev).  Without them the registry
# targets are simply not defined (the manager and its synthetic tests still are).
if(NOT RG_PYTHON)
  find_program(RG_PYTHON NAMES python3 python )
  find_program(RG_PYTHON NAMES python3 python)
endif()
set(RG_OVL_GEN_DIR ${CMAKE_BINARY_DIR}/overlay-gen)
set(RG_OVL_GEN_OK FALSE)
set(_snap ${CMAKE_SOURCE_DIR}/game/SNAPSHOT.txt)
if(RG_PYTHON AND EXISTS ${_snap} AND EXISTS ${CMAKE_SOURCE_DIR}/game/MANIFEST.tsv)
  file(STRINGS ${_snap} _src REGEX "^source\t")
  string(REGEX REPLACE "^source\t" "" _src "${_src}")
  if(_src AND EXISTS "${_src}")
    set(RG_OVL_GEN_OK TRUE)
  endif()
endif()
# Without the snapshot repo (a published checkout): the generator's output committed under
# pregen/overlay-gen/ (i686; its data words are filled by tools/gamedata_fill.py).
set(RG_OVL_PREGEN FALSE)
if(NOT RG_OVL_GEN_OK AND NOT RG_ARCH STREQUAL "x64"
   AND EXISTS ${CMAKE_SOURCE_DIR}/pregen/overlay-gen/ovl_native_gen.c)
  set(RG_OVL_GEN_OK TRUE)
  set(RG_OVL_PREGEN TRUE)
  set(RG_OVL_GEN_DIR ${CMAKE_SOURCE_DIR}/pregen/overlay-gen)
  message(STATUS "overlay registry: pre-generated pregen/overlay-gen (no snapshot repo)")
endif()
set(RG_OVL_DATA2C "" CACHE STRING
    "REPO@REV holding config/data2c.json (MAIN data slots into overlays); empty = the snapshot's own (docs/LINK.md)")
set(RG_OVL_GEN_OK ${RG_OVL_GEN_OK} PARENT_SCOPE)
set(RG_OVL_GEN_DIR ${RG_OVL_GEN_DIR} PARENT_SCOPE)

if(RG_OVL_GEN_OK)
  set(_gen_args --out ${RG_OVL_GEN_DIR})
  if(RG_OVL_DATA2C)
    string(REGEX REPLACE "@.*$" "" _d2c_repo "${RG_OVL_DATA2C}")
    if(EXISTS "${_d2c_repo}")
      list(APPEND _gen_args --data2c ${RG_OVL_DATA2C})
    endif()
  endif()
  if(RG_ARCH STREQUAL "x64")
    # the native module table's data images as asm words (docs/X64-PLAN.md step 3)
    list(APPEND _gen_args --arch x64)
  endif()
  set(RG_OVL_GEN_SRCS
    ${RG_OVL_GEN_DIR}/ovl_registry_gen.c
    ${RG_OVL_GEN_DIR}/ovl_arena_gen.c
    ${RG_OVL_GEN_DIR}/ovl_ctors_gen.c)
  if(RG_OVL_PREGEN)
    add_custom_target(rg_ovl_gen)
  else()
  add_custom_command(
    OUTPUT ${RG_OVL_GEN_SRCS} ${RG_OVL_GEN_DIR}/ovl_native_gen.c ${RG_OVL_GEN_DIR}/OVERLAY_REGISTRY.tsv
    COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/gen_overlay_registry.py
            --game ${CMAKE_SOURCE_DIR}/game ${_gen_args}
    DEPENDS ${CMAKE_SOURCE_DIR}/tools/gen_overlay_registry.py
            ${CMAKE_SOURCE_DIR}/tools/ovl_lift.py
            ${CMAKE_SOURCE_DIR}/tools/stages/ovlsyms.py
            ${CMAKE_SOURCE_DIR}/game/MANIFEST.tsv ${_snap}
    COMMENT "gen_overlay_registry: overlay registry from the pinned snapshot"
    VERBATIM)
  add_custom_target(rg_ovl_gen DEPENDS ${RG_OVL_GEN_SRCS})
  endif()

  # tables only: no game symbol referenced (tests/overlay real-registry test)
  add_library(rg_ovl_registry_table STATIC ${RG_OVL_GEN_DIR}/ovl_registry_gen.c)
  target_compile_definitions(rg_ovl_registry_table PRIVATE RG_OVL_TABLE_ONLY=1)
  target_link_libraries(rg_ovl_registry_table PUBLIC rg_ps2_overlay)
  add_dependencies(rg_ovl_registry_table rg_ovl_gen)

  # the arena alone (no external references): tests link it to check labels
  add_library(rg_ovl_arena STATIC ${RG_OVL_GEN_DIR}/ovl_arena_gen.c)
  target_link_libraries(rg_ovl_arena PUBLIC rg_ps2_overlay)
  add_dependencies(rg_ovl_arena rg_ovl_gen)

  # for the game link: compiled in ALL (so a generator change that does not
  # compile is caught), linked only by the game executable.
  add_library(rg_ovl_registry_game OBJECT
    ${RG_OVL_GEN_DIR}/ovl_registry_gen.c ${RG_OVL_GEN_DIR}/ovl_ctors_gen.c)
  target_link_libraries(rg_ovl_registry_game PRIVATE rg_ps2_overlay)
  target_compile_options(rg_ovl_registry_game PRIVATE -Wno-unused-variable)
  add_dependencies(rg_ovl_registry_game rg_ovl_gen)
endif()

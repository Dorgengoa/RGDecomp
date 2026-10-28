# The game executable `rg-game` (i686): every game/ image + overrides/ +
# missing/ (the rg_game_<image> OBJECT libraries of cmake/game.cmake) linked
# with all the port libraries.  docs/LINK.md.  Included at the END of the top
# CMakeLists.txt (it names targets from src/runtime, src/movie, src/trace, ...).
# EXCLUDE_FROM_ALL: `cmake --build <dir> --target rg-game`.
#
#   host entry  src/game/rg_game_main.c: movie service + overlay service hook,
#               trace symtab, rg_runtime_init; crt0 -> rg_game_entry -> Main_15e700
#   overlays    rg_ovl_registry_game (registry, lifted ctors, import
#               trampolines) + rg_ovl_arena (the shared arena, MAIN aliases); a
#               native-only rg-game with RG_NATIVE_OVL: rg_ovl_native_game (the
#               native module table, docs/OVERLAY.md section 8) + rg_native_ovl
#   NOT /LARGEADDRESSAWARE: the DMAC model reads bit 31 of a host pointer as
#   the scratchpad flag (docs/DMAC.md), so every host address must be < 2 GiB.
#
# RG_GAME_FORCE_UNRESOLVED=ON links with /FORCE:UNRESOLVED (diagnostics only:
# lists every unresolved symbol and still writes an exe that must NOT be run).
if(NOT RG_GAME_IMAGES OR NOT TARGET rg_runtime)
  message(STATUS "rg-game: not defined (needs game/ and RG_HOST)")
  return()
endif()
option(RG_GAME_FORCE_UNRESOLVED "link rg-game with /FORCE:UNRESOLVED (diagnostics)" OFF)

set(_rg_game_objs)
foreach(img ${RG_GAME_IMAGES})
  list(APPEND _rg_game_objs $<TARGET_OBJECTS:rg_game_${img}>)
endforeach()
set(_rg_game_gen)
foreach(t rg_trace_symtab_game)
  if(TARGET ${t})
    list(APPEND _rg_game_gen $<TARGET_OBJECTS:${t}>)
  else()
    message(WARNING "rg-game: ${t} missing (generator inputs absent); the link will fail")
  endif()
endforeach()

# overlays: the arena manager's generated registry (default builds, rg-game-oracle) or
# the native module table (native-only rg-game with RG_NATIVE_OVL, docs/OVERLAY.md
# section 8).  Added per executable at the end of this file (the oracle twin copies
# rg-game's SOURCES).
set(_rg_ovl_arena_objs)
set(_rg_ovl_native_objs)
if(TARGET rg_ovl_registry_game)
  set(_rg_ovl_arena_objs $<TARGET_OBJECTS:rg_ovl_registry_game>)
else()
  message(WARNING "rg-game: rg_ovl_registry_game missing (generator inputs absent); the link will fail")
endif()
if(TARGET rg_ovl_native_game)
  set(_rg_ovl_native_objs $<TARGET_OBJECTS:rg_ovl_native_game>)
endif()
set(_rg_game_ovl_objs ${_rg_ovl_arena_objs})
if(RG_NATIVE_ONLY AND RG_NATIVE_OVL)
  set(_rg_game_ovl_objs ${_rg_ovl_native_objs})
  message(STATUS "rg-game: RG_NATIVE_OVL: overlays as native modules (no arena)")
endif()

# missing/UNBOUND.tsv -> fatal stubs (docs/LINK.md "Unbound symbols")
set(_rg_unbound ${CMAKE_BINARY_DIR}/game-gen/rg_game_unbound.c)
add_custom_command(
  OUTPUT ${_rg_unbound}
  COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/gen_unbound.py
          ${CMAKE_SOURCE_DIR}/missing/UNBOUND.tsv ${_rg_unbound}
  DEPENDS ${CMAKE_SOURCE_DIR}/tools/gen_unbound.py ${CMAKE_SOURCE_DIR}/missing/UNBOUND.tsv
  COMMENT "gen_unbound: rg-game fatal stubs"
  VERBATIM)

add_executable(rg-game EXCLUDE_FROM_ALL
  ${CMAKE_SOURCE_DIR}/src/game/rg_game_main.c ${CMAKE_SOURCE_DIR}/src/game/rg_slots.c
  ${CMAKE_SOURCE_DIR}/src/game/rg_game_ss.c ${_rg_unbound} ${_rg_game_objs} ${_rg_game_gen})
target_include_directories(rg-game PRIVATE
  ${CMAKE_SOURCE_DIR}/src/runtime ${CMAKE_SOURCE_DIR}/src/movie
  ${CMAKE_SOURCE_DIR}/src/ps2/overlay ${CMAKE_SOURCE_DIR}/src/trace)
set(_rg_game_libs
  rg_runtime rg_movie_runtime rg_movie_game rg_movie
  rg_ps2_overlay_bind rg_ovl_arena rg_ps2_overlay
  rg_trace rg_trace_core
  rg_sce_kernel rg_sce_cdvd rg_sce_graphics rg_sce_sif rg_sce_padmc rg_sce_vu0 rg_sce_mpeg
  rg_crt rg_vu0
  rg_ps2_hwbus rg_ps2_spin rg_ps2_kernel rg_ps2_cdvd rg_ps2_dmac rg_ps2_gs rg_ps2_vif rg_ps2_vu
  rg_ps2_sif rg_ps2_iop rg_ps2_iop_hle rg_ps2_padmc rg_ps2_sound rg_ps2_spu
  rg_host rg_settings
  rg_savestate)   # save states (docs/TEST-FIXTURES.md): replaces malloc for the exe
# RG_NATIVE_ONLY (docs/NATIVE-ONLY.md): native-only clones, no IOP/sound/CDVD oracles
if(RG_NATIVE_ONLY)
  include(${CMAKE_SOURCE_DIR}/cmake/native_only.cmake)
  set(_rg_game_libs_all ${_rg_game_libs})
  set(_rg_game_libs)
  foreach(l ${_rg_game_libs_all})
    if(TARGET ${l})
      list(APPEND _rg_game_libs ${l})
    endif()
  endforeach()
  rg_native_only_map(_rg_game_libs ${_rg_game_libs})
  get_property(_rg_nonly_clones GLOBAL PROPERTY RG_NONLY_CLONES)
  message(STATUS "rg-game: RG_NATIVE_ONLY: native-only clones of ${_rg_nonly_clones}")
endif()
foreach(l ${_rg_game_libs})
  if(TARGET ${l})
    target_link_libraries(rg-game PRIVATE ${l})
  endif()
endforeach()

target_link_libraries(rg-game PRIVATE rg_flags)
if(TARGET rg_ubsan_census)   # RG_UBSAN census build (cmake/game.cmake, docs/UB-AUDIT.md)
  target_link_libraries(rg-game PRIVATE rg_ubsan_census)
endif()
if(TARGET rg_sbguard_census)  # RG_SBGUARD census build (cmake/game.cmake, docs/PROTOS.md)
  target_link_libraries(rg-game PRIVATE rg_sbguard_census)
endif()
if(WIN32)
  target_compile_definitions(rg-game PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_link_options(rg-game PRIVATE "LINKER:/LARGEADDRESSAWARE:NO" "LINKER:/STACK:8388608"
    "LINKER:/ERRORLIMIT:0" "LINKER:/MAP"
    # keep every MAIN data object (they form ONE contiguous image in retail
    # order, datareloc) and every function address distinct (the game compares
    # function pointers): no reference GC, no identical-code folding
    "LINKER:/OPT:NOREF" "LINKER:/OPT:NOICF"
    # save states (docs/TEST-FIXTURES.md): statics and code at the same
    # address in every run of the build (no ASLR for the exe)
    "LINKER:/DYNAMICBASE:NO")
  if(RG_GAME_FORCE_UNRESOLVED)
    target_link_options(rg-game PRIVATE "LINKER:/FORCE:UNRESOLVED")
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # The Windows options above, for an ELF link (docs/LINUX.md "The game"):
  #  /MAP                -> -Map (<target>.map in the build dir, next to the
  #                         exe; rg-game-oracle copies the option and gets its own)
  #  /OPT:NOREF /NOICF   -> no --gc-sections / --icf (both off by default in
  #                         lld and GNU ld); the explicit --no-gc-sections and
  #                         --icf=none (ELF lld has no --no-icf) keep a global
  #                         LDFLAGS from turning them on
  #  /DYNAMICBASE:NO     -> -no-pie (cmake/toolchain-linux-i686.cmake), so code
  #                         and statics are at the link address in every run
  #  /LARGEADDRESSAWARE:NO, /STACK:8M -> no switch: the guest-visible allocators
  #                         are pinned below 2 GB (crt0.c, fiber_ucontext.c) and
  #                         the main stack is `ulimit -s` (8 MB default)
  #  /ERRORLIMIT:0       -> --error-limit=0 (lld)
  target_link_options(rg-game PRIVATE "LINKER:-Map=$<TARGET_PROPERTY:NAME>.map"
    "LINKER:--no-gc-sections")
  if(CMAKE_C_COMPILER_ID MATCHES "Clang" AND RG_LD_LLD)
    target_link_options(rg-game PRIVATE "LINKER:--icf=none" "LINKER:--error-limit=0")
  endif()
  if(RG_GAME_FORCE_UNRESOLVED)
    target_link_options(rg-game PRIVATE "LINKER:--unresolved-symbols=ignore-all")
  endif()
endif()

# Renderer backend: rg_gpu (src/gpu) exists only where a backend is implemented (D3D11 on
# Windows).  Without it nothing defines RG_HAVE_GPU and rg-game gets the headless renderer
# (runtime.c gpu_start: the native frame-chain walker into the software GS model; no
# window-quality output).  docs/LINUX.md "Headless renderer" / "A Linux renderer backend".
if(NOT TARGET rg_gpu)
  message(STATUS "rg-game: no GPU backend for ${CMAKE_SYSTEM_NAME}: headless renderer "
                 "(frame-chain walker -> software GS; docs/LINUX.md)")
endif()

# RG_NATIVE_ONLY: rg-game-oracle, the same-tree default twin (the same game objects and
# host sources, the oracle-capable libraries): the comparison baseline and the link-audit
# control (docs/NATIVE-ONLY.md).  EXCLUDE_FROM_ALL; costs one link.
if(RG_NATIVE_ONLY)
  get_target_property(_rg_s rg-game SOURCES)
  add_executable(rg-game-oracle EXCLUDE_FROM_ALL ${_rg_s})
  foreach(p INCLUDE_DIRECTORIES COMPILE_DEFINITIONS COMPILE_OPTIONS LINK_OPTIONS)
    get_target_property(_rg_v rg-game ${p})
    if(_rg_v)
      set_property(TARGET rg-game-oracle PROPERTY ${p} "${_rg_v}")
    endif()
  endforeach()
  foreach(l ${_rg_game_libs_all})
    if(TARGET ${l})
      target_link_libraries(rg-game-oracle PRIVATE ${l})
    endif()
  endforeach()
  target_link_libraries(rg-game-oracle PRIVATE rg_flags)
endif()

# the overlay objects (see the top): after the twin copied rg-game's sources
target_sources(rg-game PRIVATE ${_rg_game_ovl_objs})
if(TARGET rg-game-oracle)
  target_sources(rg-game-oracle PRIVATE ${_rg_ovl_arena_objs})
endif()

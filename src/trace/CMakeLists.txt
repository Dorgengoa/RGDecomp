# SPDX-License-Identifier: CC0-1.0
# rg_trace: port-side state-trace recorder (docs/TRACE-PORT.md).
#   rg_trace_core          hash, address map, region files, recorder (no runtime)
#   rg_trace               runtime glue: RG_TRACE_* environment, VBlank observer
#   rg_trace_demo          synthetic symbols for rg-runtime-demo (linked into it)
#   rg_trace_symtab_game   OBJECT: generated PS2 symbol -> host address table,
#                          linked only by the game exe
add_library(rg_trace_core STATIC rg_trace.h blake2b.c trace_map.c trace_regions.c trace_rec.c)
target_include_directories(rg_trace_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_trace_core PUBLIC rg_ps2_overlay rg_flags)
set(_rg_trace_targets rg_trace_core)

set(RG_TRACE_GEN_DIR ${CMAKE_BINARY_DIR}/trace-gen)

if(TARGET rg_runtime)
  # timing record (docs/TIMING-LOCKSTEP.md): its site table is generated from
  # probe.py's `timing` hook set, so the port and PCSX2 sides cannot drift
  set(_tt ${CMAKE_SOURCE_DIR}/tools/trace)
  add_custom_command(
    OUTPUT ${RG_TRACE_GEN_DIR}/rg_timing_sites.h
    COMMAND ${RG_PYTHON} ${_tt}/gen_timing_sites.py --h ${RG_TRACE_GEN_DIR}/rg_timing_sites.h
    DEPENDS ${_tt}/gen_timing_sites.py ${_tt}/probe.py ${_tt}/mips.py
    COMMENT "gen_timing_sites: timing record site table"
    VERBATIM)
  add_library(rg_trace STATIC trace_runtime.c timing.c rg_timing.h ${RG_TRACE_GEN_DIR}/rg_timing_sites.h)
  target_include_directories(rg_trace PUBLIC ${RG_TRACE_GEN_DIR})
  target_link_libraries(rg_trace PUBLIC rg_trace_core rg_runtime rg_ps2_overlay rg_sce_cdvd rg_sce_padmc
                        rg_movie_game)
  add_library(rg_trace_demo STATIC demo/trace_demo_syms.c demo/trace_demo_syms.h)
  target_include_directories(rg_trace_demo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/demo)
  target_link_libraries(rg_trace_demo PUBLIC rg_trace rg_runtime_demo_guest)
  list(APPEND _rg_trace_targets rg_trace rg_trace_demo)
  # the optional hook in src/runtime/demo/runtime_demo.c (no effect without RG_TRACE_OUT)
  target_link_libraries(rg-runtime-demo PRIVATE rg_trace_demo)
  target_compile_definitions(rg-runtime-demo PRIVATE RG_WITH_TRACE=1)
endif()

# Generated game symbol table: every PS2 data symbol the trace regions need,
# as `&D_xxxxxxxx` (tools/trace/gen_port_symtab.py).  Compiled here so the
# generator output is checked on every build; only the game exe links it
# (the D_ symbols arrive with the data snapshot).
if(RG_PYTHON AND EXISTS ${CMAKE_SOURCE_DIR}/game/src)
  set(_tt ${CMAKE_SOURCE_DIR}/tools/trace)
  add_custom_command(
    OUTPUT ${RG_TRACE_GEN_DIR}/rg_trace_symtab_gen.c ${RG_TRACE_GEN_DIR}/rg_trace_symtab_gen.tsv
    COMMAND ${RG_PYTHON} ${_tt}/gen_port_symtab.py --regions ${_tt}/regions_golden.cfg
            --src ${CMAKE_SOURCE_DIR}/game/src --out ${RG_TRACE_GEN_DIR}/rg_trace_symtab_gen.c
    DEPENDS ${_tt}/gen_port_symtab.py ${_tt}/trace.py ${_tt}/regions_golden.cfg ${_tt}/regions_symbols.cfg
            ${CMAKE_SOURCE_DIR}/game/MANIFEST.tsv
    COMMENT "gen_port_symtab: trace symbol table for the game"
    VERBATIM)
  add_library(rg_trace_symtab_game OBJECT ${RG_TRACE_GEN_DIR}/rg_trace_symtab_gen.c)
  target_link_libraries(rg_trace_symtab_game PRIVATE rg_trace_core)
endif()

foreach(t ${_rg_trace_targets})
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

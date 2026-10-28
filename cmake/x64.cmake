# x64 build (P7, strategy A: a 32-bit game address space; docs/X64-PLAN.md).
# Included by CMakeLists.txt only when RG_ARCH is x64 (64-bit Windows toolchain,
# cmake/toolchain-x64-windows-clang.cmake); the i686 build never reads this file.
#
#   rg_x64_setup()     before the first target: the link-flag gate (every
#                      executable is linked through tools/x64/linkgate.py, which
#                      fails the link and deletes the exe unless its PE headers
#                      say LAA:NO / DYNAMICBASE:NO / HIGHENTROPYVA:NO / image below
#                      2 GB: tools/x64/pecheck.py) and the derived source tree
#   rg_x64_game()      after cmake/game.cmake: the x64 game flags
#   rg_x64_finalize()  at the end: src/x64/lowmem_check.c (start-up self-check:
#                      image, stack, heap, top-down VirtualAlloc below 2 GB) into
#                      every executable of the project; tests/x64
#
# The game sources of an x64 build come from the DERIVED tree RG_X64_SRC
# (tools/x64/derive.py: game/ + overrides/ + missing/ with the x64 stages ptr32,
# addr32 and vthunk applied).  Re-run derive after a re-ingest or an override
# edit, then rebuild.

macro(rg_x64_setup)
  find_program(RG_PYTHON NAMES python3 python )
  find_program(RG_PYTHON NAMES python3 python)
  if(NOT RG_PYTHON)
    message(FATAL_ERROR "x64 build: python is required (tools/x64/linkgate.py)")
  endif()
  # the link-flag gate (docs/X64-PLAN.md R2)
  set(CMAKE_C_LINKER_LAUNCHER ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/linkgate.py)
  set(CMAKE_CXX_LINKER_LAUNCHER ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/linkgate.py)
  # the derived source tree
  set(RG_X64_SRC "${CMAKE_SOURCE_DIR}/build/x64-src" CACHE PATH
      "x64 source tree derived by tools/x64/derive.py (game/, overrides/, missing/)")
  if(EXISTS ${RG_X64_SRC}/game/MANIFEST.tsv)
    set(RG_GAME_TREE "${RG_X64_SRC}/game")
    message(STATUS "x64: game sources from ${RG_X64_SRC} (tools/x64/derive.py)")
  else()
    # no derived tree: the game targets are not defined (cmake/game.cmake skips them)
    set(RG_GAME_TREE "${RG_X64_SRC}/game")
    message(STATUS "x64: no derived tree at ${RG_X64_SRC} (run tools/x64/derive.py --out ${RG_X64_SRC}); "
                   "game targets not defined")
  endif()
endmacro()

macro(rg_x64_game)
  if(TARGET rg_game_flags)
    # LLVM's __ptr32 (addrspace 271) gaps, all LOUD with these flags (docs/X64-PLAN.md R1):
    #  -fno-optimize-sibling-calls  a call through a __ptr32 function pointer the ptr32
    #     stage did not wrap in RG_FPC is an isel error, never the silent tail-call
    #     miscompile (an 8-byte load of the slot; repro build/x64-probe/lowmem/t8.c)
    #  -fno-jump-tables  SimplifyCFG's switch-to-lookup-table turns stores of function
    #     addresses into a __ptr32 table initializer ("unsupported expression in static
    #     initializer: addrspacecast")
    #  -fno-vectorize -fno-slp-vectorize  vectors of __ptr32 crash type legalisation
    #     ("Do not know how to widen/split this operator's operand")
    target_compile_options(rg_game_flags INTERFACE -fno-optimize-sibling-calls -fno-jump-tables
                           -fno-vectorize -fno-slp-vectorize)
  endif()
endmacro()

function(rg_x64_collect_exes dir out)
  get_property(_t DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
  set(_r)
  foreach(t ${_t})
    get_target_property(_ty ${t} TYPE)
    if(_ty STREQUAL "EXECUTABLE")
      list(APPEND _r ${t})
    endif()
  endforeach()
  get_property(_subs DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
  foreach(s ${_subs})
    if(NOT s MATCHES "/_deps/")
      rg_x64_collect_exes(${s} _sr)
      list(APPEND _r ${_sr})
    endif()
  endforeach()
  set(${out} ${_r} PARENT_SCOPE)
endfunction()

macro(rg_x64_finalize)
  # port libraries whose SDK structs live in game memory (SCE_P32 / CRT_P32 members:
  # src/sce/*, src/crt): the same LOUD flags as the game objects (rg_x64_game)
  foreach(d src/sce/kernel src/sce/sif src/sce/graphics src/sce/padmc src/sce/cdvd src/sce/vu0
            src/sce/mpeg src/crt)
    if(EXISTS ${CMAKE_SOURCE_DIR}/${d}/CMakeLists.txt)
      get_property(_t DIRECTORY ${CMAKE_SOURCE_DIR}/${d} PROPERTY BUILDSYSTEM_TARGETS)
      foreach(t ${_t})
        get_target_property(_ty ${t} TYPE)
        if(_ty MATCHES "LIBRARY$" AND NOT _ty STREQUAL "INTERFACE_LIBRARY")
          target_compile_options(${t} PRIVATE -fno-optimize-sibling-calls -fno-jump-tables
                                 -fno-vectorize -fno-slp-vectorize)
        endif()
      endforeach()
    endif()
  endforeach()
  # VU0 libraries outside the game objects: the same float-sqrt rounding as the game
  # objects (port/x64.h: sqrtf / __builtin_sqrtf round to nearest as the i686 CRT's
  # x87 sqrtf does, port/sqrtf_rn.h; docs/X64-PLAN.md section 0.7)
  foreach(d src/native/vu0 src/sce/vu0)
    if(EXISTS ${CMAKE_SOURCE_DIR}/${d}/CMakeLists.txt)
      get_property(_t DIRECTORY ${CMAKE_SOURCE_DIR}/${d} PROPERTY BUILDSYSTEM_TARGETS)
      foreach(t ${_t})
        get_target_property(_ty ${t} TYPE)
        if(NOT _ty STREQUAL "INTERFACE_LIBRARY")
          target_compile_options(${t} PRIVATE "SHELL:-include port/x64.h")
        endif()
      endforeach()
    endif()
  endforeach()
  add_subdirectory(tests/x64)
  rg_x64_collect_exes(${CMAKE_SOURCE_DIR} _rg_x64_exes)
  foreach(t ${_rg_x64_exes})
    target_sources(${t} PRIVATE ${CMAKE_SOURCE_DIR}/src/x64/lowmem_check.c)
  endforeach()
  list(LENGTH _rg_x64_exes _n)
  message(STATUS "x64: start-up low-address self-check in ${_n} executables")
endmacro()

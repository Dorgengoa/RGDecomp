cmake_minimum_required(VERSION 3.25)

# Rogue Galaxy PC port.  Configure with a toolchain file from cmake/ (i686
# first, PLAN.md D1); tools/build.ps1 does it on Windows.
project(rgport LANGUAGES C CXX)

# RG_ARCH, from the toolchain: i686 (PLAN.md D1: the default and shipping build,
# cmake/toolchain-i686-*.cmake) or x64 (P7 strategy A, docs/X64-PLAN.md: an x64 exe
# whose whole address space stays below 2 GB; cmake/toolchain-x64-windows-clang.cmake,
# cmake/x64.cmake).  Nothing below changes for i686.
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(RG_ARCH i686)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8 AND WIN32)
  set(RG_ARCH x64)
else()
  message(FATAL_ERROR "rgport builds i686 (cmake/toolchain-i686-*.cmake) or Windows x64 "
                      "(cmake/toolchain-x64-windows-clang.cmake, docs/X64-PLAN.md)")
endif()
message(STATUS "RG_ARCH=${RG_ARCH}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# D9 native-only configuration (docs/NATIVE-ONLY.md): rg-game links native-only clones
# of the SDK layer and runtime (RG_NATIVE_ONLY=1) and none of the IOP / SIF / pad+card
# server / sound / SPU2 / CDVD / EE-kernel HLE oracles nor the VU0 model; tests keep
# linking those directly, and rg-game-oracle (EXCLUDE_FROM_ALL) is the same-tree twin
# with the oracles.  Default ON since 2026-10-18 (docs/NATIVE-CPU.md section 8); an
# existing build dir keeps its cached value.
option(RG_NATIVE_ONLY "rg-game without the IOP/sound/CDVD/kernel HLE oracles (docs/NATIVE-ONLY.md)" ON)
# RG_NATIVE_ONLY rg-game: the overlays as a native module table (src/native/ovl, no
# retail-address arena; docs/OVERLAY.md section 8) instead of the arena manager.  Default
# ON since 2026-10-25 (gates: docs/bringup/BRINGUP-HISTORY.md "D9 residue"); OFF = the arena
# manager in the native-only exe too (A/B)
option(RG_NATIVE_OVL "native-only rg-game: overlays as native modules (docs/OVERLAY.md section 8)" ON)


# PLAN.md D2: SSE float (no x87 excess precision), MIPS-like integer and
# aliasing semantics, -O1 (the game sources: RG_GAME_OPT, default -O2 since the
# UB audit, cmake/game.cmake and docs/UB-AUDIT.md).
# (x64: no -m32; SSE2 is the baseline there)
set(RG_ARCH_FLAGS)
if(RG_ARCH STREQUAL "i686")
  set(RG_ARCH_FLAGS -m32)
endif()
set(RG_COMMON_FLAGS
  ${RG_ARCH_FLAGS} -msse2 -mfpmath=sse
  -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks
  -O1)

# The optimisation level is set ONLY by RG_COMMON_FLAGS: strip CMake's
# per-config -O2/-O3 so a Release build does not silently differ.
foreach(lang C CXX)
  foreach(cfg RELEASE RELWITHDEBINFO MINSIZEREL DEBUG)
    string(REGEX REPLACE "(^| )-O[0-9sz]( |$)" " " CMAKE_${lang}_FLAGS_${cfg} "${CMAKE_${lang}_FLAGS_${cfg}}")
  endforeach()
endforeach()

add_library(rg_flags INTERFACE)
target_compile_options(rg_flags INTERFACE ${RG_COMMON_FLAGS})
if(NOT WIN32)
  # libm is separate from libc on Linux (docs/LINUX.md); nearly every target
  # links rg_flags.
  target_link_libraries(rg_flags INTERFACE m)
endif()

# x64: the link-flag gate on every executable and the derived game tree
# (cmake/x64.cmake, docs/X64-PLAN.md step 1); before the first target
if(RG_ARCH STREQUAL "x64")
  include(cmake/x64.cmake)
  rg_x64_setup()
endif()

# ---- smoke test: proves the toolchain produces a running 32-bit exe
add_executable(rg-smoke src/host/smoke.c)
target_link_libraries(rg-smoke PRIVATE rg_flags)

enable_testing()
add_test(NAME smoke COMMAND rg-smoke)
set_tests_properties(smoke PROPERTIES LABELS port)

add_subdirectory(src/ps2/kernel)
add_subdirectory(src/sce/kernel)
add_subdirectory(src/ps2/cdvd)
add_subdirectory(src/sce/cdvd)
add_subdirectory(tests/cdvd)
add_subdirectory(src/native/fs)   # native host file service (docs/NATIVE-FS.md)
add_subdirectory(tests/native_fs)
add_subdirectory(src/native/audio)   # native audio engine (docs/NATIVE-AUDIO.md)
add_subdirectory(tests/native_audio)
add_subdirectory(src/ps2/vu)
add_subdirectory(src/ps2/vif)
add_subdirectory(tests/vu)
add_subdirectory(src/ps2/gs)
add_subdirectory(tests/gs)
add_subdirectory(src/ps2/spin)
add_subdirectory(tests/spin)
add_subdirectory(src/ps2/iop)
add_subdirectory(src/ps2/sif)
add_subdirectory(src/sce/sif)
add_subdirectory(src/ps2/padmc)
add_subdirectory(src/sce/padmc)
add_subdirectory(src/ps2/dmac)
add_subdirectory(src/sce/graphics)
add_subdirectory(tests/dmac)
add_subdirectory(src/ps2/hwbus)   # HW_R*/HW_W* register bus (docs/HWBUS.md)
add_subdirectory(tests/hwbus)
add_subdirectory(src/ps2/overlay)  # overlay manager + generated registry (docs/OVERLAY.md)
add_subdirectory(src/native/ovl)   # native module table for the overlays (docs/OVERLAY.md section 8)
add_subdirectory(tests/overlay)
# sound: SPU2 engine + sdr_driver/SK/pcm_mixer HLE (docs/SOUND.md)
add_subdirectory(src/ps2/spu)
add_subdirectory(src/ps2/iop/sound)
add_subdirectory(tests/sound)

# ---- port headers + VU0 model (docs/PORT-HEADERS.md)
# Game code sees: -include port/prelude.h, then include/ (port replacement
# headers: vu0inline.h, libvu0.h, port/*) AHEAD of game/include.
# RG_GAME_TREE: the generated game tree to build (default game/).  Diagnostic
# builds point it at a scratch ingest, e.g. the stack-guard census
# (docs/PROTOS.md "Stack-block census", RG_PROTOS_SB_GUARD).
set(RG_GAME_TREE "${CMAKE_SOURCE_DIR}/game" CACHE PATH "generated game tree (tools/ingest.py --out)")
add_library(rg_game_headers INTERFACE)
target_include_directories(rg_game_headers INTERFACE
  ${CMAKE_SOURCE_DIR}/include ${RG_GAME_TREE}/include)
if(RG_ARCH STREQUAL "x64")
  # RG_P32 / RG_FPC: the x64 spellings of the ptr32 stage (include/port/x64.h)
  target_compile_options(rg_game_headers INTERFACE "SHELL:-include port/x64.h")
endif()
target_compile_options(rg_game_headers INTERFACE
  "SHELL:-include port/prelude.h")

# VU0 macro code (docs/NATIVE-CPU.md): model = one global register file + VU
# float rules + vcallms on the VU interpreter (the bring-up model, the oracle);
# local = a register file per translation unit (cross-file protocols share a
# named context), the microprogram as native C, VU float rules (bit-identical
# to model); native = local + IEEE single arithmetic (the default, USER 10-18; not
# bit-faithful: the first battle plays out differently, docs/NATIVE-CPU.md).
set(RG_VU0_MODE "native" CACHE STRING "VU0 macro code: model | local | native")
set_property(CACHE RG_VU0_MODE PROPERTY STRINGS model local native)
set(RG_VU0_DEFS)
if(RG_VU0_MODE STREQUAL "local")
  set(RG_VU0_DEFS RG_VU0_LOCAL=1)
elseif(RG_VU0_MODE STREQUAL "native")
  set(RG_VU0_DEFS RG_VU0_LOCAL=1 RG_VU0_IEEE=1)
elseif(NOT RG_VU0_MODE STREQUAL "model")
  message(FATAL_ERROR "RG_VU0_MODE must be model, local or native (got ${RG_VU0_MODE})")
endif()
target_compile_definitions(rg_game_headers INTERFACE ${RG_VU0_DEFS})
message(STATUS "RG_VU0_MODE=${RG_VU0_MODE}")

# rg_vu0: the global register file + vcallms, built in RG_VU0_MODE (local /
# native: vcallms refuses, no interpreter use); rg_vu0_oracle: always the model
# (vcallms on the VU interpreter), for the tests that check the model itself.
foreach(t rg_vu0 rg_vu0_oracle)
  add_library(${t} STATIC src/ps2/vu0.c src/ps2/vu0_micro.c)  # + vcallms (micro mode)
  target_include_directories(${t} PUBLIC ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(${t} PRIVATE rg_flags rg_ps2_vu)
endforeach()
target_compile_definitions(rg_vu0 PRIVATE ${RG_VU0_DEFS})
target_compile_definitions(rg_vu0_oracle PRIVATE RG_VU0_ORACLE=1)

# ---- tests: u128 substitute, VU0 model + headers, vu0asm stage end to end
find_program(RG_PYTHON NAMES python3 python )
find_program(RG_PYTHON NAMES python3 python)
set(RG_XLAT_OUT ${CMAKE_BINARY_DIR}/xlat)
set(RG_XLAT_SRCS)
foreach(x push_apart lerp_gnu)
  add_custom_command(
    OUTPUT ${RG_XLAT_OUT}/${x}.c
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RG_XLAT_OUT}
    COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/portxform.py
            int128,gccvarargs,vu0asm,asmexclude
            ${CMAKE_SOURCE_DIR}/tests/xlat/${x}.c ${RG_XLAT_OUT}/${x}.c
    DEPENDS ${CMAKE_SOURCE_DIR}/tests/xlat/${x}.c ${CMAKE_SOURCE_DIR}/tools/portxform.py
    COMMENT "portxform: tests/xlat/${x}.c")
  list(APPEND RG_XLAT_SRCS ${RG_XLAT_OUT}/${x}.c)
endforeach()

# dialect `bitfield-gcc`: the staged fixture has mwcc's bitfield layout; the raw one
# (clang's MSVC layout) must fail
add_custom_command(
  OUTPUT ${RG_XLAT_OUT}/bitfields.c
  COMMAND ${CMAKE_COMMAND} -E make_directory ${RG_XLAT_OUT}
  COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/portxform.py dialect
          ${CMAKE_SOURCE_DIR}/tests/xlat/bitfields.c ${RG_XLAT_OUT}/bitfields.c
  DEPENDS ${CMAKE_SOURCE_DIR}/tests/xlat/bitfields.c ${CMAKE_SOURCE_DIR}/tools/portxform.py
  COMMENT "portxform dialect: tests/xlat/bitfields.c")
add_executable(rg-test-bitfields ${RG_XLAT_OUT}/bitfields.c)
target_link_libraries(rg-test-bitfields PRIVATE rg_flags)
add_test(NAME dialect.bitfields COMMAND rg-test-bitfields)
add_executable(rg-test-bitfields-raw tests/xlat/bitfields.c)
target_link_libraries(rg-test-bitfields-raw PRIVATE rg_flags)
add_test(NAME dialect.bitfields_control COMMAND rg-test-bitfields-raw)
set_tests_properties(dialect.bitfields dialect.bitfields_control PROPERTIES LABELS port)
set_tests_properties(dialect.bitfields_control PROPERTIES WILL_FAIL TRUE)

add_executable(rg-test-u128 tests/test_u128.c tests/test_u128_cpp.cpp)
target_include_directories(rg-test-u128 PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rg-test-u128 PRIVATE rg_flags)
add_test(NAME u128 COMMAND rg-test-u128)
set_tests_properties(u128 PROPERTIES LABELS port)

add_executable(rg-test-vu0 tests/test_vu0.c tests/test_libvu0.c ${RG_XLAT_SRCS})
target_link_libraries(rg-test-vu0 PRIVATE rg_flags rg_game_headers rg_vu0_oracle)
target_compile_definitions(rg-test-vu0 PRIVATE RG_VU0_ORACLE=1)  # checks the model itself
add_test(NAME vu0 COMMAND rg-test-vu0)
set_tests_properties(vu0 PROPERTIES LABELS port)

# ---- game/ as OBJECT libraries rg_game_<image> + umbrella rg_game_objs
# (EXCLUDE_FROM_ALL; source list from game/MANIFEST.tsv; cmake/game.cmake)
include(cmake/game.cmake)
if(RG_ARCH STREQUAL "x64")
  rg_x64_game()
endif()
add_subdirectory(tests/devirt)    # devirt stage: layout, real fixtures, retail cross-check
add_subdirectory(tests/protos)    # protos stage: ABI regression fixture + deliberate-fault controls

# ---- excluded-symbol providers (docs/BINDINGS.md): libvu0 on the VU0 model,
# the C/C++ runtime under game names; tests compile overrides with the game
# flags, so this comes after cmake/game.cmake.  ctest -L bindings
add_subdirectory(src/sce/vu0)
add_subdirectory(src/native/vu0)   # libvu0 + microprogram as plain C (docs/NATIVE-CPU.md section 9)
add_subdirectory(src/crt)
add_subdirectory(src/sce/mpeg)   # libmpeg names of the never-run movie decoder layer
add_subdirectory(tests/bindings)

# ---- host shell: SDL3 window/input/audio/pacing (docs/HOST.md).  Needs the
# GS model (demo) and RG_PYTHON (tests), so it comes after both.
option(RG_HOST "Build src/host (fetches + builds SDL3, docs/HOST.md)" ON)
# typed settings registry + menu model (docs/SETTINGS.md); pure C, no SDL
add_subdirectory(src/settings)
if(RG_HOST)
  add_subdirectory(src/host)
  add_subdirectory(tests/host)
  # registry + input-action layer tests (docs/SETTINGS.md, docs/INPUT.md)
  add_subdirectory(tests/settings)
endif()

# ---- GPU GS renderer: Direct3D 11, Windows only (docs/GPU.md).  After
# src/host so it can give rg-host-demo its --gpu path.
add_subdirectory(src/gpu)
add_subdirectory(tests/gpu)
add_subdirectory(src/native/render)   # native renderer, scene side (docs/NATIVE-RENDER.md)

# ---- platform runtime: boots every model under the host shell (docs/RUNTIME.md)
if(RG_HOST)
  add_subdirectory(src/runtime)
  add_subdirectory(tests/runtime)
endif()

# ---- movies: CC0 MPEG-2 decoder + movie service replacing the game's movie layer
# (docs/MOVIE.md).  After src/host so rg-movie-play gets its --window path.
add_subdirectory(src/movie)
add_subdirectory(tests/movie)

# ---- state-trace recorder: the port side of the PCSX2 lockstep (docs/TRACE-PORT.md).
# After src/runtime: it hooks rg-runtime-demo and uses rg_runtime when RG_HOST is on.
add_subdirectory(src/trace)
add_subdirectory(tests/trace)

# ---- port save states / test fixtures (docs/TEST-FIXTURES.md): rg-game only.
add_subdirectory(src/savestate)

# ---- the game executable rg-game (EXCLUDE_FROM_ALL; docs/LINK.md).  Last: it
# links the game objects (cmake/game.cmake) with every port library above.
include(cmake/game_link.cmake)
# save-state tests (docs/TEST-FIXTURES.md): need the rg-game target
add_subdirectory(tests/fixtures)
# D9 link gate (docs/NATIVE-ONLY.md): reads the rg-game map
add_subdirectory(tests/native_only)

# x64: start-up low-address self-check in every executable + tests/x64 (cmake/x64.cmake)
if(RG_ARCH STREQUAL "x64")
  rg_x64_finalize()
endif()


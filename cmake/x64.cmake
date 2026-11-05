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
  # the link-flag gate (docs/X64-PLAN.md R2).  Linux: ld.lld itself rejects an R_X86_64_32
  # out of range or in a PIE (cmake/toolchain-linux-x64.cmake, docs/LINUX.md "x64 Linux")
  if(WIN32)
    set(CMAKE_C_LINKER_LAUNCHER ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/linkgate.py)
    set(CMAKE_CXX_LINKER_LAUNCHER ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/linkgate.py)
  endif()
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
    if(NOT WIN32)
      # x64 Linux (SysV), -mstackrealign (docs/LINUX.md "x64 Linux"):
      #  (1) a `void` forwarder that retail tail-called (devirt slot thunks) is read as
      #      returning its callee's RAX, as on i686 / Win64.  Plain SysV clang aligns a 1-slot
      #      frame with `pushq %rax` ... `popq %rax`: the caller read the thunk's own address
      #      (boot crash, IterInit_370170).  A realigned frame ends `movq %rbp, %rsp; popq %rbp`
      #      (gate tools/linux/voidret_scan.py: 0 game functions end in `popq %rax; ret`);
      #  (2) locals keep the Win64 build's ORDER: X86 orderFrameObjects reverses the slot order
      #      for frames addressed off the frame pointer (-fno-omit-frame-pointer, the first fix
      #      tried), not for realigned / rsp-addressed ones.  Game code relies on retail's
      #      adjacency of escaping locals: CollFrameTreeCalcBounds_16be80 hands &spB0 to a
      #      slot that writes spB0 AND spC0 (32 bytes); with the reversed order the second
      #      half overwrote saved registers (fault in BoundsFrom4Points_13df00, field ~2,100).
      target_compile_options(rg_game_flags INTERFACE -mstackrealign)
    endif()
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
  if(WIN32)
    add_subdirectory(tests/x64)   # PE / VirtualAlloc / TEB gates (Linux: lowmem_linux.c at start-up)
  endif()
  # dialect.bitfields: the x64 game gets the dialect stage AND the ptr32 stage
  # (tools/x64/derive.py); the fixture's G holds a `u8 *` that is 4 bytes in game memory,
  # so the x64 test compiles the dialect output after the ptr32 stage (docs/X64-PLAN.md 0.8)
  if(TARGET rg-test-bitfields)
    add_custom_command(
      OUTPUT ${RG_XLAT_OUT}/bitfields_x64.c
      COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/stages/ptr32.py ${RG_XLAT_OUT}/bitfields.c
              --out ${RG_XLAT_OUT}/bitfields_x64.c
      DEPENDS ${RG_XLAT_OUT}/bitfields.c ${CMAKE_SOURCE_DIR}/tools/stages/ptr32.py
      COMMENT "ptr32 stage: the dialect.bitfields fixture (x64)")
    set_property(TARGET rg-test-bitfields PROPERTY SOURCES ${RG_XLAT_OUT}/bitfields_x64.c)
    target_include_directories(rg-test-bitfields PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_compile_options(rg-test-bitfields PRIVATE "SHELL:-include port/x64.h")
  endif()
  rg_x64_collect_exes(${CMAKE_SOURCE_DIR} _rg_x64_exes)
  foreach(t ${_rg_x64_exes})
    if(WIN32)
      target_sources(${t} PRIVATE ${CMAKE_SOURCE_DIR}/src/x64/lowmem_check.c)
      # a link map beside every x64 executable: lowmem_check.c's crash report prints
      # module + RVA, tools/x64/rva2sym.py names them through it (rg-game has its own /MAP)
      if(NOT t MATCHES "^rg-game")
        target_link_options(${t} PRIVATE "LINKER:/MAP")
      endif()
    else()
      # Linux: the glibc heap pinned low + the start-up check (docs/LINUX.md "x64 Linux")
      target_sources(${t} PRIVATE ${CMAKE_SOURCE_DIR}/src/x64/lowmem_linux.c)
    endif()
  endforeach()
  # i686-only targets and tests (docs/X64-PLAN.md 0.8 "ctest on x64"): kept out of ALL and
  # DISABLED (ctest lists them as "Not Run (Disabled)"), label i686_only.
  #  rg_ovl_registry_game: the arena overlay registry of rg-game-oracle (the emulation twin,
  #     not built for x64); i686 data2c `(uint32_t)sym` initializers.  x64 rg-game links the
  #     native module table (gen_overlay_registry.py --arch x64).
  #  protos.abi*: the protos stage's i686 call-ABI fixture (x87 returns, soft-double bit
  #     transport, i686 data2c `(u32)&fn` words; the controls need the i686 faults).  The
  #     x64 counterpart is x64.narrowabi; the stage itself runs on x64 (protos.stage*).
  if(TARGET rg_ovl_registry_game)
    set_target_properties(rg_ovl_registry_game PROPERTIES EXCLUDE_FROM_ALL TRUE)
  endif()
  foreach(v ok providers bits wide vslot abi2 shortagg abi3)
    if(TARGET rg-protos-abi-${v})
      set_target_properties(rg-protos-abi-${v} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()
  endforeach()
  set_tests_properties(protos.abi protos.abi_control_providers protos.abi_control_bits
                       protos.abi_control_wide protos.abi_control_vslot protos.abi_control_abi2
                       protos.abi_control_shortagg protos.abi_control_abi3
                       DIRECTORY ${CMAKE_SOURCE_DIR}/tests/protos
                       PROPERTIES DISABLED TRUE LABELS "protos;i686_only")
  #  protos.irabi(_control): every manual call vs its definition's i686 STACK-WORD signature
  #     (tools/bringup/protos_deficits.py --ir); compiled for x64 every pointer is a q word.
  #     The x64 call ABI is checked by x64.narrowabi.
  if(RG_PYTHON)
    set_tests_properties(protos.irabi protos.irabi_control DIRECTORY ${CMAKE_SOURCE_DIR}/tests/protos
                         PROPERTIES DISABLED TRUE LABELS "protos;i686_only")
    #  protos.f32args(_control): the i686 STACK layout of each slot call's view vs its retail
    #     targets, over the i686 game tree; on the derived tree the data2c vtables are asm
    #     (addr32) and the views widened, so the census was vacuous (control "passed": 0 rows).
    #     The x64 counterpart (Win64 register classes) is x64.vcmdecide (X64-PLAN 0.11).
    set_tests_properties(protos.f32args protos.f32args_control DIRECTORY ${CMAKE_SOURCE_DIR}/tests/protos
                         PROPERTIES DISABLED TRUE LABELS "protos;i686_only")
  endif()
  list(LENGTH _rg_x64_exes _n)
  message(STATUS "x64: start-up low-address self-check in ${_n} executables")
endmacro()

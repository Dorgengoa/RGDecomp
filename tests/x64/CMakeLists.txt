# SPDX-License-Identifier: CC0-1.0
# x64 build gates (docs/X64-PLAN.md step 1), ctest label `x64`; only an x64 build
# (RG_ARCH=x64, cmake/x64.cmake) adds this directory.
#   x64.lowmem_link            tools/x64/pecheck.py on rg-smoke.exe and rg-x64-lowmem.exe
#                              (and rg-game.exe once built): LAA off, no DYNAMICBASE /
#                              HIGHENTROPYVA, image below 2 GB
#   x64.lowmem_link_control    the same check on rg-x64-lowmem-ctl.exe, linked WITH
#                              /LARGEADDRESSAWARE /DYNAMICBASE /HIGHENTROPYVA and the
#                              default 0x140000000 base (and without the linker launcher,
#                              which would delete it): must FAIL
#   x64.linkgate_control       tools/x64/linkgate.py around a fresh link of the same bad
#                              exe at test time: the launcher must fail the link
#   x64.lowmem_runtime         rg-x64-lowmem: heap / VirtualAlloc / thread and fiber stacks
#                              / image below 2 GB at run time (+ the start-up self-check)
add_executable(rg-x64-lowmem lowmem_test.c)
target_link_libraries(rg-x64-lowmem PRIVATE rg_flags)
add_test(NAME x64.lowmem_runtime COMMAND rg-x64-lowmem)

add_executable(rg-x64-lowmem-ctl ${CMAKE_SOURCE_DIR}/src/host/smoke.c)
target_link_libraries(rg-x64-lowmem-ctl PRIVATE rg_flags)
target_link_options(rg-x64-lowmem-ctl PRIVATE
  "LINKER:/LARGEADDRESSAWARE" "LINKER:/DYNAMICBASE" "LINKER:/HIGHENTROPYVA" "LINKER:/BASE:0x140000000")
set_target_properties(rg-x64-lowmem-ctl PROPERTIES C_LINKER_LAUNCHER "" CXX_LINKER_LAUNCHER "")

set(_pc ${CMAKE_SOURCE_DIR}/tools/x64/pecheck.py)
add_test(NAME x64.lowmem_link
         COMMAND ${RG_PYTHON} ${_pc} $<TARGET_FILE:rg-smoke> $<TARGET_FILE:rg-x64-lowmem>)
add_test(NAME x64.lowmem_link_control COMMAND ${RG_PYTHON} ${_pc} $<TARGET_FILE:rg-x64-lowmem-ctl>)

add_test(NAME x64.linkgate_control
         COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/linkgate.py
                 ${CMAKE_C_COMPILER} --target=x86_64-pc-windows-msvc -fuse-ld=lld
                 -nostdlib ${CMAKE_CURRENT_SOURCE_DIR}/ctl_entry.c
                 -o ${CMAKE_CURRENT_BINARY_DIR}/linkgate_ctl.exe
                 -Wl,/ENTRY:rg_ctl_entry,/SUBSYSTEM:CONSOLE
                 -Wl,/LARGEADDRESSAWARE,/DYNAMICBASE,/HIGHENTROPYVA,/BASE:0x140000000)
# the controls must fail FOR THE GATE'S REASON (not a compile/link error)
set_tests_properties(x64.lowmem_link_control x64.linkgate_control PROPERTIES
  PASS_REGULAR_EXPRESSION "FAIL: LARGE_ADDRESS_AWARE is set")

set_tests_properties(x64.lowmem_runtime x64.lowmem_link x64.lowmem_link_control x64.linkgate_control
                     PROPERTIES LABELS x64)

# x64.fiber_arena (step 4): the fixed-address fiber switch on x64 (callee-saved GPR / xmm,
# MXCSR per fiber, SEH on a fiber stack: TEB stack fields)
add_executable(rg-x64-fiber-arena fiber_arena_test.c)
target_link_libraries(rg-x64-fiber-arena PRIVATE rg_flags rg_native_fiber)
add_test(NAME x64.fiber_arena COMMAND rg-x64-fiber-arena)
set_tests_properties(x64.fiber_arena PROPERTIES LABELS x64 PASS_REGULAR_EXPRESSION "fiber arena: ok")

# x64.layouts (step 2 gate, label x64-long): tools/x64/xprobe.py --layout --check on every
# 25th game TU of an i686 build's compile db (RG_X64_I686_DB): the derived x64 tree must
# compile and give every game record its i686 layout.  x64.layouts_control: the same on the
# ORIGINAL tree (no ptr32 stage) must FAIL.  Full run: --every 1 (about an hour).
set(RG_X64_I686_DB "" CACHE PATH "an i686 build dir (compile_commands.json) for the x64 layout gate")
if(RG_X64_I686_DB AND EXISTS ${RG_X64_I686_DB}/compile_commands.json)
  set(_xp ${CMAKE_SOURCE_DIR}/tools/x64/xprobe.py)
  add_test(NAME x64.layouts COMMAND ${RG_PYTHON} ${_xp} --db ${RG_X64_I686_DB}
           --src ${RG_X64_SRC} --out ${CMAKE_CURRENT_BINARY_DIR}/layouts --layout --every 25 --check)
  add_test(NAME x64.layouts_control COMMAND ${RG_PYTHON} ${_xp} --db ${RG_X64_I686_DB}
           --src ${CMAKE_SOURCE_DIR} --out ${CMAKE_CURRENT_BINARY_DIR}/layouts_ctl --layout --every 25 --check)
  set_tests_properties(x64.layouts_control PROPERTIES PASS_REGULAR_EXPRESSION " [1-9][0-9]* differing game records -> FAIL")
  set_tests_properties(x64.layouts x64.layouts_control PROPERTIES LABELS x64-long TIMEOUT 3600)
endif()

# x64.sqrtf_rn (section 0.7): the float sqrt of game code rounds to nearest under the guest
# MXCSR as on i686 (port/sqrtf_rn.h); every 7th float bit pattern (denormals included).
# x64.sqrtf_rn_control: a raw sqrtss under the guest MXCSR must differ.
add_executable(rg-x64-sqrtf-rn sqrtf_rn_test.c)
target_include_directories(rg-x64-sqrtf-rn PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rg-x64-sqrtf-rn PRIVATE rg_flags)
add_test(NAME x64.sqrtf_rn COMMAND rg-x64-sqrtf-rn --step 7)
add_test(NAME x64.sqrtf_rn_control COMMAND rg-x64-sqrtf-rn --control --step 7)
set_tests_properties(x64.sqrtf_rn PROPERTIES LABELS x64 PASS_REGULAR_EXPRESSION "sqrtf_rn: ok")
set_tests_properties(x64.sqrtf_rn_control PROPERTIES LABELS x64 PASS_REGULAR_EXPRESSION " [1-9][0-9]* differ")

# x64.datalayout (section 0.7): the data layer keeps retail's relative layout on x64
# (tools/x64/datalayout.py: host - retail address constant along every run, compared with
# the i686 map of RG_X64_I686_DB; x86-64 clang 16-aligns arrays >= 16 bytes unless the
# derive pass `dalign` pins them).  Needs rg-game built in both dirs.
if(RG_X64_I686_DB AND EXISTS ${RG_X64_I686_DB}/compile_commands.json)
  add_test(NAME x64.datalayout
           COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/datalayout.py
                   ${RG_X64_I686_DB}/rg-game.map ${CMAKE_BINARY_DIR}/rg-game.map --show 10)
  set_tests_properties(x64.datalayout PROPERTIES LABELS x64)
endif()

# x64.narrowabi (section 0.7): no caller declaration in the derived tree disagrees with
# its definition on a 1/2-byte integer argument or a narrow return (i686 extends small
# integers, Win64 does not; tools/x64/narrowabi.py, derive pass `narrowabi`).
add_test(NAME x64.narrowabi
         COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/x64/narrowabi.py --root ${RG_X64_SRC} --check)
set_tests_properties(x64.narrowabi PROPERTIES LABELS x64 TIMEOUT 900)

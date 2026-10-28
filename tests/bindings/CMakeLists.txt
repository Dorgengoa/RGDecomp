# SPDX-License-Identifier: CC0-1.0
# ctest -L bindings: src/sce/vu0, src/crt, and the override lanes
# (docs/BINDINGS.md).  The override sources under test are compiled with the
# game flags (rg_game_flags: -include port/prelude.h, game headers).
#
# Two builds of the same tests: `bindings` must pass; `bindings.control`
# (-DRG_BT_WRONG flips one expectation per suite) must FAIL, proving the
# checks are armed.
set(RG_BT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# override lanes with tests: lane name -> its test file + the overrides it calls
set(RG_BT_LANES)
set(RG_BT_LANE_SRCS)
include(${RG_BT_DIR}/lanes.cmake OPTIONAL)
# An override dropped because the snapshot now has the function as C (the
# d784320c de-asm, docs/LINK.md "Overrides") is tested through its game/ file:
# same lane, same expectations, as in the game build (overrides/ else game/).
set(_bt_srcs)
foreach(s IN LISTS RG_BT_LANE_SRCS)
  if(NOT EXISTS ${s} AND s MATCHES "/overrides/(.*)$")
    set(s ${CMAKE_SOURCE_DIR}/game/${CMAKE_MATCH_1})
  endif()
  if(EXISTS ${s})
    list(APPEND _bt_srcs ${s})
  endif()
endforeach()
set(RG_BT_LANE_SRCS ${_bt_srcs})

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/lanes.inc.tmp "")
foreach(l IN LISTS RG_BT_LANES)
  file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/lanes.inc.tmp "BT_LANE(${l})\n")
endforeach()
configure_file(${CMAKE_CURRENT_BINARY_DIR}/lanes.inc.tmp
               ${CMAKE_CURRENT_BINARY_DIR}/gen/lanes.inc COPYONLY)

foreach(v IN ITEMS pass wrong)
  set(t rg-bindings-tests)
  if(v STREQUAL "wrong")
    set(t rg-bindings-tests-wrong)
  endif()
  add_executable(${t}
    ${RG_BT_DIR}/bindings_main.c
    ${RG_BT_DIR}/stubs.c
    ${RG_BT_DIR}/test_sce_vu0.c
    ${RG_BT_DIR}/test_crt.c
    ${RG_BT_DIR}/platform_host.c)
  target_include_directories(${t} PRIVATE ${RG_BT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/gen)
  # platform_host.c: kernel HLE + hwbus (GS/DMAC/VIF) for the handler lane,
  # the VU interpreter + retail ELF reader for the vcallms lane
  target_link_libraries(${t} PRIVATE rg_sce_vu0_oracle rg_crt rg_sce_kernel rg_ps2_hwbus
    rg_ps2_vif rg_vu_retail rg_vu0_oracle rg_flags)
  # these suites check the VU0 model's register side effects across files:
  # always the bring-up model, whatever RG_VU0_MODE (docs/NATIVE-CPU.md)
  target_compile_definitions(${t} PRIVATE RG_VU0_ORACLE=1)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(RG_BT_LANE_SRCS AND TARGET rg_game_flags)
    add_library(${t}-ovr OBJECT ${RG_BT_LANE_SRCS})
    target_include_directories(${t}-ovr PRIVATE ${RG_BT_DIR})
    target_link_libraries(${t}-ovr PRIVATE rg_game_flags)
    target_compile_definitions(${t}-ovr PRIVATE RG_VU0_ORACLE=1)
    target_link_libraries(${t} PRIVATE ${t}-ovr)
    if(v STREQUAL "wrong")
      target_compile_definitions(${t}-ovr PRIVATE RG_BT_WRONG)
    endif()
  endif()
  if(v STREQUAL "wrong")
    target_compile_definitions(${t} PRIVATE RG_BT_WRONG)
  endif()
endforeach()

add_test(NAME bindings COMMAND rg-bindings-tests)
set_tests_properties(bindings PROPERTIES LABELS bindings TIMEOUT 120)
add_test(NAME bindings.control COMMAND rg-bindings-tests-wrong)
set_tests_properties(bindings.control PROPERTIES LABELS bindings TIMEOUT 120 WILL_FAIL TRUE)
# a suite that cannot run (vcallms without the retail ELF) makes a run of
# only that suite exit 77 = skipped
# each suite's control must fail on its own, too
foreach(s IN ITEMS sce_vu0 crt)
  add_test(NAME bindings.control.${s} COMMAND rg-bindings-tests-wrong ${s})
  set_tests_properties(bindings.control.${s} PROPERTIES LABELS bindings TIMEOUT 120 WILL_FAIL TRUE)
endforeach()
foreach(l IN LISTS RG_BT_LANES)
  add_test(NAME bindings.control.ovr_${l} COMMAND rg-bindings-tests-wrong ovr_${l})
  set_tests_properties(bindings.control.ovr_${l} PROPERTIES LABELS bindings TIMEOUT 120 WILL_FAIL TRUE
    SKIP_RETURN_CODE 77)
endforeach()

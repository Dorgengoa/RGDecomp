# SPDX-License-Identifier: CC0-1.0
# protos stage ABI regression tests (docs/PROTOS.md): ctest -L protos
#
#   protos.stage            the stage over fixture/ is idempotent and makes the expected
#                           per-site decisions (PROTOS.tsv / outputs, run_stage.py --check)
#   protos.stage_control    the same with the provider table removed: must FAIL
#   protos.abi              the staged fixture linked against native providers: soft-double
#                           bit transport, x87 void callers, missing-arg pass-through, lane
#                           remap, hosted static, address alias, double carriers, virtual
#                           tail value (test_main.c)
#   protos.abi_control_providers / _bits / _wide / _vslot / _abi2   the same fixture staged with a
#                           deliberate fault (no provider table / double handled as an integer /
#                           no 64-bit carrier rules / no vslot-lane rule / none of the 2026-10-18
#                           rules: ee-round-floor, def-v0-return, u128-view, extern "C" block
#                           linkage, overlay-import tail) / no short-agg rule (shortagg): must FAIL
#   protos.stage_control_shortagg   run_stage --check without rule short-agg: must FAIL
#   protos.stage_control_abi3 / protos.abi_control_abi3   without the 2026-10-25 manual-row
#                           rules (agg-view, u128-view extra lane, ret-narrow-view, type
#                           macros; run_stage.py --fault abi3): must FAIL
#   protos.deficits         tools/bringup/protos_deficits.py over game/: every call the stage
#                           left short of its definition (or spelled with a by-value struct
#                           return against a scalar definition) has an override; control
#                           protos.deficits_control (--ignore-overrides) must FAIL
set(RG_PROTOS_STAGE ${CMAKE_SOURCE_DIR}/tools/stages/protos.py
    ${CMAKE_SOURCE_DIR}/tools/stages/asmflow.py)
set(RG_PROTOS_RUN ${CMAKE_CURRENT_SOURCE_DIR}/run_stage.py)
set(RG_PROTOS_FIX ${CMAKE_CURRENT_SOURCE_DIR}/fixture)
file(GLOB_RECURSE _fix_inputs CONFIGURE_DEPENDS ${RG_PROTOS_FIX}/*)
# staged fixture files compiled into the test (the overlay-import callers and the
# asm placeholder are checked as text only)
set(RG_PROTOS_UNITS
    src/main/soft/SoftMul_100000.c src/main/x87/TouchMany_100030.c
    src/main/arity/MatFromQuatFull_13c4c0.c src/main/arity/FixCopyUser_13c4e0.c src/main/lane/ModelObjSetMotionRate_1add50.c
    src/main/hosted/Host_200000.c src/main/hosted/User_200200.c
    src/main/alias/Target_300000.c src/main/alias/AliasUser_300100.c
    src/main/dbl/DoubleLess_1002b0.c src/main/dbl/IsNeg_500000.c
    src/main/menu/IconRecId_2a2230.c src/main/listing/WideFlags_400c00.c
    src/main/listing/WideRet_400d00.c src/main/listing/ZextFlags_400e40.c
    src/main/vslot/VStep_401000.c src/main_data/data2c_00480000.c src/main_data/data2c_00480020.c
    src/main/abi2/Abi2_401200.c src/main/abi2/Abi2User_401400.c src/main/abi2/LinkCpp_401500.cpp
    src/main/abi2/HandleGet_401900.c src/main/abi2/HandleUser_401940.c
    src/main/abi3/GaijiDraw_402000.c src/main/abi3/GaijiUser_402040.c
    src/main/abi3/PushApart_402080.c src/main/abi3/PushUser_4020a0.c
    src/main/abi3/Low8Sum_4020c0.c src/main/abi3/NarrowUser_4020e0.cpp
    src/main/abi3/NarrowPtrUser_402100.cpp)

foreach(v ok providers bits wide vslot abi2 shortagg abi3)
  set(_out ${CMAKE_BINARY_DIR}/protos/${v})
  set(_fault)
  if(NOT v STREQUAL "ok")
    set(_fault --fault ${v})
  endif()
  set(_gen ${_out}/include/port/game_protos.h ${_out}/src/main/obj/IconRec_3ae3e0.cpp)
  foreach(u ${RG_PROTOS_UNITS})
    list(APPEND _gen ${_out}/${u})
  endforeach()
  add_custom_command(
    OUTPUT ${_gen}
    COMMAND ${RG_PYTHON} ${RG_PROTOS_RUN} --out ${_out} ${_fault}
    DEPENDS ${RG_PROTOS_RUN} ${RG_PROTOS_STAGE} ${_fix_inputs}
    COMMENT "protos: stage tests/protos/fixture (${v})")
  set(_exe rg-protos-abi-${v})
  add_executable(${_exe} test_main.c test_vcall.cpp providers_impl.c
                 ${RG_PROTOS_FIX}/overrides/src/main/vec/VecLen_1cb3c0.c ${_gen})
  set_source_files_properties(${_out}/include/port/game_protos.h
                              ${_out}/src/main/obj/IconRec_3ae3e0.cpp
                              PROPERTIES HEADER_FILE_ONLY TRUE)
  set_source_files_properties(test_vcall.cpp PROPERTIES
      COMPILE_DEFINITIONS "STAGED_ICONREC=\"${_out}/src/main/obj/IconRec_3ae3e0.cpp\""
      OBJECT_DEPENDS ${_out}/src/main/obj/IconRec_3ae3e0.cpp)
  target_include_directories(${_exe} PRIVATE ${_out}/include ${RG_PROTOS_FIX}/include
                             ${CMAKE_CURRENT_SOURCE_DIR})
  # the game-file C flags (cmake/game.cmake): views the stage leaves alone still compile
  target_compile_options(${_exe} PRIVATE -w $<$<COMPILE_LANGUAGE:C>:-Wno-int-conversion
      -Wno-incompatible-pointer-types -Wno-implicit-function-declaration>)
  target_link_libraries(${_exe} PRIVATE rg_flags)
endforeach()

add_test(NAME protos.abi COMMAND rg-protos-abi-ok)
add_test(NAME protos.abi_control_providers COMMAND rg-protos-abi-providers)
add_test(NAME protos.abi_control_bits COMMAND rg-protos-abi-bits)
add_test(NAME protos.abi_control_wide COMMAND rg-protos-abi-wide)
add_test(NAME protos.abi_control_vslot COMMAND rg-protos-abi-vslot)
add_test(NAME protos.abi_control_abi2 COMMAND rg-protos-abi-abi2)
add_test(NAME protos.abi_control_shortagg COMMAND rg-protos-abi-shortagg)
add_test(NAME protos.abi_control_abi3 COMMAND rg-protos-abi-abi3)
set_tests_properties(protos.abi_control_providers protos.abi_control_bits
                     protos.abi_control_wide protos.abi_control_vslot protos.abi_control_abi2
                     protos.abi_control_shortagg protos.abi_control_abi3 PROPERTIES WILL_FAIL TRUE)
add_test(NAME protos.stage COMMAND ${RG_PYTHON} ${RG_PROTOS_RUN}
         --out ${CMAKE_BINARY_DIR}/protos/check --check)
add_test(NAME protos.stage_control COMMAND ${RG_PYTHON} ${RG_PROTOS_RUN}
         --out ${CMAKE_BINARY_DIR}/protos/check_control --check --fault providers)
add_test(NAME protos.stage_control_shortagg COMMAND ${RG_PYTHON} ${RG_PROTOS_RUN}
         --out ${CMAKE_BINARY_DIR}/protos/check_shortagg --check --fault shortagg)
add_test(NAME protos.stage_control_abi3 COMMAND ${RG_PYTHON} ${RG_PROTOS_RUN}
         --out ${CMAKE_BINARY_DIR}/protos/check_abi3 --check --fault abi3)
set_tests_properties(protos.stage_control protos.stage_control_shortagg protos.stage_control_abi3
                     PROPERTIES WILL_FAIL TRUE)
set_tests_properties(protos.abi protos.abi_control_providers protos.abi_control_bits
                     protos.abi_control_wide protos.abi_control_vslot protos.abi_control_abi2
                     protos.abi_control_shortagg protos.abi_control_abi3 protos.stage
                     protos.stage_control protos.stage_control_shortagg protos.stage_control_abi3
                     PROPERTIES LABELS protos TIMEOUT 60)

# vu0frame stage (tools/stages/vu0frame.py, docs/UB-AUDIT.md): frames, frame helpers,
# declarations, address-taken helpers, idempotence; control = no helpers (must FAIL)
if(RG_PYTHON)
  add_test(NAME protos.vu0frame COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_vu0frame.py)
  add_test(NAME protos.vu0frame_control
           COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_vu0frame.py control)
  set_tests_properties(protos.vu0frame protos.vu0frame_control PROPERTIES LABELS protos TIMEOUT 60)
  set_tests_properties(protos.vu0frame_control PROPERTIES WILL_FAIL TRUE)
endif()

# retwiden stage (tools/stages/retwiden.py, docs/PROTOS.md "retwiden"): narrow returns of
# address-taken functions widened; control = stage disabled (must FAIL)
if(RG_PYTHON)
  add_test(NAME protos.retwiden COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_retwiden.py)
  add_test(NAME protos.retwiden_control
           COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_retwiden.py control)
  set_tests_properties(protos.retwiden protos.retwiden_control PROPERTIES LABELS protos TIMEOUT 60)
  set_tests_properties(protos.retwiden_control PROPERTIES WILL_FAIL TRUE)
endif()

# wideret stage (tools/stages/wideret.py, docs/PROTOS.md "wideret"): 64-bit returns through
# chains / accumulators / helpers; control = stage disabled (must FAIL)
if(RG_PYTHON)
  add_test(NAME protos.wideret COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_wideret.py)
  add_test(NAME protos.wideret_control
           COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_wideret.py control)
  set_tests_properties(protos.wideret protos.wideret_control PROPERTIES LABELS protos TIMEOUT 60)
  set_tests_properties(protos.wideret_control PROPERTIES WILL_FAIL TRUE)
endif()

# short calls the stage could not fix (tools/bringup/protos_deficits.py, BRINGUP-HISTORY
# 2026-10-25 (sweep)): each needs an override; the control ignores the overrides (must FAIL)
if(RG_PYTHON)
  add_test(NAME protos.deficits COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE})
  add_test(NAME protos.deficits_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE} --ignore-overrides)
  set_tests_properties(protos.deficits protos.deficits_control PROPERTIES LABELS protos TIMEOUT 60)
  set_tests_properties(protos.deficits_control PROPERTIES WILL_FAIL TRUE)
  # 2026-10-25 protos manual-row close-out (docs/PROTOS.md "Manual rows closed"):
  # protos.manual   every manual / unresolved PROTOS.tsv row has a reviewed verdict in
  #                 census/protos_manual.tsv, none BUG; control: overrides ignored (FAIL)
  # protos.irabi    every manual-call / manual-decl pair compiled to clang IR with this
  #                 build's commands, the call vs the definition's i686 signature
  #                 (tools/bringup/protos_irabi.py); control: overrides ignored (FAIL: the
  #                 game files the 2026-10-25 overrides replace are re-found)
  add_test(NAME protos.manual COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE} --manual)
  add_test(NAME protos.manual_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE} --manual --ignore-overrides)
  add_test(NAME protos.irabi COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE} --ir ${CMAKE_BINARY_DIR})
  add_test(NAME protos.irabi_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/bringup/protos_deficits.py
           --game ${RG_GAME_TREE} --ir ${CMAKE_BINARY_DIR} --ignore-overrides
           --cache ${CMAKE_BINARY_DIR}/protos/ir_control)
  set_tests_properties(protos.manual protos.manual_control PROPERTIES LABELS protos TIMEOUT 120)
  set_tests_properties(protos.irabi protos.irabi_control PROPERTIES LABELS protos TIMEOUT 900)
  set_tests_properties(protos.manual_control protos.irabi_control PROPERTIES WILL_FAIL TRUE)
endif()

# SPDX-License-Identifier: CC0-1.0
# Save-state tests (docs/TEST-FIXTURES.md), ctest label `fixtures`:
#   fixtures.save        power-on 120 fields headless (software GS), states at 60 and 120
#   fixtures.roundtrip   load 60, run to 120: the run hash equals the power-on run's
#   fixtures.cli         run_from.py argument handling (--print; runs no game)
#   fixtures.saveedit    tools/fixtures/saveedit.py on a synthetic save (docs/SAVE-FORMAT.md)
#   fixtures.refuse.*    WILL_FAIL controls: a corrupted, a truncated and a
#                        foreign-build state must be refused cleanly (exit 3)
#   fixtures.shopcrash   the 1025b shop-close crash: card zuser1025, buy Grand Edge in
#                        Salgin's item shop, close the shop (tools/fixtures/shopcrash.py,
#                        D3D11; skipped without the card or the game data)
#   fixtures.shadowbands the shadow bands at internal res x3 / x5 (2026-10-26): save2 at 3,850,
#                        the shadow map's CT16-shuffled alpha in the mirror vs its red, shadow
#                        region vs x1 (tools/shadow/shadowcheck.py, D3D11); _control: RG_NR_UV16=0
#                        must show the bands
#   fixtures.poison      the same route with RG_NR_POISON=2 (dead frame packet stacks poisoned,
#                        abort at the first renderer read of one: tools/fixtures/poisoncheck.py)
#   fixtures.poison_control  RG_NR_NOTE_COPY=0 (the pre-1025c re-reads) under poison: the
#                        detector must report poisoned reads
#   fixtures.optgate_quick  the P6 options-matrix gate, quick mode (tools/p6/optgate.py: 4 settings +
#                        the arming control on the save2 boot and the route to 2,000; ~1-2 min)
#   fixtures.fpsgate_quick  the P6 frame-rate gate, quick tier (tools/p6/fpsgate.py: 144 Hz interpolated,
#                        60 Hz snapshots, jittered presents + exact re-render, host / 240 leak, the
#                        arming control; save2 boot + route to 2,000; ~6 min at -j 2); label fpsgate
# They run rg-game (EXCLUDE_FROM_ALL: build the rg-game target first) and need
# the extracted data ($RG_DATA or data/; skipped without it).
# Slot waits (2026-11-01, docs/TEST-FIXTURES.md "Slot waits"): every test that runs rg-game is
# added with rg_slot_test(), under tools/fixtures/slotwatch.py: its limit is ACTIVE run time
# (time waiting for an rg_slots slot, held by other lanes' runs, excluded); the ctest TIMEOUT is
# only a wall-clock backstop, max(4 x limit, 3600 s).
#   fixtures.slotwatch     slotwatch.py --selftest (synthetic child, no game, ~8 s)
#   fixtures.slot_census   tools/fixtures/slot_census.py --check: every ctest of this build whose
#                          command names an rg-game exe is wrapped (or reviewed as running none)
# eefloat.launcher (label eefloat, no game run, ~3 s): the RG_EE_FPU_EXACT compiler launcher
#   (tools/parity/eediv/eediv_selftest.py): IR rewrite + 3,000 add/sub/div vs a Python EE model
if(RG_PYTHON AND CMAKE_SIZEOF_VOID_P EQUAL 4)
  add_test(NAME eefloat.launcher COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/parity/eediv/eediv_selftest.py
           ${CMAKE_C_COMPILER} --target=${CMAKE_C_COMPILER_TARGET} --work ${CMAKE_CURRENT_BINARY_DIR}/eefloat)
  set_tests_properties(eefloat.launcher PROPERTIES LABELS "eefloat;parity" TIMEOUT 120 SKIP_RETURN_CODE 77)
endif()
if(RG_PYTHON)
  add_test(NAME fixtures.slotwatch COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/slotwatch.py --selftest)
  add_test(NAME fixtures.slot_census COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/slot_census.py
           --ctest ${CMAKE_CTEST_COMMAND} --build ${CMAKE_BINARY_DIR} --check)
  set_tests_properties(fixtures.slotwatch fixtures.slot_census PROPERTIES LABELS fixtures TIMEOUT 120)
endif()
if(NOT TARGET rg-game OR NOT TARGET rg_savestate OR NOT RG_PYTHON)
  return()
endif()
# rg_slot_test(<name> <active limit s> [WILL_FAIL] <command...>): the test under slotwatch.py
# (see above); WILL_FAIL: a control, and a watchdog kill exits 0 so it fails the control
function(rg_slot_test name active)
  set(_cmd ${ARGN})
  set(_krc 1)
  list(GET _cmd 0 _first)
  if(_first STREQUAL "WILL_FAIL")
    list(REMOVE_AT _cmd 0)
    set(_krc 0)
  endif()
  add_test(NAME ${name} COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/slotwatch.py
           --active-timeout ${active} --killed-rc ${_krc} -- ${_cmd})
  if(_krc EQUAL 0)
    set_tests_properties(${name} PROPERTIES WILL_FAIL TRUE)
  endif()
  math(EXPR _wall "${active} * 4")
  if(_wall LESS 3600)
    set(_wall 3600)
  endif()
  set_tests_properties(${name} PROPERTIES TIMEOUT ${_wall})
endfunction()
set(_fx ${CMAKE_CURRENT_SOURCE_DIR}/fixture_test.py)
set(_work ${CMAKE_CURRENT_BINARY_DIR}/work)
rg_slot_test(fixtures.save 900 ${RG_PYTHON} ${_fx} save $<TARGET_FILE:rg-game> ${_work})
rg_slot_test(fixtures.roundtrip 900 ${RG_PYTHON} ${_fx} roundtrip $<TARGET_FILE:rg-game> ${_work})
add_test(NAME fixtures.cli COMMAND ${RG_PYTHON} ${_fx} cli $<TARGET_FILE:rg-game> ${_work})
set_tests_properties(fixtures.cli PROPERTIES LABELS fixtures TIMEOUT 120)
# fixtures.saveedit: the save editor on a synthetic save file (no game data, no rg-game run)
add_test(NAME fixtures.saveedit COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/saveedit_test.py)
set_tests_properties(fixtures.saveedit PROPERTIES LABELS fixtures TIMEOUT 60)
rg_slot_test(fixtures.shopcrash 300 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/shopcrash.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --out ${_work}/shopcrash --skip-missing)
set_tests_properties(fixtures.shopcrash PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)
rg_slot_test(fixtures.poison 300 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/poisoncheck.py
         --exe $<TARGET_FILE:rg-game> --suite shop --mode 2 --out ${_work}/poison --skip-missing)
rg_slot_test(fixtures.poison_control 300 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/poisoncheck.py
         --exe $<TARGET_FILE:rg-game> --suite shop --control --out ${_work}/poison_control --skip-missing)
rg_slot_test(fixtures.shadowbands 300 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/shadow/shadowcheck.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --scales 3,5 --out ${_work}/shadowbands --skip-missing)
rg_slot_test(fixtures.shadowbands_control 300 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/shadow/shadowcheck.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --scales 3 --control --out ${_work}/shadowbands_control --skip-missing)
set_tests_properties(fixtures.shadowbands fixtures.shadowbands_control PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)
set_tests_properties(fixtures.poison fixtures.poison_control PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)
rg_slot_test(fixtures.optgate_quick 600 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/p6/optgate.py run --mode quick
         --exe $<TARGET_FILE:rg-game> --out ${_work}/optgate_quick -j 2 --skip-missing)
set_tests_properties(fixtures.optgate_quick PROPERTIES LABELS "fixtures;p6" SKIP_RETURN_CODE 77)
rg_slot_test(fixtures.fpsgate_quick 1200 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/p6/fpsgate.py run --tier quick
         --exe $<TARGET_FILE:rg-game> --out ${_work}/fpsgate_quick -j 2 --skip-missing)
set_tests_properties(fixtures.fpsgate_quick PROPERTIES LABELS "fixtures;p6;fpsgate" SKIP_RETURN_CODE 77)
# invsort (lane invsort 2026-11-09, docs/SETTINGS.md "Sort items by category"): the generated
# category map is current, and the scripted sort -> save -> load -> use play test
add_test(NAME fixtures.invsort_census COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/census/invsort_census.py --check)
set_tests_properties(fixtures.invsort_census PROPERTIES LABELS fixtures TIMEOUT 120 SKIP_RETURN_CODE 77)
rg_slot_test(fixtures.invsort 900 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/invsort/invsort_test.py play
         --exe $<TARGET_FILE:rg-game> --out ${_work}/invsort --skip-missing)
set_tests_properties(fixtures.invsort PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)
set(_tests fixtures.save fixtures.roundtrip)
foreach(kind corrupt truncated foreign)
  rg_slot_test(fixtures.refuse.${kind} 900 WILL_FAIL ${RG_PYTHON} ${_fx} refuse $<TARGET_FILE:rg-game> ${_work} ${kind})
  list(APPEND _tests fixtures.refuse.${kind})
endforeach()
set_tests_properties(fixtures.save PROPERTIES FIXTURES_SETUP rg_ss_states)
set_tests_properties(${_tests} PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)
list(REMOVE_ITEM _tests fixtures.save)
set_tests_properties(${_tests} PROPERTIES FIXTURES_REQUIRED rg_ss_states)
# scenario (lane scenario 2026-11-11, docs/TEST-FIXTURES.md "Scenarios", docs/GAME-PROGRESSION.md):
# fixtures.scenario_selftest = no game run: the condition decoder on known strings, the census
# (census/progression.tsv rebuilt from data/) and target resolution ('Mud Whooper' -> fixed 1005 on
# Juraika, section 2032); fixtures.scenario = card sc_1005 booted, RG_FORCE_ENCOUNTER=fixed:1005@60
# queues the boss, passes when the enemy records name Mud Whooper
add_test(NAME fixtures.scenario_selftest COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/scenario.py selftest)
set_tests_properties(fixtures.scenario_selftest PROPERTIES LABELS fixtures TIMEOUT 300 SKIP_RETURN_CODE 77)
rg_slot_test(fixtures.scenario 900 ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/scenario.py run "Mud Whooper"
         --exe $<TARGET_FILE:rg-game> --out ${_work}/scenario --skip-missing)
set_tests_properties(fixtures.scenario PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77)

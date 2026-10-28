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
# They run rg-game (EXCLUDE_FROM_ALL: build the rg-game target first) and need
# the extracted data ($RG_DATA or data/; skipped without it).
if(NOT TARGET rg-game OR NOT TARGET rg_savestate OR NOT RG_PYTHON)
  return()
endif()
set(_fx ${CMAKE_CURRENT_SOURCE_DIR}/fixture_test.py)
set(_work ${CMAKE_CURRENT_BINARY_DIR}/work)
add_test(NAME fixtures.save COMMAND ${RG_PYTHON} ${_fx} save $<TARGET_FILE:rg-game> ${_work})
add_test(NAME fixtures.roundtrip COMMAND ${RG_PYTHON} ${_fx} roundtrip $<TARGET_FILE:rg-game> ${_work})
add_test(NAME fixtures.cli COMMAND ${RG_PYTHON} ${_fx} cli $<TARGET_FILE:rg-game> ${_work})
set_tests_properties(fixtures.cli PROPERTIES LABELS fixtures TIMEOUT 120)
# fixtures.saveedit: the save editor on a synthetic save file (no game data, no rg-game run)
add_test(NAME fixtures.saveedit COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/saveedit_test.py)
set_tests_properties(fixtures.saveedit PROPERTIES LABELS fixtures TIMEOUT 60)
add_test(NAME fixtures.shopcrash COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/shopcrash.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --out ${_work}/shopcrash --skip-missing)
set_tests_properties(fixtures.shopcrash PROPERTIES LABELS fixtures TIMEOUT 300 SKIP_RETURN_CODE 77)
add_test(NAME fixtures.poison COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/poisoncheck.py
         --exe $<TARGET_FILE:rg-game> --suite shop --mode 2 --out ${_work}/poison --skip-missing)
add_test(NAME fixtures.poison_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/fixtures/poisoncheck.py
         --exe $<TARGET_FILE:rg-game> --suite shop --control --out ${_work}/poison_control --skip-missing)
add_test(NAME fixtures.shadowbands COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/shadow/shadowcheck.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --scales 3,5 --out ${_work}/shadowbands --skip-missing)
add_test(NAME fixtures.shadowbands_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/shadow/shadowcheck.py
         --exe $<TARGET_FILE:rg-game> --api d3d11 --scales 3 --control --out ${_work}/shadowbands_control --skip-missing)
set_tests_properties(fixtures.shadowbands fixtures.shadowbands_control PROPERTIES LABELS fixtures TIMEOUT 300 SKIP_RETURN_CODE 77)
set_tests_properties(fixtures.poison fixtures.poison_control PROPERTIES LABELS fixtures TIMEOUT 300 SKIP_RETURN_CODE 77)
add_test(NAME fixtures.optgate_quick COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/p6/optgate.py run --mode quick
         --exe $<TARGET_FILE:rg-game> --out ${_work}/optgate_quick -j 2 --skip-missing)
set_tests_properties(fixtures.optgate_quick PROPERTIES LABELS "fixtures;p6" TIMEOUT 600 SKIP_RETURN_CODE 77)
set(_tests fixtures.save fixtures.roundtrip)
foreach(kind corrupt truncated foreign)
  add_test(NAME fixtures.refuse.${kind}
           COMMAND ${RG_PYTHON} ${_fx} refuse $<TARGET_FILE:rg-game> ${_work} ${kind})
  set_tests_properties(fixtures.refuse.${kind} PROPERTIES WILL_FAIL TRUE)
  list(APPEND _tests fixtures.refuse.${kind})
endforeach()
set_tests_properties(fixtures.save PROPERTIES FIXTURES_SETUP rg_ss_states)
set_tests_properties(${_tests} PROPERTIES LABELS fixtures SKIP_RETURN_CODE 77 TIMEOUT 900)
list(REMOVE_ITEM _tests fixtures.save)
set_tests_properties(${_tests} PROPERTIES FIXTURES_REQUIRED rg_ss_states)

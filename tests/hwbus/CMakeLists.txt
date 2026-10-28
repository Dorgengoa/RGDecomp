# SPDX-License-Identifier: CC0-1.0
# Hardware register bus + hwaccess stage tests (docs/HWBUS.md).  ctest -L hwbus
if(NOT RG_PYTHON)
  find_program(RG_PYTHON NAMES python3 python )
  find_program(RG_PYTHON NAMES python3 python)
endif()

# Game functions rewritten by the stage, straight from game/ (end-to-end):
# hardware stores/loads, D_ENABLEW, IPU poll, a 0x0FFFFFFF mask, RG_OVL_DATA.
set(RG_HW_E2E
  src/main/movie/ViBufSetD4Chcr_1d47a0.c
  src/main/movie/ViBufSetD3Chcr_1d4800.c
  src/main/movie/ViBufStopDma_1d4180.c
  src/main/movie/ViBufDelete_1d3e20.c
  src/main/movie/ViBufGetFifoIndex_1d4860.c
  src/main/ui/FieldHudInitOnce_204120.c)
set(RG_HW_E2E_SRCS)
set(_e2e_ok TRUE)
foreach(rel IN LISTS RG_HW_E2E)
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/game/${rel})
    set(_e2e_ok FALSE)
  endif()
endforeach()
if(RG_PYTHON AND _e2e_ok)
  foreach(rel IN LISTS RG_HW_E2E)
    set(out ${CMAKE_CURRENT_BINARY_DIR}/game/${rel})
    add_custom_command(
      OUTPUT ${out}
      COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/stages/hwaccess.py
              --game ${CMAKE_SOURCE_DIR}/game --one ${CMAKE_SOURCE_DIR}/game/${rel} ${out}
      DEPENDS ${CMAKE_SOURCE_DIR}/game/${rel} ${CMAKE_SOURCE_DIR}/tools/stages/hwaccess.py
      COMMENT "hwaccess: ${rel}")
    list(APPEND RG_HW_E2E_SRCS ${out})
  endforeach()
  # compiled exactly like game code (cmake/game.cmake flags)
  add_library(rg_hwbus_game_e2e OBJECT ${RG_HW_E2E_SRCS})
  target_link_libraries(rg_hwbus_game_e2e PRIVATE rg_flags rg_game_headers)
  target_compile_options(rg_hwbus_game_e2e PRIVATE
    -w -Wno-int-conversion -Wno-incompatible-pointer-types
    -Wno-incompatible-function-pointer-types -fgnu89-inline
    -Wno-implicit-function-declaration -Wno-return-mismatch)
endif()

add_executable(rg-hwbus-tests hwbus_tests.c)
target_include_directories(rg-hwbus-tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(rg-hwbus-tests PRIVATE rg_ps2_hwbus rg_flags)
if(TARGET rg_hwbus_game_e2e)
  target_sources(rg-hwbus-tests PRIVATE $<TARGET_OBJECTS:rg_hwbus_game_e2e>)
  target_compile_definitions(rg-hwbus-tests PRIVATE RG_HWBUS_GAME_E2E=1)
endif()
if(WIN32)
  target_compile_definitions(rg-hwbus-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(RG_HWBUS_TESTS claims kernel dmac fifo_vif_gif gs_priv sif ipu unknown spin_charge
                   spr_ovl dstat_order)
if(TARGET rg_hwbus_game_e2e)
  list(APPEND RG_HWBUS_TESTS game_e2e)
endif()
foreach(t IN LISTS RG_HWBUS_TESTS)
  add_test(NAME hwbus.${t} COMMAND rg-hwbus-tests ${t})
  set_tests_properties(hwbus.${t} PROPERTIES TIMEOUT 60 LABELS hwbus)
endforeach()
# Deliberately-wrong control: kernel asked before the DMAC for D_STAT.  Must FAIL.
add_test(NAME hwbus.dstat_order_control COMMAND rg-hwbus-tests dstat_order_control)
set_tests_properties(hwbus.dstat_order_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS hwbus)

if(RG_PYTHON)
  # stage unit tests on fixtures (+ control: alias handling disabled, must FAIL)
  add_test(NAME hwbus.stage_unit
           COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_stage.py)
  add_test(NAME hwbus.stage_unit_control
           COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_stage.py control)
  set_tests_properties(hwbus.stage_unit PROPERTIES TIMEOUT 120 LABELS hwbus)
  set_tests_properties(hwbus.stage_unit_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS hwbus)
  # the stage over a copy of game/ (out/hw-test/) + clang -fsyntax-only on the
  # changed files, before vs after (+ control, must FAIL)
  if(EXISTS ${CMAKE_SOURCE_DIR}/game/MANIFEST.tsv)
    add_test(NAME hwbus.stage_game
             COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/stage_game.py
                     ${CMAKE_SOURCE_DIR}/out/hw-test/game)
    add_test(NAME hwbus.stage_game_control
             COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/stage_game.py
                     ${CMAKE_SOURCE_DIR}/out/hw-test/game-control control)
    set_tests_properties(hwbus.stage_game PROPERTIES TIMEOUT 600 LABELS hwbus)
    set_tests_properties(hwbus.stage_game_control PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS hwbus)
  endif()
endif()

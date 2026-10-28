# SPDX-License-Identifier: CC0-1.0
# Pad + memory card HLE tests (included from src/sce/padmc/CMakeLists.txt). ctest -L padmc
add_executable(rg-padmc-tests padmc_tests.c)
target_link_libraries(rg-padmc-tests PRIVATE rg_sce_padmc rg_ps2_padmc rg_sce_sif rg_sce_kernel
  rg_ps2_sif rg_ps2_iop rg_ps2_kernel rg_native_input rg_native_saves rg_native_iop rg_flags)
if(WIN32)
  target_compile_definitions(rg-padmc-tests PRIVATE _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_WARNINGS)
endif()

# The game's own pad code (game/src/main/pad, generated, may be absent) driven by
# this libpad: PadOpenPorts -> PadWaitReady must reach phase 0x63.
set(RG_PADMC_GAME_PAD_SRCS)
foreach(f PadOpenPorts_1c6bf0 PadSysInit_185080 PadPortOpen_184ed0 PadStateInit_184f90
          PadWaitReady_1849e0 PadUpdateConnection_184a50 PadReadData_184df0
          PadIsAnalogMode_184960 PadUpdateVibration_184250)
  # an overrides/ file replaces its game/ file, as in the game build
  # (PadReadData_184df0: 32-byte read buffer, docs/PADMC.md)
  set(p ${PROJECT_SOURCE_DIR}/overrides/src/main/pad/${f}.c)
  if(NOT EXISTS ${p})
    set(p ${PROJECT_SOURCE_DIR}/game/src/main/pad/${f}.c)
  endif()
  if(EXISTS ${p})
    list(APPEND RG_PADMC_GAME_PAD_SRCS ${p})
  endif()
endforeach()
list(LENGTH RG_PADMC_GAME_PAD_SRCS RG_PADMC_NGAME)
set(RG_PADMC_TESTS pad_stable pad_mapping pad_replay pad_rumble pad_analog_lock mc_files mc_errors mc_async mc_persist
  mc_card_states mc_save_cycle mc_full mc_exact_fit mc_corrupt mc_write_fail mc_backup mc_layout
  npad_equiv)
if(RG_PADMC_NGAME EQUAL 9)
  add_library(rg_padmc_game_pad OBJECT ${RG_PADMC_GAME_PAD_SRCS})
  target_link_libraries(rg_padmc_game_pad PRIVATE rg_game_headers rg_flags)
  target_sources(rg-padmc-tests PRIVATE $<TARGET_OBJECTS:rg_padmc_game_pad>)
  target_compile_definitions(rg-padmc-tests PRIVATE RG_PADMC_GAME_PAD=1)
  list(APPEND RG_PADMC_TESTS pad_game)
else()
  message(STATUS "padmc: game/src/main/pad not ingested; pad_game test skipped")
endif()

# The game's own save state machines (game/src/main/file/Mc*.c ...) on this card model.
set(RG_PADMC_GAME_MC_SRCS)
set(RG_PADMC_GAME_MC_UNITS
  file/McGetInfoStep_375640 file/McFormatStep_3736b0 file/McSaveCreateStep_375090
  file/McSaveStep_374110 file/McLoadStep_373890 file/McSaveDirScan_3748c0
  file/McSaveSlotScanStep_374b00 menu/McSetErrorResult_375890 sys/McCardCheckFreeSpace_376220
  file/McCardIsReady_376280 file/SaveCalcSizeKB_3735e0 file/McBuildIconPath_376400
  file/McBuildSaveDirPath_376460 file/MemcardBuildSavePath_376380 file/SaveMgrClearResult_3759d0
  util/SaveMgrGetResult_375a00 file/SaveResultClear_3761b0 file/SaveProgressAdd_373650
  file/SaveSlotEntryClear_3761a0 file/SaveSlotEntrySetBroken_376120 file/SaveSlotEntrySetValid_376080
  file/SaveSlotEntrySetBadData_3760d0 file/SaveSlotEntryIsEmpty_376170 file/SaveSlotEntryIsEmptyAt_3734c0
  file/SaveSlotEntryIsValid_376050 sys/SaveSlotEntrySetNoSpace_376160 sys/SaveSlotEntryIsBroken_3760f0
  file/SaveSlotEntriesClear_373590 file/SaveDirListClear_373330 file/SaveDirListContains_3732b0
  file/SaveDirEntriesClear_376020 sys/McPollCardChange_372db0)
foreach(u IN LISTS RG_PADMC_GAME_MC_UNITS)
  set(p ${PROJECT_SOURCE_DIR}/overrides/src/main/${u}.c)
  if(NOT EXISTS ${p})
    set(p ${PROJECT_SOURCE_DIR}/game/src/main/${u}.c)
  endif()
  if(EXISTS ${p})
    list(APPEND RG_PADMC_GAME_MC_SRCS ${p})
  endif()
endforeach()
list(LENGTH RG_PADMC_GAME_MC_SRCS RG_PADMC_NGAME_MC)
list(LENGTH RG_PADMC_GAME_MC_UNITS RG_PADMC_NGAME_MC_WANT)
if(RG_PADMC_NGAME_MC EQUAL RG_PADMC_NGAME_MC_WANT)
  add_library(rg_padmc_game_mc OBJECT ${RG_PADMC_GAME_MC_SRCS})
  target_link_libraries(rg_padmc_game_mc PRIVATE rg_game_headers rg_flags)
  # the game build's C dialect flags (cmake/game.cmake RG_GAME_C_FLAGS)
  target_compile_options(rg_padmc_game_mc PRIVATE -w -Wno-int-conversion -Wno-incompatible-pointer-types
    -Wno-incompatible-function-pointer-types -fgnu89-inline -Wno-implicit-function-declaration)
  target_sources(rg-padmc-tests PRIVATE $<TARGET_OBJECTS:rg_padmc_game_mc>)
  target_compile_definitions(rg-padmc-tests PRIVATE RG_PADMC_GAME_MC=1)
  list(APPEND RG_PADMC_TESTS mc_game)
  # control: expects the save the pulled card interrupted to be on the host
  add_test(NAME padmc.mc_game_control COMMAND rg-padmc-tests mc_game_control)
  set_tests_properties(padmc.mc_game_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS padmc
    ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
  set_property(TEST padmc.mc_game_control APPEND PROPERTY RESOURCE_LOCK padmc_dir_mc_game)
else()
  message(STATUS "padmc: game save units not ingested; mc_game test skipped")
endif()

foreach(t IN LISTS RG_PADMC_TESTS)
  add_test(NAME padmc.${t} COMMAND rg-padmc-tests ${t})
  set_tests_properties(padmc.${t} PROPERTIES TIMEOUT 120 LABELS padmc
    ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
endforeach()

if(TEST padmc.mc_game)
  set_property(TEST padmc.mc_game APPEND PROPERTY RESOURCE_LOCK padmc_dir_mc_game)
endif()

# RG_IOP=native (docs/NATIVE-IOP.md): the same tests with libpad / libmc on the native pad
# and save services (no padman / mcserv / SIF); own card directory.  npad_equiv runs both
# services itself.  Controls: the armed checks must fail natively too.
set(_rg_padmc_native_dir ${CMAKE_CURRENT_BINARY_DIR}/native)
file(MAKE_DIRECTORY ${_rg_padmc_native_dir})
foreach(t IN LISTS RG_PADMC_TESTS)
  if(t STREQUAL "npad_equiv")
    continue()
  endif()
  add_test(NAME padmc.native.${t} COMMAND rg-padmc-tests ${t})
  set_tests_properties(padmc.native.${t} PROPERTIES TIMEOUT 120 LABELS "padmc;native_iop"
    ENVIRONMENT "RG_PADMC_TMP=${_rg_padmc_native_dir};RG_IOP=native;RG_IOP_QUIET=1")
endforeach()
foreach(t pad_stable pad_mapping pad_analog_lock mc_files mc_async)
  add_test(NAME padmc.native.${t}_control COMMAND rg-padmc-tests ${t}_control)
  set_tests_properties(padmc.native.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS "padmc;native_iop"
    ENVIRONMENT "RG_PADMC_TMP=${_rg_padmc_native_dir};RG_IOP=native;RG_IOP_QUIET=1")
  set_tests_properties(padmc.native.${t} padmc.native.${t}_control PROPERTIES RESOURCE_LOCK padmc_native_dir_${t})
endforeach()
if(TEST padmc.native.mc_game)
  set_property(TEST padmc.native.mc_game APPEND PROPERTY RESOURCE_LOCK padmc_native_dir_mc_game)
endif()
# npad_equiv_control: the native run gets cmd_frames 2 and must differ from padman
add_test(NAME padmc.npad_equiv_control COMMAND rg-padmc-tests npad_equiv_control)
set_tests_properties(padmc.npad_equiv_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS "padmc;native_iop"
  ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
set_tests_properties(padmc.npad_equiv PROPERTIES LABELS "padmc;native_iop")

# Persistence across processes: one process writes the card, a second reads it.
add_test(NAME padmc.mc_persist_write COMMAND rg-padmc-tests mc_persist_write)
add_test(NAME padmc.mc_persist_read COMMAND rg-padmc-tests mc_persist_read)
set_tests_properties(padmc.mc_persist_write PROPERTIES FIXTURES_SETUP padmc_card LABELS padmc
  TIMEOUT 60 ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR}")
set_tests_properties(padmc.mc_persist_read PROPERTIES FIXTURES_REQUIRED padmc_card LABELS padmc
  TIMEOUT 60 ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR}")

# A crash mid-save: one process writes half a save over an old one and exits without
# flush / close / shutdown; a second process must find the old save whole.
add_test(NAME padmc.mc_crash_write COMMAND rg-padmc-tests mc_crash_write)
add_test(NAME padmc.mc_crash_read COMMAND rg-padmc-tests mc_crash_read)
add_test(NAME padmc.mc_crash_read_control COMMAND rg-padmc-tests mc_crash_read_control)
set_tests_properties(padmc.mc_crash_write PROPERTIES FIXTURES_SETUP padmc_crash LABELS padmc
  TIMEOUT 60 ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR}")
set_tests_properties(padmc.mc_crash_read padmc.mc_crash_read_control PROPERTIES FIXTURES_REQUIRED padmc_crash
  LABELS padmc TIMEOUT 60 ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR}")
set_tests_properties(padmc.mc_crash_read_control PROPERTIES WILL_FAIL TRUE)
set_tests_properties(padmc.mc_crash_read padmc.mc_crash_read_control PROPERTIES RESOURCE_LOCK padmc_crash_dir)

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   pad_stable_control:  expects STABLE one VBlank after open
#   pad_mapping_control: expects active-high button bytes in the DS2 frame
#   pad_replay_control:  replays a script shifted by one frame, expects the same hash
#   pad_analog_lock_control: expects the hardware power cycle (digital) after a replug
#   mc_files_control:    expects free space unchanged after writing a save
#   mc_async_control:    expects the result visible right after issue
#   mc_persist_control:  reads the card back from a different root
#   mc_write_fail_control: expects the half-written save on the host after the card is pulled
#   mc_corrupt_control:  expects a save left with icon.err (no icon.sys) to scan as valid
#   mc_crash_read_control (above): expects the uncommitted half-write after a crash
foreach(t pad_stable pad_mapping pad_replay pad_analog_lock mc_files mc_async mc_persist mc_write_fail mc_corrupt)
  add_test(NAME padmc.${t}_control COMMAND rg-padmc-tests ${t}_control)
  set_tests_properties(padmc.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS padmc
    ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
  # a test and its control use the same card directory
  set_tests_properties(padmc.${t} padmc.${t}_control PROPERTIES RESOURCE_LOCK padmc_dir_${t})
endforeach()

# tools/saves/ps2card.py (PCSX2 card images, folder cards, the port's cards) on synthetic
# cards; it also leaves a card for mc_pyimport, which the C model must read.
if(RG_PYTHON)
  add_test(NAME padmc.ps2card COMMAND ${RG_PYTHON} -I -B ${CMAKE_CURRENT_SOURCE_DIR}/test_ps2card.py
    ${CMAKE_CURRENT_BINARY_DIR})
  set_tests_properties(padmc.ps2card PROPERTIES LABELS padmc TIMEOUT 300 FIXTURES_SETUP padmc_pyimport
    ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR}")
  add_test(NAME padmc.mc_pyimport COMMAND rg-padmc-tests mc_pyimport)
  set_tests_properties(padmc.mc_pyimport PROPERTIES LABELS padmc TIMEOUT 60 FIXTURES_REQUIRED padmc_pyimport
    ENVIRONMENT "RG_PADMC_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
endif()

# SPDX-License-Identifier: CC0-1.0
# Settings registry (label `settings`) and input-action layer (label `input`)
# tests: docs/SETTINGS.md, docs/INPUT.md.   ctest -L settings ; ctest -L input
add_executable(rg-settings-tests settings_tests.c)
target_link_libraries(rg-settings-tests PRIVATE rg_host rg_settings rg_flags)
if(WIN32)
  target_compile_definitions(rg-settings-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-settings-tests PRIVATE -Wall -Wextra)
endif()

set(_out ${CMAKE_CURRENT_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${_out})

set(RG_SETTINGS_TESTS
  registry_types ini_parse ini_roundtrip presets cmdline change_tracking
  display_trial save_load core_defs menu_keyboard menu_gamepad
  menu_rebind_keyboard menu_rebind_gamepad menu_text_entry menu_flags
  menu_device_guard_keyboard menu_device_guard_gamepad menu_wrap screenshot_dir_live fps_counter)
foreach(t IN LISTS RG_SETTINGS_TESTS)
  add_test(NAME settings.${t} COMMAND rg-settings-tests ${t} ${_out})
  set_tests_properties(settings.${t} PROPERTIES TIMEOUT 60 LABELS settings)
endforeach()

set(RG_INPUT_TESTS
  binding_text default_layout ds2_report multi_binding legacy_equivalence tuning
  mouse hotplug latch tap_cadence ui_nav settings_bindings script_bypass
  action_aliases walk stick_compensation stick_range camera_convention
  capture pad_family prompt_style
  capture_motion menu_mouse_capture_keyboard menu_mouse_capture_gamepad)
foreach(t IN LISTS RG_INPUT_TESTS)
  add_test(NAME input.${t} COMMAND rg-settings-tests ${t} ${_out})
  set_tests_properties(input.${t} PROPERTIES TIMEOUT 60 LABELS input)
endforeach()

# Controls (WILL_FAIL): prove the checks are armed.
#   settings.invalid_control  expects an out-of-range file value to be KEPT
#   input.report_control      expects CROSS from a key bound only to CIRCLE
add_test(NAME settings.invalid_control COMMAND rg-settings-tests invalid_control ${_out})
set_tests_properties(settings.invalid_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS settings)
add_test(NAME input.report_control COMMAND rg-settings-tests report_control ${_out})
set_tests_properties(input.report_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS input)
#   input.tap_cadence_control expects every tap to reach the game with the press latch off
add_test(NAME input.tap_cadence_control COMMAND rg-settings-tests tap_cadence_control ${_out})
set_tests_properties(input.tap_cadence_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS input)

# Mouse camera (docs/INPUT.md "Mouse camera implementation"): label input
add_executable(rg-mouse-look-tests mouse_look_tests.c)
target_link_libraries(rg-mouse-look-tests PRIVATE rg_host rg_settings rg_flags)
if(WIN32)
  target_compile_definitions(rg-mouse-look-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-mouse-look-tests PRIVATE -Wall -Wextra)
endif()
foreach(t look_quantise look_settings look_script look_host)
  add_test(NAME input.${t} COMMAND rg-mouse-look-tests ${t})
  set_tests_properties(input.${t} PROPERTIES TIMEOUT 60 LABELS input)
endforeach()
# Control (WILL_FAIL): injected motion must not arrive with the setting off.
add_test(NAME input.look_control COMMAND rg-mouse-look-tests look_control)
set_tests_properties(input.look_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS input)

# Overlay hold chord + overlay prompts (docs/INPUT.md "Opening the settings
# overlay with a gamepad", "Prompts in the settings overlay"): label input
add_executable(rg-chord-tests chord_tests.c)
target_link_libraries(rg-chord-tests PRIVATE rg_host rg_settings rg_flags)
if(WIN32)
  target_compile_definitions(rg-chord-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-chord-tests PRIVATE -Wall -Wextra)
endif()
foreach(t chord_settings chord_no_leak chord_lone_press chord_rebind chord_hotplug overlay_prompts)
  add_test(NAME input.${t} COMMAND rg-chord-tests ${t})
  set_tests_properties(input.${t} PROPERTIES TIMEOUT 60 LABELS input)
endforeach()
# The host_sdl.c wiring with an SDL virtual gamepad (a small window, ~5 s real
# time; skipped without a display).
add_test(NAME input.chord_host COMMAND rg-chord-tests chord_host)
set_tests_properties(input.chord_host PROPERTIES TIMEOUT 60 LABELS input SKIP_RETURN_CODE 77 RUN_SERIAL TRUE)
# its control (WILL_FAIL): with the chord off, Select / Start do reach the game
add_test(NAME input.chord_host_control COMMAND rg-chord-tests chord_host_control)
set_tests_properties(input.chord_host_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS input RUN_SERIAL TRUE)
# Control (WILL_FAIL): without the filter the chord does reach the report.
add_test(NAME input.chord_control COMMAND rg-chord-tests chord_control)
set_tests_properties(input.chord_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS input)

# Button prompts (docs/PROMPTS.md "Implementation"): ctest -L prompts
add_executable(rg-prompts-tests prompts_tests.c)
target_link_libraries(rg-prompts-tests PRIVATE rg_settings rg_flags)
if(WIN32)
  target_compile_definitions(rg-prompts-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-prompts-tests PRIVATE -Wall -Wextra)
endif()
foreach(t layout build art key_labels step)
  add_test(NAME prompts.${t} COMMAND rg-prompts-tests ${t})
  set_tests_properties(prompts.${t} PROPERTIES TIMEOUT 60 LABELS "prompts;settings")
endforeach()
# Control (WILL_FAIL): a write behind the switch's back must be caught.
add_test(NAME prompts.step_control COMMAND rg-prompts-tests step_control)
set_tests_properties(prompts.step_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS "prompts;settings")
# The C atlas builder == tools/assets/gaiji.py build, pixel for pixel, on the
# real gaiji2.img (skipped without data/).
if(RG_PYTHON)
  add_test(NAME prompts.vs_gaiji_py
    COMMAND ${RG_PYTHON} -I ${CMAKE_SOURCE_DIR}/tools/prompts/compare.py
            --exe $<TARGET_FILE:rg-prompts-tests> --data ${CMAKE_SOURCE_DIR}/data
            --out ${_out}/prompts_atlas)
  set_tests_properties(prompts.vs_gaiji_py PROPERTIES TIMEOUT 600 LABELS "prompts;settings"
                       SKIP_RETURN_CODE 77)
endif()

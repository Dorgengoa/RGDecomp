# SPDX-License-Identifier: CC0-1.0
# Host shell tests (docs/HOST.md).  ctest -L host
add_executable(rg-host-tests host_tests.c)
# ps2k.h only, for the pacing-hook signature check (no link)
target_include_directories(rg-host-tests PRIVATE ${CMAKE_SOURCE_DIR}/src/ps2/kernel)
target_link_libraries(rg-host-tests PRIVATE rg_host rg_flags)
if(WIN32)
  target_compile_definitions(rg-host-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(RG_HOST_TESTS
  pad_report input_mapping input_config input_script script_determinism
  scaling png_roundtrip pacing audio_reg audio_device audio_focus)
foreach(t IN LISTS RG_HOST_TESTS)
  add_test(NAME host.${t} COMMAND rg-host-tests ${t})
  set_tests_properties(host.${t} PROPERTIES TIMEOUT 60 LABELS host)
endforeach()
# Deliberately corrupted PNG: the checker must reject it (WILL_FAIL control).
add_test(NAME host.png_corrupt_control COMMAND rg-host-tests png_corrupt_control)
set_tests_properties(host.png_corrupt_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS host)
# Widescreen stage 0 (docs/WIDESCREEN.md): ctest -L wide
foreach(t wide_fit wide_present wide_host)
  add_test(NAME host.${t} COMMAND rg-host-tests ${t})
  set_tests_properties(host.${t} PROPERTIES TIMEOUT 60 LABELS "host;wide")
endforeach()
add_test(NAME settings.wide_policy COMMAND rg-host-tests wide_policy)
set_tests_properties(settings.wide_policy PROPERTIES TIMEOUT 60 LABELS "settings;wide")
# Widescreen stage 1: any aspect (resolve, projection / HUD scale, published values)
add_test(NAME settings.wide_any COMMAND rg-host-tests wide_any)
set_tests_properties(settings.wide_any PROPERTIES TIMEOUT 60 LABELS "settings;wide")
add_test(NAME settings.wide_layout COMMAND rg-host-tests wide_layout)
set_tests_properties(settings.wide_layout PROPERTIES TIMEOUT 60 LABELS "settings;wide")
add_test(NAME settings.wide_menu COMMAND rg-host-tests wide_menu)
set_tests_properties(settings.wide_menu PROPERTIES TIMEOUT 60 LABELS "settings;wide")
add_test(NAME settings.wide_strips COMMAND rg-host-tests wide_strips)
set_tests_properties(settings.wide_strips PROPERTIES TIMEOUT 60 LABELS "settings;wide")
add_test(NAME host.wide_present_control COMMAND rg-host-tests wide_present_control)
set_tests_properties(host.wide_present_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS "host;wide")

set(_out ${CMAKE_CURRENT_BINARY_DIR}/out)
file(MAKE_DIRECTORY ${_out})
if(RG_PYTHON)
  # The C script compiler == tools/trace/input.py, byte for byte.
  foreach(s ${CMAKE_SOURCE_DIR}/tools/trace/examples/start_cross.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/data/script_edge.txt
            ${CMAKE_CURRENT_SOURCE_DIR}/data/demo_input.txt)
    get_filename_component(n ${s} NAME_WE)
    add_test(NAME host.script_vs_input_py.${n}
      COMMAND ${CMAKE_COMMAND} -DPY=${RG_PYTHON} -DINPUT_PY_DIR=${CMAKE_SOURCE_DIR}/tools/trace
              -DTESTS=$<TARGET_FILE:rg-host-tests> -DSCRIPT=${s} -DOUT=${_out}
              -P ${CMAKE_CURRENT_SOURCE_DIR}/compare_script.cmake)
    set_tests_properties(host.script_vs_input_py.${n} PROPERTIES TIMEOUT 120 LABELS host)
  endforeach()
  # The PNG decoded by an independent implementation (Python zlib).
  add_test(NAME host.png_python_write COMMAND rg-host-tests png_write ${_out}/py.png)
  add_test(NAME host.png_python_check
    COMMAND ${RG_PYTHON} -I ${CMAKE_CURRENT_SOURCE_DIR}/pngcheck.py ${_out}/py.png)
  set_tests_properties(host.png_python_write PROPERTIES LABELS host TIMEOUT 60
                       FIXTURES_SETUP host_pypng)
  set_tests_properties(host.png_python_check PROPERTIES LABELS host TIMEOUT 60
                       FIXTURES_REQUIRED host_pypng)
else()
  message(WARNING "python not found: host.script_vs_input_py / host.png_python skipped")
endif()

add_test(NAME host.demo_headless
  COMMAND ${CMAKE_COMMAND} -DDEMO=$<TARGET_FILE:rg-host-demo> -DTESTS=$<TARGET_FILE:rg-host-tests>
          -DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/data/demo_input.txt
          -DOTHER=${CMAKE_CURRENT_SOURCE_DIR}/data/demo_input_other.txt
          -DOUT=${_out}/demo -DFRAMES=40
          -P ${CMAKE_CURRENT_SOURCE_DIR}/demo_headless.cmake)
set_tests_properties(host.demo_headless PROPERTIES TIMEOUT 300 LABELS host)

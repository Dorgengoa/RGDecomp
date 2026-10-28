# SPDX-License-Identifier: CC0-1.0
# Overlay manager tests (docs/OVERLAY.md).  ctest -L overlay
if(NOT RG_PYTHON)
  find_program(RG_PYTHON NAMES python3 python )
  find_program(RG_PYTHON NAMES python3 python)
endif()

# synthetic overlays (+ the OverlayLoadFile binding and hwbus RG_OVL_DATA path)
add_executable(rg-ovl-tests ovl_tests.c)
target_link_libraries(rg-ovl-tests PRIVATE rg_ps2_overlay_bind rg_flags)
target_compile_definitions(rg-ovl-tests PRIVATE RG_OVL_TEST_BIND=1)
if(WIN32)
  target_compile_definitions(rg-ovl-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
# ovl_asm.h declares (never uses) the generated arena / MAIN bss; the tests do
# not link them.
set(RG_OVL_TESTS data_restore bss_zero ctor_order resolver_current shared_address
                 unknown address_map object_mode bind_validation bind_hwbus)
foreach(t IN LISTS RG_OVL_TESTS)
  add_test(NAME overlay.${t} COMMAND rg-ovl-tests ${t})
  set_tests_properties(overlay.${t} PROPERTIES TIMEOUT 60 LABELS overlay)
endforeach()
# deliberately wrong controls: must FAIL
foreach(t ctor_order_control shared_address_control)
  add_test(NAME overlay.${t} COMMAND rg-ovl-tests ${t})
  set_tests_properties(overlay.${t} PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS overlay)
endforeach()

# the real generated registry (needs the generator inputs, see src/ps2/overlay)
if(TARGET rg_ovl_registry_table)
  add_executable(rg-ovl-real-tests ovl_real_tests.c)
  target_link_libraries(rg-ovl-real-tests PRIVATE rg_ovl_registry_table rg_ovl_arena rg_ps2_overlay rg_flags)
  target_compile_definitions(rg-ovl-real-tests PRIVATE RG_OVL_TEST_ARENA=1
                             RG_OVL_BIN_DIR="${CMAKE_SOURCE_DIR}/data/BIN")
  if(WIN32)
    target_compile_definitions(rg-ovl-real-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  foreach(t real_registry arena bin_data)
    add_test(NAME overlay.${t} COMMAND rg-ovl-real-tests ${t})
    set_tests_properties(overlay.${t} PROPERTIES TIMEOUT 60 LABELS overlay SKIP_RETURN_CODE 77)
  endforeach()
  add_test(NAME overlay.real_registry_control COMMAND rg-ovl-real-tests real_registry_control)
  set_tests_properties(overlay.real_registry_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS overlay)
endif()

if(RG_PYTHON)
  # generator pieces on fixtures: MIPS ctor lifter, data-asm parser, ovlsyms stage
  add_test(NAME overlay.gen_unit COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_gen.py)
  add_test(NAME overlay.gen_unit_control COMMAND ${RG_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/test_gen.py control)
  set_tests_properties(overlay.gen_unit PROPERTIES TIMEOUT 120 LABELS overlay)
  set_tests_properties(overlay.gen_unit_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS overlay)
endif()

# the native module table (src/native/ovl, docs/OVERLAY.md section 8): synthetic modules
# + the trace recorder's address map over it (trace_map.c compiled in: rg_trace_core links
# the arena manager)
add_executable(rg-ovl-native-tests ovl_native_tests.c ${CMAKE_SOURCE_DIR}/src/trace/trace_map.c)
target_include_directories(rg-ovl-native-tests PRIVATE ${CMAKE_SOURCE_DIR}/src/trace)
target_link_libraries(rg-ovl-native-tests PRIVATE rg_native_ovl rg_flags)
if(WIN32)
  target_compile_definitions(rg-ovl-native-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
foreach(t data_restore bss_ctors imports bind trace_map)
  add_test(NAME overlay.native_${t} COMMAND rg-ovl-native-tests ${t})
  set_tests_properties(overlay.native_${t} PROPERTIES TIMEOUT 60 LABELS "overlay;native_only")
  add_test(NAME overlay.native_${t}_control COMMAND rg-ovl-native-tests ${t}_control)
  set_tests_properties(overlay.native_${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS "overlay;native_only")
endforeach()

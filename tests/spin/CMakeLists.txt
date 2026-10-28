# SPDX-License-Identifier: CC0-1.0
# Spin-loop runtime tests (docs/SPIN.md) on the real kernel HLE: ctest -L spin
add_executable(rg-spin-tests spin_tests.c)
target_link_libraries(rg-spin-tests PRIVATE rg_ps2_spin rg_sce_kernel rg_ps2_kernel rg_flags)
foreach(t handler_flag thread_flag rotate_flag determinism di_report halt long_wait)
  add_test(NAME spin.${t} COMMAND rg-spin-tests ${t})
  set_tests_properties(spin.${t} PROPERTIES TIMEOUT 60 LABELS spin)
endforeach()
# Deliberately-wrong controls (uninstrumented loop / perturbed charge): must FAIL.
foreach(t handler_flag thread_flag rotate_flag determinism)
  add_test(NAME spin.${t}_control COMMAND rg-spin-tests ${t}_control)
  set_tests_properties(spin.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS spin)
endforeach()

# Driven-thread busy-wait census (tools/census/driven_wait.py, docs/SPIN.md "Driven threads"):
# no loop on a game flow may wake a non-sync driven step and poll for it without passing a
# driver point.  The control ignores the overrides' driver points and must find the
# SoundStreamSlotShutdown_1bdfd0 kick loops (fixed 2026-10-25): it must FAIL.  Needs the
# retail images / platform cache (skip 77 without them).
if(RG_PYTHON)
  add_test(NAME spin.driven_wait COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/census/driven_wait.py
           --check --no-write)
  add_test(NAME spin.driven_wait_control COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/census/driven_wait.py
           --check --no-write --no-overrides)
  set_tests_properties(spin.driven_wait spin.driven_wait_control PROPERTIES
                       LABELS spin TIMEOUT 300 SKIP_RETURN_CODE 77)
  set_tests_properties(spin.driven_wait_control PROPERTIES WILL_FAIL TRUE)
endif()

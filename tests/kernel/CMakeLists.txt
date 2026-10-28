# SPDX-License-Identifier: CC0-1.0
# EE kernel HLE tests (included from src/sce/kernel/CMakeLists.txt).
add_executable(rg-kernel-tests kernel_tests.c)
target_link_libraries(rg-kernel-tests PRIVATE rg_sce_kernel rg_ps2_kernel rg_native_threads rg_flags)

set(RG_KERNEL_TESTS
  priority_order non_preemption wakeup_counting semaphores vblank_count
  delay_thread di_ei di_ei_per_thread intc_chain ids determinism
  context_violations timers alarms thread_lifecycle run_limits service_thread
  poll_wait driven_thread frame_driver frame_native pace)
foreach(t IN LISTS RG_KERNEL_TESTS)
  add_test(NAME kernel.${t} COMMAND rg-kernel-tests ${t})
  set_tests_properties(kernel.${t} PROPERTIES TIMEOUT 60 LABELS kernel)
endforeach()

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   non_preemption_control: injects a preemption mid-loop
#   di_ei_control:          delivers an interrupt while EIE = 0
#   determinism_control:    perturbs the second replay by 1 us
#   intc_chain_control:     expects the old "stop at the first non-zero" rule
#   service_thread_control: the service run makes one kernel call more
#   poll_wait_control:      a 200 us timed poll instead of the poll wait (sees the flag late)
#   frame_native_control:   the frame-driven scenario on the HLE scheduler (cfg.native = 0)
#   pace_control:           paced mode without the debt bound (60 phases back to back after a hitch)
foreach(t non_preemption di_ei determinism intc_chain service_thread poll_wait frame_native pace)
  add_test(NAME kernel.${t}_control COMMAND rg-kernel-tests ${t}_control)
  set_tests_properties(kernel.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS kernel)
endforeach()

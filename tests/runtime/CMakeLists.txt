# SPDX-License-Identifier: CC0-1.0
# rg_runtime tests (docs/RUNTIME.md "Tests").  ctest -L runtime
add_executable(rg-runtime-tests runtime_tests.c)
target_link_libraries(rg-runtime-tests PRIVATE rg_runtime_demo_guest rg_runtime rg_flags)
if(WIN32)
  target_compile_definitions(rg-runtime-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(_tmp ${CMAKE_CURRENT_BINARY_DIR}/tmp)
file(MAKE_DIRECTORY ${_tmp})

set(RG_RUNTIME_TESTS init_order vblank_rate audio_field pad_script cdvd_async smoke_all crt0 kernel_glue
    audio_wav)
foreach(t IN LISTS RG_RUNTIME_TESTS)
  file(MAKE_DIRECTORY ${_tmp}/${t})
  add_test(NAME runtime.${t} COMMAND rg-runtime-tests ${t} ${_tmp}/${t})
  # the demo drives the bring-up sound / SIF path: these run on the IOP HLE (docs/NATIVE-IOP.md)
  set_tests_properties(runtime.${t} PROPERTIES TIMEOUT 300 LABELS runtime ENVIRONMENT "RG_IOP=hle")
endforeach()
# RG_IOP=native: the boot leaves no SIF / IOP behind; the demo's pad on the native service
foreach(t init_order pad_script)
  file(MAKE_DIRECTORY ${_tmp}/native_${t})
  add_test(NAME runtime.native.${t} COMMAND rg-runtime-tests ${t} ${_tmp}/native_${t})
  set_tests_properties(runtime.native.${t} PROPERTIES TIMEOUT 300 LABELS "runtime;native_iop" ENVIRONMENT "RG_IOP=native")
endforeach()

# the demo through the GPU renderer (cfg.gpu; WARP, RG_GPU_HW=1 the adapter):
# the software GS's frame, game RAM below 0x10000000 (docs/GPU.md "Real game
# validation").  Skips without src/gpu.
if(TARGET rg_gpu)
  target_compile_definitions(rg-runtime-tests PRIVATE RG_HAVE_GPU=1)
endif()
file(MAKE_DIRECTORY ${_tmp}/gpu_smoke)
add_test(NAME runtime.gpu_smoke COMMAND rg-runtime-tests gpu_smoke ${_tmp}/gpu_smoke)
set_tests_properties(runtime.gpu_smoke PROPERTIES TIMEOUT 300 LABELS runtime SKIP_RETURN_CODE 77 ENVIRONMENT "RG_IOP=hle")

# with an extracted disc only (RG_DATA): SYSTEM.CNF through the whole stack
file(MAKE_DIRECTORY ${_tmp}/cdvd_realdata)
add_test(NAME runtime.cdvd_realdata COMMAND rg-runtime-tests cdvd_realdata ${_tmp}/cdvd_realdata)
set_tests_properties(runtime.cdvd_realdata PROPERTIES TIMEOUT 300 LABELS runtime SKIP_RETURN_CODE 77 ENVIRONMENT "RG_IOP=hle")

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   vblank_rate_control: expects a 60.00 Hz field count (60 VBLANK_ENDs in 1 s)
#   pad_script_control:  expects the script one VBlank late
foreach(t vblank_rate pad_script)
  file(MAKE_DIRECTORY ${_tmp}/${t}_control)
  add_test(NAME runtime.${t}_control COMMAND rg-runtime-tests ${t}_control ${_tmp}/${t}_control)
  set_tests_properties(runtime.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 300 LABELS runtime ENVIRONMENT "RG_IOP=hle")
endforeach()

# Determinism: two separate processes run rg-runtime-demo headless for 10
# virtual seconds (600 fields, every part, a pad script, the display folded in
# every 60 fields) and must print the same run_hash.  The control runs the
# second process with a script that differs on one VBlank: same-hash fails.
set(_det_args -DDEMO=$<TARGET_FILE:rg-runtime-demo> -DFIELDS=600
    -DSCRIPT=${CMAKE_CURRENT_SOURCE_DIR}/data/det_input.txt)
add_test(NAME runtime.determinism
  COMMAND ${CMAKE_COMMAND} ${_det_args} -DOTHER=${CMAKE_CURRENT_SOURCE_DIR}/data/det_input.txt
          -DOUT=${_tmp}/determinism -P ${CMAKE_CURRENT_SOURCE_DIR}/determinism.cmake)
add_test(NAME runtime.determinism_control
  COMMAND ${CMAKE_COMMAND} ${_det_args} -DOTHER=${CMAKE_CURRENT_SOURCE_DIR}/data/det_input_other.txt
          -DOUT=${_tmp}/determinism_control -P ${CMAKE_CURRENT_SOURCE_DIR}/determinism.cmake)
set_tests_properties(runtime.determinism PROPERTIES TIMEOUT 600 LABELS runtime ENVIRONMENT "RG_IOP=hle")
set_tests_properties(runtime.determinism_control PROPERTIES TIMEOUT 600 LABELS runtime WILL_FAIL TRUE ENVIRONMENT "RG_IOP=hle")

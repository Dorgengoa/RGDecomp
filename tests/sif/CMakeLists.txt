# SPDX-License-Identifier: CC0-1.0
# SIF/IOP HLE tests (included from src/sce/sif/CMakeLists.txt). ctest -L sif
add_executable(rg-sif-tests sif_tests.c)
target_link_libraries(rg-sif-tests PRIVATE rg_sce_sif rg_ps2_iop_hle rg_ps2_sif rg_ps2_iop rg_ps2_kernel rg_flags)
if(WIN32)
  target_compile_definitions(rg-sif-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(RG_SIF_TESTS dma_iop_ram rpc_call rpc_async registry unknown sdk_kernel native_sdk)
foreach(t IN LISTS RG_SIF_TESTS)
  add_test(NAME sif.${t} COMMAND rg-sif-tests ${t})
  set_tests_properties(sif.${t} PROPERTIES TIMEOUT 60 LABELS sif RESOURCE_LOCK rg_sif_tmp
    ENVIRONMENT "RG_SIF_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
endforeach()

# RESOURCE_LOCK: every test shares RG_SIF_TMP (native_sdk and its control write the same
# host0:SIF_NATIVE_FIO.BIN; ctest -j2 interleaved them once, 2026-10-18).
# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   dma_iop_ram_control: expects the SIF1 data at the wrong IOP address
#   rpc_async_control:   delivers async completions early, ignoring the latency
#   native_sdk_control:  one HLE call in native mode must show in the census counter
foreach(t dma_iop_ram rpc_async native_sdk)
  add_test(NAME sif.${t}_control COMMAND rg-sif-tests ${t}_control)
  set_tests_properties(sif.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS sif RESOURCE_LOCK rg_sif_tmp
    ENVIRONMENT "RG_SIF_TMP=${CMAKE_CURRENT_BINARY_DIR};RG_IOP_QUIET=1")
endforeach()

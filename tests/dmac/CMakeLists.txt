# SPDX-License-Identifier: CC0-1.0
# DMAC model + libdma/libgraph/libpkt tests (docs/DMAC.md).  ctest -L dmac
add_executable(rg-dmac-tests dmac_tests.c)
target_link_libraries(rg-dmac-tests PRIVATE rg_sce_graphics rg_ps2_dmac rg_vu_retail rg_flags)
if(WIN32)
  target_compile_definitions(rg-dmac-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(RG_DMAC_TESTS
  chain_tags normal_spr dstat_interrupts mskpath3 sif_ipu_hooks
  path3_storeimage libgraph_env syncv_blocking)
foreach(t IN LISTS RG_DMAC_TESTS)
  add_test(NAME dmac.${t} COMMAND rg-dmac-tests ${t})
  set_tests_properties(dmac.${t} PROPERTIES TIMEOUT 120 LABELS dmac)
endforeach()

# Needs the retail ELF (RG_ELF, default ../work/SCUS_974.90); skipped (77) without it.
add_test(NAME dmac.vif1_vu1_retail COMMAND rg-dmac-tests vif1_vu1_retail)
set_tests_properties(dmac.vif1_vu1_retail PROPERTIES TIMEOUT 300 LABELS dmac SKIP_RETURN_CODE 77)

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   chain_tags_control:     RET ignores the address stack (ends the chain)
#   syncv_blocking_control: sceGsSyncV returns without waiting for VBLANK_START
foreach(t chain_tags syncv_blocking)
  add_test(NAME dmac.${t}_control COMMAND rg-dmac-tests ${t}_control)
  set_tests_properties(dmac.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS dmac)
endforeach()

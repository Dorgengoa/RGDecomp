# SPDX-License-Identifier: CC0-1.0
# D9 link gate (docs/NATIVE-ONLY.md), ctest label `native_only`.  Reads the rg-game map
# (tools/native/link_audit.py); skipped (77) until rg-game is built (EXCLUDE_FROM_ALL).
#   native_only.link_audit          RG_NATIVE_ONLY=ON: no library of the `iop` set
#                                   (SIF / IOP / padman+mcserv / sound HLE / SPU2 / CDVD
#                                   model / libcdvd / FS oracle) nor of the `kernel` set (EE
#                                   kernel HLE, its spin runtime and libkernl with the census
#                                   recorder: docs/NATIVE-THREADS.md "Native-only") nor the
#                                   VU0 model (`vu0`: docs/NATIVE-CPU.md section 8) nor the DMAC
#                                   model + libdma over it (`render-dma`) nor the register bus
#                                   (rg_ps2_hwbus) nor VIF1 / VU1 (`render-vu`) nor the GS
#                                   model / GS renderer (`render`: rg_ps2_gs, rg_gpu; builds
#                                   with the native device) nor libvu0 on the VU register
#                                   struct (`vu0lib`) nor the overlay arena manager
#                                   (`overlay`, with RG_NATIVE_OVL) is linked
#   native_only.link_audit_control  the same check on a default-config exe must FAIL (the
#                                   audit sees the oracles the run-time switch keeps linked):
#                                   rg-game in a default build, rg-game-oracle (the same-tree
#                                   twin, build it first) in a native-only build
#   native_only.link_report         the per-class size table (informational, always passes)
#   native_only.addr_census         D9 "no PS2 address arithmetic": tools/native/addr_census.py
#                                   --check over the compiled game set (+ this build's generated
#                                   overlay sources): 0 `arith` and 0 `marker` sites (HW
#                                   accessors, hardware / scratchpad literals, PS2_PHYS / UNCACHED /
#                                   UCAB markers, unreviewed KSEG masks, RG_PS2_ADDR_ defines,
#                                   arena / overlay-address maps, EE-RAM casts).  Pure text, runs in
#                                   every build.  A new site fails it; a literal that is not an
#                                   address goes into the script's REVIEWED table with a reason.
#   native_only.addr_census_control the same with one synthetic site per kind injected: must FAIL
if(RG_PYTHON)
  set(_ac ${CMAKE_SOURCE_DIR}/tools/native/addr_census.py)
  add_test(NAME native_only.addr_census COMMAND ${RG_PYTHON} ${_ac} --build ${CMAKE_BINARY_DIR} --check)
  add_test(NAME native_only.addr_census_control
           COMMAND ${RG_PYTHON} ${_ac} --build ${CMAKE_BINARY_DIR} --check --inject)
  set_tests_properties(native_only.addr_census_control PROPERTIES WILL_FAIL TRUE)
  set_tests_properties(native_only.addr_census native_only.addr_census_control
                       PROPERTIES LABELS native_only TIMEOUT 300)
  # the renderer's reads of game memory: every walker's host() checked (nr_game_ptr), every raw
  # dereference reviewed (tools/native/gameptr_census.py; docs/NATIVE-RENDER.md "Remembered packets")
  add_test(NAME native_only.gameptr_census COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/native/gameptr_census.py --check)
  set_tests_properties(native_only.gameptr_census PROPERTIES LABELS native_only TIMEOUT 60)
endif()
if(NOT TARGET rg-game OR NOT RG_PYTHON)
  return()
endif()
set(_la ${CMAKE_SOURCE_DIR}/tools/native/link_audit.py)
# + the VU0 model (rg_vu0: global register file + vcallms bridge) unless the build is
# RG_VU0_MODE=model, which links it on purpose (docs/NATIVE-CPU.md section 8)
if(RG_VU0_MODE STREQUAL "model")
  set(_forbid iop,kernel)
else()
  set(_forbid iop,kernel,vu0)
endif()
# + the DMAC model, libdma over it and the hardware register bus (renderer lane,
# docs/NATIVE-RENDER.md "DMA without the DMAC"): `render-dma` and rg_ps2_hwbus.  The rest of
# `render` (GS model + GPU renderer, VIF1 / VU1 for the overlay VU1 programs) is still linked:
# the full `render` set joins when they leave (docs/NATIVE-RENDER.md "Still emulated").
# + VIF1 / VU1 (`render-vu`, 2026-10-18 (8)): every VU1 program is native (nr_vux.c).
# + the GS model and its GPU renderer (`render`, 2026-10-24 (10)): the native state block, GIF
# input and device in rg_native_render (docs/NATIVE-RENDER.md "Checkpoint 10"); only where the
# device exists (rg_gpu: the D3D11 backend; headless Linux keeps the software GS model)
set(_forbid ${_forbid},render-dma,render-vu)
if(TARGET rg_gpu)
  set(_forbid ${_forbid},render)
endif()
# + libvu0 on the VU register struct (`vu0lib`, 2026-10-25): rg_native_vu0 (plain C lanes,
# docs/NATIVE-CPU.md section 9) replaces it unless the build is RG_VU0_MODE=model
if(NOT RG_VU0_MODE STREQUAL "model")
  set(_forbid ${_forbid},vu0lib)
endif()
# + the overlay arena manager (`overlay`: rg_ps2_overlay, rg_ps2_overlay_bind, rg_ovl_arena,
# rg_ovl_data, 2026-10-25): the native module table (src/native/ovl, docs/OVERLAY.md
# section 8) with RG_NATIVE_OVL
if(RG_NATIVE_OVL)
  set(_forbid ${_forbid},overlay)
endif()
set(_extra --extra rg_ps2_hwbus)
set(_map $<TARGET_FILE_DIR:rg-game>/rg-game.map)
if(RG_NATIVE_ONLY)
  add_test(NAME native_only.link_audit COMMAND ${RG_PYTHON} ${_la} check ${_map} --forbid ${_forbid} ${_extra} --skip-missing)
  set(_ctl $<TARGET_FILE_DIR:rg-game-oracle>/rg-game-oracle.map)
  set(_t native_only.link_audit native_only.link_audit_control)
else()
  set(_ctl ${_map})
  set(_t native_only.link_audit_control)
endif()
add_test(NAME native_only.link_audit_control COMMAND ${RG_PYTHON} ${_la} check ${_ctl} --forbid ${_forbid} ${_extra} --skip-missing)
set_tests_properties(native_only.link_audit_control PROPERTIES WILL_FAIL TRUE)
add_test(NAME native_only.link_report COMMAND ${RG_PYTHON} ${_la} report ${_map} --skip-missing)
set_tests_properties(${_t} native_only.link_report PROPERTIES LABELS native_only SKIP_RETURN_CODE 77 TIMEOUT 120)

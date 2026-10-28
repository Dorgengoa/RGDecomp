# SPDX-License-Identifier: CC0-1.0
# GPU renderer vs software reference (docs/GPU.md "Validation").  ctest -L gpu
# Runs on D3D11 WARP (headless); RG_GPU_HW=1 in the environment uses the GPU.
if(NOT TARGET rg_gpu)
  return()
endif()

# The tests/gs golden scenes, compiled again with every GS entry point
# renamed to the tee (gpu_tee.h is force-included).
add_library(rg_gpu_golden OBJECT
  ${CMAKE_SOURCE_DIR}/tests/gs/test_gs_prim.c
  ${CMAKE_SOURCE_DIR}/tests/gs/test_gs_pixel.c
  ${CMAKE_SOURCE_DIR}/tests/gs/test_gs_clut.c
  ${CMAKE_SOURCE_DIR}/tests/gs/test_gs_display.c)
target_include_directories(rg_gpu_golden PRIVATE ${CMAKE_SOURCE_DIR}/tests/gs
  ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(rg_gpu_golden PRIVATE
  "SHELL:-include ${CMAKE_CURRENT_SOURCE_DIR}/gpu_tee.h")
target_compile_definitions(rg_gpu_golden PRIVATE _CRT_SECURE_NO_WARNINGS)
target_link_libraries(rg_gpu_golden PRIVATE rg_ps2_gs rg_flags)

add_executable(rg-gpu-tests
  gpu_tests.c
  gpu_tee.c
  gpu_compare.c
  gpu_scenes.c
  gpu_replay.c
  gpu_gfx_tests.c
  $<TARGET_OBJECTS:rg_gpu_golden>)
target_link_libraries(rg-gpu-tests PRIVATE rg_gpu rg_ps2_gs rg_flags rg_settings)
target_compile_definitions(rg-gpu-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-gpu-tests PRIVATE -Wall -Wextra)
endif()

set(RG_GPU_GOLDEN
  prim_sprite prim_triangle prim_shading prim_line_point prim_queue
  prim_texture_wrap prim_bilinear prim_perspective prim_mipmap prim_env prim_fullscreen
  prim_sprite_uv
  blend_presets blend_misc depth_matrix alpha_matrix dither_fog tex_functions
  clut_csm1_t8 clut_csm1_t4_ct16 clut_csm1_t4_ct32 clut_csm2 clut_cld
  display_one display_merge display_interlace display_antiflicker display_ct16)
set(RG_GPU_SCENES
  formats offscreen blend_flat ordered blend_gouraud tex_point tex_filter pixel_ops prims coherence
  display frame640 rtt_formats rtt_depth rtt_feedback rtt_upscaled rtt_alias rtt_flip split
  alias_pages exact_float)

add_test(NAME gpu.info COMMAND rg-gpu-tests info)
set_tests_properties(gpu.info PROPERTIES TIMEOUT 60 LABELS gpu)
foreach(t IN LISTS RG_GPU_GOLDEN)
  add_test(NAME gpu.golden.${t} COMMAND rg-gpu-tests golden.${t})
  set_tests_properties(gpu.golden.${t} PROPERTIES TIMEOUT 300 LABELS gpu)
endforeach()
foreach(t IN LISTS RG_GPU_SCENES)
  add_test(NAME gpu.scene.${t} COMMAND rg-gpu-tests scene.${t})
  set_tests_properties(gpu.scene.${t} PROPERTIES TIMEOUT 600 LABELS gpu)
endforeach()
# Internal resolution x2: exact 2D scenes must still match after write-back
# and display read-out (docs/GPU.md "Upscaling").
foreach(t blend_flat pixel_ops display rtt_feedback rtt_upscaled rtt_alias rtt_flip)
  add_test(NAME gpu.scale2.${t} COMMAND rg-gpu-tests scale2.${t})
  set_tests_properties(gpu.scale2.${t} PROPERTIES TIMEOUT 600 LABELS gpu)
endforeach()
# rtt_formats' bloom downsamples hard-edged content, which direct
# (upscaled) sampling resolves differently by design: exact through the
# native-mirror path (gpu_config.rtt_native), as before direct sampling.
add_test(NAME gpu.scale2.rtt_formats COMMAND rg-gpu-tests scale2n.rtt_formats)
set_tests_properties(gpu.scale2.rtt_formats PROPERTIES TIMEOUT 600 LABELS gpu)
# x4: render targets sampled directly at the internal resolution (bloom,
# DOF, the per-frame flip copy) within the documented tolerance
foreach(t rtt_upscaled rtt_flip)
  add_test(NAME gpu.scale4.${t} COMMAND rg-gpu-tests scale4.${t})
  set_tests_properties(gpu.scale4.${t} PROPERTIES TIMEOUT 900 LABELS gpu)
endforeach()
# Deliberately-wrong control: the GPU blend shifts by 6 instead of 7 in
# scene.blend_flat; the comparison must catch it.
add_test(NAME gpu.control COMMAND rg-gpu-tests control)
set_tests_properties(gpu.control PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: render-target feedback splitting off in
# scene.rtt_feedback (primitives sample memory drawn earlier in their batch
# from the stale mirror); the comparison must catch it.
add_test(NAME gpu.control_feedback COMMAND rg-gpu-tests control_feedback)
set_tests_properties(gpu.control_feedback PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: rtt_upscaled at x2 with direct sampling off
# (render targets read through the native mirror); the upscaled-detail and
# no-write-back checks must fail.
add_test(NAME gpu.control_direct COMMAND rg-gpu-tests control_direct)
set_tests_properties(gpu.control_direct PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: FRAME and ZBUF on the same pages drawn by two
# GPU targets instead of the software rasterizer; must fail.
add_test(NAME gpu.control_alias COMMAND rg-gpu-tests control_alias)
set_tests_properties(gpu.control_alias PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Real game frames (docs/GPU.md "Real game validation"): every GS recording
# (*.rggs, made by rg-game with RG_GS_REC / RG_GS_REC_FIELDS) under
# out/p3/gsrec replayed through the reference and the GPU in lockstep: FIFO
# reads, every field's display and the final local memory must be identical
# (x2: box-filtered, +-64 with 200 ppm beyond).  Recordings are game data and never committed:
# skipped without RG_DATA or recordings.
set(RG_GPU_REPLAY_DIR ${CMAKE_SOURCE_DIR}/out/p3/gsrec CACHE PATH "GS recordings for gpu.game_replay")
add_test(NAME gpu.game_replay COMMAND rg-gpu-tests replay-all ${RG_GPU_REPLAY_DIR})
add_test(NAME gpu.scale2.game_replay COMMAND rg-gpu-tests scale2.replay-all ${RG_GPU_REPLAY_DIR})
set_tests_properties(gpu.game_replay gpu.scale2.game_replay PROPERTIES
  TIMEOUT 1800 LABELS gpu SKIP_RETURN_CODE 77)
# Deliberately-wrong control: triangles through float attribute interpolation
# (gpu_config.fault = 4) held to the exact-triangle tolerance 0 in
# scene.frame640 (a Gouraud triangle); must fail, proving the exact path is
# what makes triangles bit-exact (docs/GPU.md "Exact triangles").
add_test(NAME gpu.control_exact COMMAND rg-gpu-tests control_exact)
set_tests_properties(gpu.control_exact PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: exact triangles drawn as triangles, leaving
# coverage to the rasterizer, in scene.offscreen; must fail on a device that
# clips large triangles into fans (WARP: pixels on the fans' inner edges drawn
# twice or not at all); skipped (77) on one that does not (RTX 3080).
# Deliberately-wrong control: scene.ordered with the overlapping
# destination-reading primitives batched together but drawn from one
# snapshot (gpu_config.fault = 6, no ordered view); must fail, proving the
# scene's overlaps exercise ordered blending (docs/GPU.md "Performance").
add_test(NAME gpu.control_ordered COMMAND rg-gpu-tests control_ordered)
set_tests_properties(gpu.control_ordered PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: split pages (docs/GPU.md "Performance",
# checkpoint 3) merged without their mask (gpu_config.fault = 8: the whole
# page from gs->vram, stale outside the transfers' bits) in the field_7600
# recording and in scene.split; each must fail, proving both merge split pages.
add_test(NAME gpu.control_merge COMMAND rg-gpu-tests replay ${RG_GPU_REPLAY_DIR}/field_7600.rggs)
set_tests_properties(gpu.control_merge PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu
  ENVIRONMENT RG_GPU_FAULT=8)
add_test(NAME gpu.control_merge_scene COMMAND rg-gpu-tests scene.split)
set_tests_properties(gpu.control_merge_scene PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu
  ENVIRONMENT RG_GPU_FAULT=8)
# Pipelined display read-back (gpu_config.readback_lag): every read returns
# the previous frame bit for bit (docs/GPU.md "Performance"); game data.
add_test(NAME gpu.readback_lag COMMAND rg-gpu-tests lag ${RG_GPU_REPLAY_DIR}/load_2400.rggs)
set_tests_properties(gpu.readback_lag PROPERTIES TIMEOUT 600 LABELS gpu SKIP_RETURN_CODE 77)
# Deliberately-wrong controls for scene.alias_pages (docs/GPU.md "Checkpoint
# 4"): colour and depth targets sharing pages left live without the
# write-backs around their draws (fault 10), and the reference reading
# texture memory as the primitive writes it (no snapshot); each must fail.
add_test(NAME gpu.control_shared COMMAND rg-gpu-tests control_shared)
set_tests_properties(gpu.control_shared PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
add_test(NAME gpu.control_selfread COMMAND rg-gpu-tests control_selfread)
set_tests_properties(gpu.control_selfread PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: the exact-triangle shader takes every float
# value without its bound (fault 12); scene.exact_float must then fail.
add_test(NAME gpu.control_floatpath COMMAND rg-gpu-tests control_floatpath)
set_tests_properties(gpu.control_floatpath PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: CPU reads of split pages served from gs->vram
# without checking the transfer bits cover them (fault 14); must fail.
add_test(NAME gpu.control_readcurrent COMMAND rg-gpu-tests control_readcurrent)
set_tests_properties(gpu.control_readcurrent PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: early copies of hot read-back regions kept
# after later draws into their pages (fault 16); scene.rtt_depth must fail.
add_test(NAME gpu.control_early COMMAND rg-gpu-tests control_early)
set_tests_properties(gpu.control_early PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
# Deliberately-wrong control: decoded textures (docs/GPU.md "Performance")
# with the red channel of every decoded texel off by one (gpu_config.fault =
# 7) in scene.tex_point; must fail, proving the scenes sample the decoded copy.
add_test(NAME gpu.control_decode COMMAND rg-gpu-tests control_decode)
set_tests_properties(gpu.control_decode PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu)
add_test(NAME gpu.control_cover COMMAND rg-gpu-tests control_cover)
set_tests_properties(gpu.control_cover PROPERTIES WILL_FAIL TRUE TIMEOUT 600 LABELS gpu
  SKIP_RETURN_CODE 77)
# Graphics settings (docs/GPU.md "Graphics settings"): each option's effect
# on a synthetic scene, the Original preset bit-exact with the reference, and
# the game recordings with the Original preset applied through the settings.
foreach(t original settings_map internal_res texture_filter anisotropic ssaa fxaa sharpen color
        output_filter resample)
  add_test(NAME gpu.gfx.${t} COMMAND rg-gpu-tests gfx.${t})
  set_tests_properties(gpu.gfx.${t} PROPERTIES TIMEOUT 600 LABELS "gpu;settings")
endforeach()
add_test(NAME gpu.gfx.game_replay COMMAND rg-gpu-tests gfx.replay-all ${RG_GPU_REPLAY_DIR})
set_tests_properties(gpu.gfx.game_replay PROPERTIES TIMEOUT 1800 LABELS "gpu;settings"
  SKIP_RETURN_CODE 77)
# The anti-flicker display merge at the internal resolution (x2, x4).
foreach(s 2 4)
  add_test(NAME gpu.scale${s}.af_upscaled COMMAND rg-gpu-tests scale${s}.af_upscaled)
  set_tests_properties(gpu.scale${s}.af_upscaled PROPERTIES TIMEOUT 600 LABELS gpu)
endforeach()

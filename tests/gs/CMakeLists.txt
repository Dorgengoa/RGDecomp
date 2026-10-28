# SPDX-License-Identifier: CC0-1.0
# GS model tests (docs/GS.md).  ctest -L gs
add_executable(rg-gs-tests
  gs_tests.c
  test_gs_swizzle.c
  test_gs_xfer.c
  test_gs_clut.c
  test_gs_pixel.c
  test_gs_prim.c
  test_gs_gif.c
  test_gs_display.c
  test_gs_sinks.c)
# vu.h / vif.h for the sink-signature check only (headers, no link)
target_include_directories(rg-gs-tests PRIVATE
  ${CMAKE_SOURCE_DIR}/src/ps2/vu ${CMAKE_SOURCE_DIR}/src/ps2/vif)
target_link_libraries(rg-gs-tests PRIVATE rg_ps2_gs rg_flags)
if(WIN32)
  target_compile_definitions(rg-gs-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

set(RG_GS_TESTS
  swizzle_tables swizzle_bijection
  xfer_roundtrip xfer_split xfer_l2l xfer_alias xfer_separable xfer_bulk xfer_mask
  clut_csm1_t8 clut_csm1_t4_ct16 clut_csm1_t4_ct32 clut_csm2 clut_cld
  blend_presets blend_misc depth_matrix alpha_matrix dither_fog tex_functions
  prim_sprite prim_triangle prim_shading prim_line_point prim_queue
  prim_texture_wrap prim_bilinear prim_perspective prim_mipmap prim_env prim_fullscreen
  prim_sprite_uv prim_self_read
  gif_packed gif_reglist_tags gif_arbitration gif_signal gif_sinks
  display_one display_merge display_interlace display_antiflicker display_ct16)
foreach(t IN LISTS RG_GS_TESTS)
  add_test(NAME gs.${t} COMMAND rg-gs-tests ${t})
  set_tests_properties(gs.${t} PROPERTIES TIMEOUT 120 LABELS gs)
endforeach()

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   swizzle_control: reference block table with blocks 1 and 2 swapped
#   blend_control:   expects preset 1 to produce preset 2's pixel
#   xfer_bulk_control: one IMAGE bit flipped on the bulk side only
foreach(t swizzle_control blend_control xfer_bulk_control)
  add_test(NAME gs.${t} COMMAND rg-gs-tests ${t})
  set_tests_properties(gs.${t} PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS gs)
endforeach()

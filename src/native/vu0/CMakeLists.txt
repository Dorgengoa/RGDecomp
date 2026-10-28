# SPDX-License-Identifier: CC0-1.0
# Native VU0 side (docs/NATIVE-CPU.md section 9, PLAN.md D9): what the game links for its
# VU0 use besides the inline vu0frame code of port/vu0.h.
#   rg_native_vu0   libvu0 (the sceVu0* functions) as plain C on float lanes, the game's
#                   only VU0 microprogram as C (rg_vu0_srt) and the two named contexts of
#                   the cross-file protocols (xfbox, colltri).  Float rules follow
#                   RG_VU0_MODE (native: IEEE single + the VU clamp rules; local: VU
#                   rounding).  RG_NATIVE_ONLY links it in place of rg_sce_vu0 (the libvu0
#                   transcription on the VU register struct, cmake/native_only.cmake).
#   native_vu0.libvu0   bit-exact comparison against rg_sce_vu0's libvu0.c in the same mode
add_library(rg_native_vu0 STATIC libvu0_native.c vu0_srt.c vu0_ctx.c)
target_include_directories(rg_native_vu0 PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_definitions(rg_native_vu0 PRIVATE ${RG_VU0_DEFS})
target_link_libraries(rg_native_vu0 PRIVATE rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_vu0 PRIVATE -Wall -Wextra)
endif()

if(NOT RG_VU0_MODE STREQUAL "model")
  add_library(rg_native_vu0_cmp OBJECT libvu0_native.c)
  target_include_directories(rg_native_vu0_cmp PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_compile_definitions(rg_native_vu0_cmp PRIVATE ${RG_VU0_DEFS} RG_VU0N_TEST=1)
  target_link_libraries(rg_native_vu0_cmp PRIVATE rg_flags)
  add_executable(rg-native-vu0-tests native_vu0_tests.c $<TARGET_OBJECTS:rg_native_vu0_cmp>)
  target_compile_definitions(rg-native-vu0-tests PRIVATE ${RG_VU0_DEFS})
  target_link_libraries(rg-native-vu0-tests PRIVATE rg_sce_vu0 rg_flags)
  add_test(NAME native_vu0.libvu0 COMMAND rg-native-vu0-tests)
  add_test(NAME native_vu0.libvu0_control COMMAND rg-native-vu0-tests --wrong)
  set_tests_properties(native_vu0.libvu0 native_vu0.libvu0_control PROPERTIES
    LABELS "port;vu0native;native_only" TIMEOUT 120)
  set_tests_properties(native_vu0.libvu0_control PROPERTIES WILL_FAIL TRUE)
endif()

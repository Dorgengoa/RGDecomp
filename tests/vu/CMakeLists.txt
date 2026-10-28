# SPDX-License-Identifier: CC0-1.0
# VU / VIF tests (docs/VU.md).  Run: ctest -L vu
add_executable(rg-vu-tests vu_tests.c vu_test.h)
target_link_libraries(rg-vu-tests PRIVATE rg_ps2_vu rg_flags)
add_executable(rg-vif-tests vif_tests.c vu_test.h)
target_link_libraries(rg-vif-tests PRIVATE rg_ps2_vif rg_flags)

set(RG_VU_TESTS
  decode_retail arith acc_forms efu2 vf0_const opmula_cross float_edges ftoi_itof
  mac_latency mac_dest_mask flags_overflow_underflow stall_shifts_flags
  clip clip_24bit q_latency waitq_div_chain div_special efu integer memory
  move_mr32 pair_order loi random branches cond_branches ebit_tpc
  ebit_with_branch int_branch_quirk xgkick xtop vu0_window runaway_budget)
# vu.<t>: default (VU1 block translator on); vu.interp.<t>: RG_VU_BLOCKS=0;
# vu.check.<t>: RG_VU_BLOCKS_CHECK=1 (every block also run on the interpreter
# and compared, docs/VU.md "Block translator")
foreach(t IN LISTS RG_VU_TESTS)
  add_test(NAME vu.${t} COMMAND rg-vu-tests ${t})
  add_test(NAME vu.interp.${t} COMMAND rg-vu-tests ${t})
  add_test(NAME vu.check.${t} COMMAND rg-vu-tests ${t})
  set_tests_properties(vu.${t} vu.interp.${t} vu.check.${t} PROPERTIES TIMEOUT 60 LABELS vu)
  set_tests_properties(vu.interp.${t} PROPERTIES ENVIRONMENT RG_VU_BLOCKS=0)
  set_tests_properties(vu.check.${t} PROPERTIES ENVIRONMENT RG_VU_BLOCKS_CHECK=1)
endforeach()

set(RG_VIF_TESTS
  unpack_s unpack_v2_v3 unpack_v3_w unpack_v3_w_split unpack_v4 unpack_skip_fill unpack_mask_mode
  tops_double_buffer direct_and_kick split_stream irq_stall vif0)
foreach(t IN LISTS RG_VIF_TESTS)
  add_test(NAME vif.${t} COMMAND rg-vif-tests ${t})
  set_tests_properties(vif.${t} PROPERTIES TIMEOUT 60 LABELS vu)
endforeach()

# Differential fuzzer of the VU1 block translator against the interpreter
# (docs/VU.md "Block translator"): random programs, registers and budgets,
# the two must agree on all state after every vu_run.
add_executable(rg-vu-blkfuzz vu_blkfuzz.c)
target_link_libraries(rg-vu-blkfuzz PRIVATE rg_ps2_vu rg_flags)
add_test(NAME vu.blkfuzz COMMAND rg-vu-blkfuzz 4000 0x12345)
add_test(NAME vu.blkfuzz_check COMMAND rg-vu-blkfuzz 1500 0x9E3779B9 --check)
add_test(NAME vu.blkfuzz_control COMMAND rg-vu-blkfuzz 200 0x12345 --control)
# a pool of 5 blocks: flushed all the time, while runs are in flight
add_test(NAME vu.blkfuzz_pool COMMAND rg-vu-blkfuzz 1000 0xC0FFEE --check)
set_tests_properties(vu.blkfuzz_pool PROPERTIES ENVIRONMENT RG_VU_BLOCKS_POOL=5)
set_tests_properties(vu.blkfuzz vu.blkfuzz_check vu.blkfuzz_control vu.blkfuzz_pool PROPERTIES TIMEOUT 600 LABELS vu)
set_tests_properties(vu.blkfuzz_control PROPERTIES WILL_FAIL TRUE)

# Differential test of the VU float helpers against the pre-rewrite
# ldexp/frexp reference copy (docs/VU.md "Performance").  The ctest runs the
# full edge cross product (16.7 M pairs per binary class) plus 1 M random
# cases per class; the long proof runs (`rg-vu-float-diff CLASS 1000000000`,
# `rg-vu-float-diff to_d 0` exhaustive) are recorded in docs/VU.md.
add_executable(rg-vu-float-diff vu_float_diff.c vu_float_ref.c vu_float_ref.h)
target_link_libraries(rg-vu-float-diff PRIVATE rg_ps2_vu rg_flags)
foreach(t to_d from_d add sub mul madd msub ftoi itof cmp clip div sqrt rsqrt efu vec)
  add_test(NAME vu.float_diff.${t} COMMAND rg-vu-float-diff ${t} 1000000)
  set_tests_properties(vu.float_diff.${t} PROPERTIES TIMEOUT 300 LABELS vu)
endforeach()
# control: add compared against mul must report mismatches
add_test(NAME vu.float_diff_control COMMAND rg-vu-float-diff control)
set_tests_properties(vu.float_diff_control PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS vu)

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   vu.mac_latency_control:  expects MAC flags visible 3 cycles after issue
#   vif.unpack_v4_control:   expects V4-5 without the 5->8 bit expansion
add_test(NAME vu.mac_latency_control COMMAND rg-vu-tests mac_latency_control)
add_test(NAME vif.unpack_v4_control COMMAND rg-vif-tests unpack_v4_control)
set_tests_properties(vu.mac_latency_control vif.unpack_v4_control
  PROPERTIES WILL_FAIL TRUE TIMEOUT 60 LABELS vu)

# Whole-program smoke tests on the retail microcode.  Need the retail ELF
# (RG_ELF, default ../work/SCUS_974.90); skipped (77) without it.
add_executable(rg-vu-smoke vu_smoke.c vu_test.h)
target_link_libraries(rg-vu-smoke PRIVATE rg_ps2_vif rg_vu_retail rg_flags)
target_compile_definitions(rg-vu-smoke PRIVATE RG_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
if(WIN32)
  target_compile_definitions(rg-vu-smoke PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
foreach(t census vu0_srt variants)
  add_test(NAME vu.smoke.${t} COMMAND rg-vu-smoke ${t})
  set_tests_properties(vu.smoke.${t} PROPERTIES TIMEOUT 300 LABELS vu SKIP_RETURN_CODE 77)
endforeach()
# control: the second run gets a different input seed, so "deterministic"
# must be reported as violated
add_test(NAME vu.smoke.variants_control COMMAND rg-vu-smoke variants_control)
set_tests_properties(vu.smoke.variants_control PROPERTIES WILL_FAIL TRUE TIMEOUT 300 LABELS vu SKIP_RETURN_CODE 77)

# Replay of PCSX2 VIF1/VU1 frame captures (docs/VALIDATION.md section 5,
# docs/VU.md "Validation against PCSX2").  The captures live in out/captures
# (gitignored, produced by tools/trace/vucap.py); each test is skipped (77)
# when its capture is absent.
add_executable(rg-vu-replay vu_replay.c)
target_link_libraries(rg-vu-replay PRIVATE rg_ps2_vif rg_ps2_vu rg_flags)
if(WIN32)
  target_compile_definitions(rg-vu-replay PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
set(RG_VIFCAP_DIR "${PROJECT_SOURCE_DIR}/out/captures")
set(RG_VIFCAP_FRAMES 01956 01958 01960 01962 09002 09004 09006 09008 24804 24806 24808)
foreach(f IN LISTS RG_VIFCAP_FRAMES)
  add_test(NAME vu.replay.v${f} COMMAND rg-vu-replay "${RG_VIFCAP_DIR}/C_v${f}.vifcap")
  set_tests_properties(vu.replay.v${f} PROPERTIES TIMEOUT 300 LABELS vu SKIP_RETURN_CODE 77)
endforeach()
# The same replay on the pre-optimisation interpreter (tests/vu/ref: verbatim
# copies of src/ps2/vu at checkpoint 0a6381a, before docs/VU.md "Performance")
# with the live VIF.  vu.replay_same.* runs both and requires identical HASH
# lines (PATH1 stream, final VU1 memory and registers, cycle count).
add_executable(rg-vu-replay-ref vu_replay.c ${PROJECT_SOURCE_DIR}/src/ps2/vif/vif.c
  ref/vu.c ref/vu_float.c ref/vu_decode.c ref/vu_disasm.c)
target_include_directories(rg-vu-replay-ref BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ref
  ${PROJECT_SOURCE_DIR}/src/ps2/vif)
target_link_libraries(rg-vu-replay-ref PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg-vu-replay-ref PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
# Each capture three ways (docs/VU.md "Block translator"):
#   vu.replay_same.*        default: VU1 block translator on (and armed)
#   vu.replay_same_interp.* RG_VU_BLOCKS=0: the interpreter only
#   vu.replay_check.*       RG_VU_BLOCKS_CHECK=1: every block also run on the
#                           interpreter and the full state compared (aborts)
foreach(f IN LISTS RG_VIFCAP_FRAMES)
  set(cap ${RG_VIFCAP_DIR}/C_v${f}.vifcap)
  add_test(NAME vu.replay_same.v${f} COMMAND ${CMAKE_COMMAND}
    -DLIVE=$<TARGET_FILE:rg-vu-replay> -DREF=$<TARGET_FILE:rg-vu-replay-ref>
    -DCAP=${cap} -DNEED_BLOCKS=1 -P ${CMAKE_CURRENT_SOURCE_DIR}/replay_same.cmake)
  add_test(NAME vu.replay_same_interp.v${f} COMMAND ${CMAKE_COMMAND}
    -DLIVE=$<TARGET_FILE:rg-vu-replay> -DREF=$<TARGET_FILE:rg-vu-replay-ref>
    -DCAP=${cap} -DENV=RG_VU_BLOCKS=0 -P ${CMAKE_CURRENT_SOURCE_DIR}/replay_same.cmake)
  add_test(NAME vu.replay_check.v${f} COMMAND ${CMAKE_COMMAND}
    -DLIVE=$<TARGET_FILE:rg-vu-replay> -DREF=$<TARGET_FILE:rg-vu-replay-ref>
    -DCAP=${cap} -DENV=RG_VU_BLOCKS_CHECK=1 -DNEED_BLOCKS=1 -P ${CMAKE_CURRENT_SOURCE_DIR}/replay_same.cmake)
  set_tests_properties(vu.replay_same.v${f} vu.replay_same_interp.v${f} vu.replay_check.v${f}
    PROPERTIES TIMEOUT 600 LABELS vu SKIP_REGULAR_EXPRESSION "SKIP:")
endforeach()

# Random programs (vu_fuzzgen.h) on the live build and on the reference copy:
# the same FUZZHASH with the translator on, off, and lockstep-checked.  The
# programs make the integer-branch quirk fire, so these also cover the VI
# history rewrite of the interpreter.
add_executable(rg-vu-progfuzz vu_progfuzz.c vu_fuzzgen.h)
target_link_libraries(rg-vu-progfuzz PRIVATE rg_ps2_vu rg_flags)
add_executable(rg-vu-progfuzz-ref vu_progfuzz.c vu_fuzzgen.h
  ref/vu.c ref/vu_float.c ref/vu_decode.c ref/vu_disasm.c)
target_include_directories(rg-vu-progfuzz-ref BEFORE PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ref)
target_link_libraries(rg-vu-progfuzz-ref PRIVATE rg_flags)
foreach(m blocks interp check)
  if(m STREQUAL "blocks")
    set(env "")
    set(need 1)
  elseif(m STREQUAL "interp")
    set(env RG_VU_BLOCKS=0)
    set(need 0)
  else()
    set(env RG_VU_BLOCKS_CHECK=1)
    set(need 1)
  endif()
  add_test(NAME vu.progfuzz_same.${m} COMMAND ${CMAKE_COMMAND}
    -DLIVE=$<TARGET_FILE:rg-vu-progfuzz> -DREF=$<TARGET_FILE:rg-vu-progfuzz-ref>
    -DENV=${env} -DKEY=FUZZHASH -DARGS=3000 -DNEED_BLOCKS=${need}
    -P ${CMAKE_CURRENT_SOURCE_DIR}/replay_same.cmake)
  set_tests_properties(vu.progfuzz_same.${m} PROPERTIES TIMEOUT 600 LABELS vu)
endforeach()

# control: one flipped payload bit in the first UNPACK must be detected
add_test(NAME vu.replay_control COMMAND rg-vu-replay "${RG_VIFCAP_DIR}/C_v09002.vifcap" --control)
set_tests_properties(vu.replay_control PROPERTIES WILL_FAIL TRUE TIMEOUT 300 LABELS vu SKIP_RETURN_CODE 77)

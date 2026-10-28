# SPDX-License-Identifier: CC0-1.0
# Run a live build and the pre-optimisation reference build (tests/vu/ref)
# of the same program and require identical result lines (docs/VU.md
# "Performance", "Block translator").
#   cmake -DLIVE=.. -DREF=.. -DCAP=.. [-DENV="RG_VU_BLOCKS=0;..."] [-DKEY=HASH]
#         [-DARGS="a;b"] [-DNEED_BLOCKS=1] -P replay_same.cmake
# CAP: a capture file (skipped when absent) or empty.  ENV: environment of
# the live run.  KEY: the result line's first word (HASH for rg-vu-replay,
# FUZZHASH for rg-vu-progfuzz).  NEED_BLOCKS: the live run must report
# translated pairs when it ran any pairs (proves the translator was armed).
if(NOT KEY)
  set(KEY HASH)
endif()
set(run_args)
if(CAP)
  if(NOT EXISTS "${CAP}")
    message("SKIP: no capture ${CAP}")
    return()
  endif()
  list(APPEND run_args "${CAP}")
endif()
if(ARGS)
  list(APPEND run_args ${ARGS})
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E env ${ENV} "${LIVE}" ${run_args}
                OUTPUT_VARIABLE out_live RESULT_VARIABLE rc_live)
execute_process(COMMAND "${REF}" ${run_args} OUTPUT_VARIABLE out_ref RESULT_VARIABLE rc_ref)
string(REGEX MATCH "${KEY} [^\n]*" h_live "${out_live}")
string(REGEX MATCH "${KEY} [^\n]*" h_ref "${out_ref}")
string(REGEX MATCH "BLK [^\n]*" blk_live "${out_live}")
message("live (${ENV}): ${h_live} (rc ${rc_live})")
message("      ${blk_live}")
message("ref:  ${h_ref} (rc ${rc_ref})")
if(h_live STREQUAL "" OR NOT h_live STREQUAL h_ref OR NOT rc_live EQUAL rc_ref)
  message(FATAL_ERROR "live and reference interpreters differ")
endif()
if(NEED_BLOCKS)
  string(REGEX MATCH " pairs ([0-9]+)" m "${h_live}")
  set(np "${CMAKE_MATCH_1}")
  string(REGEX MATCH "pairs (translated )?([0-9]+)" m2 "${blk_live}")
  set(nb "${CMAKE_MATCH_2}")
  if(np AND NOT np STREQUAL "0" AND (nb STREQUAL "" OR nb STREQUAL "0"))
    message(FATAL_ERROR "the block translator did not run (${blk_live})")
  endif()
endif()

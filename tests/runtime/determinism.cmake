# SPDX-License-Identifier: CC0-1.0
# Runs rg-runtime-demo --headless twice in separate processes and compares
# the run_hash lines (and the final screenshots).  -DDEMO -DFIELDS -DSCRIPT
# -DOTHER (script of the second run) -DOUT.
file(REMOVE_RECURSE ${OUT})
file(MAKE_DIRECTORY ${OUT}/a ${OUT}/b)
foreach(run a b)
  if(run STREQUAL "a")
    set(s ${SCRIPT})
  else()
    set(s ${OTHER})
  endif()
  execute_process(
    COMMAND ${DEMO} --headless --fields ${FIELDS} --input ${s} --hash-every 60
            --fixture ${OUT}/${run}/disc --saves ${OUT}/${run}/saves --screenshot ${OUT}/${run}/last.png
    WORKING_DIRECTORY ${OUT}/${run}
    RESULT_VARIABLE rc OUTPUT_VARIABLE out ERROR_VARIABLE err)
  message("${run}: ${out}")
  if(NOT rc EQUAL 0)
    message(FATAL_ERROR "run ${run} failed (${rc}): ${err}")
  endif()
  string(REGEX MATCH "run_hash=[0-9a-f]+" h "${out}")
  if(NOT h)
    message(FATAL_ERROR "run ${run}: no run_hash")
  endif()
  set(hash_${run} ${h})
endforeach()
file(SHA256 ${OUT}/a/last.png png_a)
file(SHA256 ${OUT}/b/last.png png_b)
if(NOT hash_a STREQUAL hash_b)
  message(FATAL_ERROR "run hashes differ: ${hash_a} vs ${hash_b}")
endif()
if(NOT png_a STREQUAL png_b)
  message(FATAL_ERROR "final screenshots differ")
endif()
message("identical: ${hash_a}")

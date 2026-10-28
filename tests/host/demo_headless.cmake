# SPDX-License-Identifier: CC0-1.0
# rg-host-demo --headless: two runs with the same input script must give
# byte-identical screenshots (and the same printed frame hash); the PNG must
# decode at 640x448 with real content; a run with a different input script
# (control) must give a different screenshot, proving input reaches the frame.
#   -DDEMO=rg-host-demo -DTESTS=rg-host-tests -DINPUT=... -DOTHER=... -DOUT=dir -DFRAMES=40
file(MAKE_DIRECTORY "${OUT}")
foreach(run a b c)
  set(inp "${INPUT}")
  if(run STREQUAL "c")
    set(inp "${OTHER}")
  endif()
  file(REMOVE "${OUT}/${run}.png")
  execute_process(
    COMMAND "${DEMO}" --headless --frames ${FRAMES} --input "${inp}" --screenshot "${OUT}/${run}.png"
    RESULT_VARIABLE rc OUTPUT_VARIABLE out_${run} ERROR_VARIABLE err)
  if(NOT rc EQUAL 0)
    message(FATAL_ERROR "demo run ${run} failed (${rc}): ${out_${run}} ${err}")
  endif()
  string(REGEX MATCH "hash=[0-9a-f]+" hash_${run} "${out_${run}}")
  message(STATUS "run ${run}: ${out_${run}}")
endforeach()
execute_process(COMMAND "${TESTS}" pngcheck "${OUT}/a.png" 640 448 RESULT_VARIABLE rc)
if(NOT rc EQUAL 0)
  message(FATAL_ERROR "screenshot a.png failed pngcheck")
endif()
file(SHA256 "${OUT}/a.png" ha)
file(SHA256 "${OUT}/b.png" hb)
file(SHA256 "${OUT}/c.png" hc)
if(NOT ha STREQUAL hb OR NOT hash_a STREQUAL hash_b OR hash_a STREQUAL "")
  message(FATAL_ERROR "screenshots differ between identical runs: ${ha} vs ${hb} (${hash_a} / ${hash_b})")
endif()
if(ha STREQUAL hc)
  message(FATAL_ERROR "control: a different input script gave the same screenshot")
endif()
message(STATUS "stable screenshot ${ha} (${hash_a}); control differs (${hc})")

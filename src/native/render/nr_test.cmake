# SPDX-License-Identifier: CC0-1.0
# ctest driver for the native-renderer checks (src/native/render/CMakeLists.txt):
#   -DCAP=capture [-DVT=rg-nr-vutrace -DCORPUS=file] -DEXE=checker [-DARGS=...]
# With VT: build the corpus from the capture first, then run EXE on the corpus;
# without: run EXE on the capture.  A missing capture prints SKIP.
if(NOT EXISTS "${CAP}")
  message("SKIP: no capture ${CAP}")
  return()
endif()
if(VT)
  execute_process(COMMAND "${VT}" "${CAP}" --corpus "${CORPUS}" RESULT_VARIABLE rc)
  if(rc)
    message(FATAL_ERROR "rg-nr-vutrace failed (${rc})")
  endif()
  set(IN "${CORPUS}")
else()
  set(IN "${CAP}")
endif()
execute_process(COMMAND "${EXE}" "${IN}" ${ARGS} RESULT_VARIABLE rc OUTPUT_VARIABLE out)
message("${out}")
if(rc)
  message(FATAL_ERROR "check failed (${rc})")
endif()

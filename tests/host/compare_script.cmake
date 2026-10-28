# SPDX-License-Identifier: CC0-1.0
# The C script compiler must produce exactly input.py's table blob.
#   -DPY=python -DINPUT_PY_DIR=tools/trace -DTESTS=rg-host-tests -DSCRIPT=... -DOUT=dir
file(MAKE_DIRECTORY "${OUT}")
get_filename_component(stem "${SCRIPT}" NAME_WE)
set(py_blob "${OUT}/${stem}.py.bin")
set(c_blob "${OUT}/${stem}.c.bin")
file(REMOVE "${py_blob}" "${c_blob}")
execute_process(
  COMMAND "${PY}" -I "${CMAKE_CURRENT_LIST_DIR}/input_py_blob.py" "${INPUT_PY_DIR}" "${SCRIPT}" "${py_blob}"
  RESULT_VARIABLE r1)
if(NOT r1 EQUAL 0)
  message(FATAL_ERROR "input.py failed on ${SCRIPT}: ${r1}")
endif()
execute_process(COMMAND "${TESTS}" script_dump "${SCRIPT}" "${c_blob}" RESULT_VARIABLE r2)
if(NOT r2 EQUAL 0)
  message(FATAL_ERROR "rg-host-tests script_dump failed on ${SCRIPT}: ${r2}")
endif()
file(SHA256 "${py_blob}" h1)
file(SHA256 "${c_blob}" h2)
if(NOT h1 STREQUAL h2)
  message(FATAL_ERROR "table mismatch for ${SCRIPT}: input.py ${h1} vs C ${h2}")
endif()
message(STATUS "${SCRIPT}: identical tables (${h1})")

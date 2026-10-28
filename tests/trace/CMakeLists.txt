# SPDX-License-Identifier: CC0-1.0
# State-trace recorder tests (docs/TRACE-PORT.md "Tests").  ctest -L trace
set(_tmp ${CMAKE_CURRENT_BINARY_DIR}/tmp)
file(MAKE_DIRECTORY ${_tmp})
set(_d ${CMAKE_CURRENT_SOURCE_DIR}/data)

# The fixture symbol table comes from the real generator, compiled and linked
# against stand-in D_ definitions (C linkage, as the game's).
set(_gen ${CMAKE_CURRENT_BINARY_DIR}/gen)
set(_fixture_srcs symtab_fixture_defs.c)
if(RG_PYTHON)
  add_custom_command(
    OUTPUT ${_gen}/symtab_fixture_gen.c
    COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/trace/gen_port_symtab.py
            --regions ${_d}/symtab_regions.cfg --symbols ${_d}/symtab_fixture.txt
            --func rg_trace_register_symtab_fixture --out ${_gen}/symtab_fixture_gen.c
    DEPENDS ${CMAKE_SOURCE_DIR}/tools/trace/gen_port_symtab.py ${CMAKE_SOURCE_DIR}/tools/trace/trace.py
            ${_d}/symtab_regions.cfg ${_d}/symtab_fixture.txt
    VERBATIM)
  list(APPEND _fixture_srcs ${_gen}/symtab_fixture_gen.c)
else()
  message(WARNING "python not found: trace symtab fixture and cross-checks skipped")
  file(WRITE ${_gen}/symtab_fixture_stub.c "int rg_trace_register_symtab_fixture(void) { return -1; }\n")
  list(APPEND _fixture_srcs ${_gen}/symtab_fixture_stub.c)
endif()

add_executable(rg-trace-tests trace_tests.c ${_fixture_srcs})
target_link_libraries(rg-trace-tests PRIVATE rg_trace_core rg_flags)
if(WIN32)
  target_compile_definitions(rg-trace-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

foreach(t deref parse)
  file(MAKE_DIRECTORY ${_tmp}/${t})
  add_test(NAME trace.${t} COMMAND rg-trace-tests ${t} ${_tmp}/${t})
  set_tests_properties(trace.${t} PROPERTIES TIMEOUT 120 LABELS trace)
endforeach()

if(RG_PYTHON)
  add_test(NAME trace.symtab_gen COMMAND rg-trace-tests symtab)
  set_tests_properties(trace.symtab_gen PROPERTIES TIMEOUT 60 LABELS trace)

  set(_x ${RG_PYTHON} -I ${CMAKE_CURRENT_SOURCE_DIR}/xcheck.py)
  # the hash == trace.py's h() (hashlib) on fixed buffers
  add_test(NAME trace.hash_xcheck COMMAND ${_x} hash --exe $<TARGET_FILE:rg-trace-tests>)
  # region semantics + TSV format == trace.py over the same EE image
  add_test(NAME trace.image_xcheck COMMAND ${_x} image --exe $<TARGET_FILE:rg-trace-tests>
           --regions ${_d}/xcheck_regions.cfg --tmp ${_tmp}/image)
  # controls (WILL_FAIL): a truncated 64-byte digest; one perturbed expected row
  add_test(NAME trace.hash_xcheck_control COMMAND ${_x} hash --exe $<TARGET_FILE:rg-trace-tests> --control)
  add_test(NAME trace.image_xcheck_control COMMAND ${_x} image --exe $<TARGET_FILE:rg-trace-tests>
           --regions ${_d}/xcheck_regions.cfg --tmp ${_tmp}/image_control --control)
  set_tests_properties(trace.hash_xcheck trace.image_xcheck PROPERTIES TIMEOUT 300 LABELS trace)
  set_tests_properties(trace.hash_xcheck_control trace.image_xcheck_control
                       PROPERTIES TIMEOUT 300 LABELS trace WILL_FAIL TRUE)

  # Python tools: port_trace.py config, gen_port_symtab.py, port_regions.cfg
  add_test(NAME trace.tools_unit COMMAND ${RG_PYTHON} -I ${CMAKE_CURRENT_SOURCE_DIR}/test_port_tools.py)
  set_tests_properties(trace.tools_unit PROPERTIES TIMEOUT 300 LABELS trace)

  # timing record (docs/TIMING-LOCKSTEP.md): the site table matches probe.py,
  # the runtime's records over synthetic memory, and an rg-runtime-demo run
  add_test(NAME trace.timing_sites_sync COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/trace/gen_timing_sites.py
           --check --tsv ${CMAKE_SOURCE_DIR}/tools/trace/timing_sites.tsv)
  set_tests_properties(trace.timing_sites_sync PROPERTIES TIMEOUT 120 LABELS trace)
  if(TARGET rg_trace)
    add_executable(rg-timing-tests timing_tests.c)
    target_link_libraries(rg-timing-tests PRIVATE rg_trace rg_flags)
    if(WIN32)
      target_compile_definitions(rg-timing-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()
    set(_tc ${RG_PYTHON} -I ${CMAKE_CURRENT_SOURCE_DIR}/timing_check.py)
    add_test(NAME trace.timing_unit COMMAND ${_tc} unit --exe $<TARGET_FILE:rg-timing-tests>
             --tmp ${_tmp}/timing_unit)
    add_test(NAME trace.timing_unit_control COMMAND ${_tc} unit --control --exe $<TARGET_FILE:rg-timing-tests>
             --tmp ${_tmp}/timing_unit_control)
    set_tests_properties(trace.timing_unit PROPERTIES TIMEOUT 300 LABELS trace)
    set_tests_properties(trace.timing_unit_control PROPERTIES TIMEOUT 300 LABELS trace WILL_FAIL TRUE)
    if(TARGET rg-runtime-demo)
      add_test(NAME trace.timing_demo COMMAND ${_tc} demo --exe $<TARGET_FILE:rg-runtime-demo>
               --tmp ${_tmp}/timing_demo)
      # the demo drives the bring-up sound / SIF path (as tests/runtime): pin the IOP HLE
      # (docs/NATIVE-IOP.md; failed since RG_IOP=native became the default)
      set_tests_properties(trace.timing_demo PROPERTIES TIMEOUT 600 LABELS trace ENVIRONMENT "RG_IOP=hle")
    endif()
  endif()

  # end to end on rg-runtime-demo (needs the runtime: RG_HOST)
  if(TARGET rg-runtime-demo AND TARGET rg_trace_demo)
    set(_e ${RG_PYTHON} -I ${CMAKE_CURRENT_SOURCE_DIR}/demo_e2e.py)
    add_test(NAME trace.demo_pipeline COMMAND ${_e} pipeline --exe $<TARGET_FILE:rg-runtime-demo>
             --tmp ${_tmp}/demo_pipeline)
    add_test(NAME trace.demo_fault COMMAND ${_e} fault --exe $<TARGET_FILE:rg-runtime-demo>
             --tmp ${_tmp}/demo_fault)
    add_test(NAME trace.demo_fault_control COMMAND ${_e} control --exe $<TARGET_FILE:rg-runtime-demo>
             --tmp ${_tmp}/demo_control)
    set_tests_properties(trace.demo_pipeline trace.demo_fault PROPERTIES TIMEOUT 600 LABELS trace)
    set_tests_properties(trace.demo_fault_control PROPERTIES TIMEOUT 600 LABELS trace WILL_FAIL TRUE)
  endif()
endif()

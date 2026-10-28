# SPDX-License-Identifier: CC0-1.0
# CDVD model tests (docs/CDVD.md).
add_executable(cdvd-tests cdvd_tests.c)
target_link_libraries(cdvd-tests PRIVATE rg_sce_cdvd rg_flags)
add_test(NAME cdvd-tests COMMAND cdvd-tests ${CMAKE_CURRENT_BINARY_DIR}/cdvd_fixture)

# Needs RG_DATA=<extracted data folder> (and optionally RG_ISO=<disc image>); skipped
# otherwise.
add_executable(cdvd-realdata-tests cdvd_realdata_tests.c)
target_link_libraries(cdvd-realdata-tests PRIVATE rg_sce_cdvd rg_flags)
if(WIN32)
  target_compile_definitions(cdvd-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_definitions(cdvd-realdata-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
add_test(NAME cdvd-realdata-tests COMMAND cdvd-realdata-tests)
set_tests_properties(cdvd-realdata-tests PROPERTIES SKIP_RETURN_CODE 77)
set_tests_properties(cdvd-tests cdvd-realdata-tests PROPERTIES LABELS cdvd)

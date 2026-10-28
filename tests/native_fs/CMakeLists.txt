# SPDX-License-Identifier: CC0-1.0
# Native file service tests (docs/NATIVE-FS.md).
add_executable(native-fs-tests native_fs_tests.c)
target_link_libraries(native-fs-tests PRIVATE rg_native_fs rg_native_fs_oracle rg_flags)
if(WIN32)
  target_compile_definitions(native-fs-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
add_test(NAME native-fs-tests COMMAND native-fs-tests ${CMAKE_CURRENT_BINARY_DIR}/native_fs_fixture)
# every disc file read natively and compared with the CDVD sector model; needs RG_DATA
add_test(NAME native-fs-realdata-tests COMMAND native-fs-tests --realdata)
set_tests_properties(native-fs-realdata-tests PROPERTIES SKIP_RETURN_CODE 77)
set_tests_properties(native-fs-tests native-fs-realdata-tests PROPERTIES LABELS native_fs)

# SPDX-License-Identifier: CC0-1.0
# devirt stage tests (docs/DEVIRT.md): ctest -L devirt
#
#   devirt.layout              stage output for fixtures/synthetic.cpp: layout static_asserts
#                              + dispatch through fake vtables
#   devirt.layout_control      the same with every vtable one slot off: must FAIL
#   devirt.stage_<fixture>     the stage on real snapshot files is idempotent; the outputs
#                              are compiled (rg_devirt_fixtures, game flags)
#   devirt.verify              retail cross-check over the built game objects (skips
#                              unless rg_game_objs was built)
#   devirt.verify_control_slot / _voff   the cross-check with the port's slot offsets /
#                              vptr offsets perturbed: every unit must be caught
set(RG_DEVIRT_OUT ${CMAKE_BINARY_DIR}/devirt)
set(RG_DEVIRT_STAGE ${CMAKE_SOURCE_DIR}/tools/stages/devirt.py)
set(RG_DEVIRT_REAL MotionEventBlockAppendEvent_1b2370 HandleRegistryStepAll_314e10
    CharaDeserialize_3a9c50 CameraResetLevelViewMaybe_30a150 CharaLearnAbility_3ad460)

set(_outs)
foreach(f synthetic ${RG_DEVIRT_REAL})
  add_custom_command(
    OUTPUT ${RG_DEVIRT_OUT}/${f}.devirt.cpp
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RG_DEVIRT_OUT}
    COMMAND ${RG_PYTHON} ${RG_DEVIRT_STAGE}
            ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/${f}.cpp ${RG_DEVIRT_OUT}/${f}.devirt.cpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/${f}.cpp ${RG_DEVIRT_STAGE}
            ${CMAKE_SOURCE_DIR}/tools/portxform.py
    COMMENT "devirt: tests/devirt/fixtures/${f}.cpp")
  list(APPEND _outs ${RG_DEVIRT_OUT}/${f}.devirt.cpp)
endforeach()

add_executable(rg-devirt-layout test_layout.cpp ${RG_DEVIRT_OUT}/synthetic.devirt.cpp)
set_source_files_properties(${RG_DEVIRT_OUT}/synthetic.devirt.cpp PROPERTIES HEADER_FILE_ONLY TRUE)
target_include_directories(rg-devirt-layout PRIVATE ${RG_DEVIRT_OUT} ${CMAKE_SOURCE_DIR}/include)
target_compile_options(rg-devirt-layout PRIVATE -include port/vcall.h -Wno-invalid-offsetof)
target_link_libraries(rg-devirt-layout PRIVATE rg_flags)
add_test(NAME devirt.layout COMMAND rg-devirt-layout)
add_test(NAME devirt.layout_control COMMAND rg-devirt-layout control)
set_tests_properties(devirt.layout PROPERTIES LABELS devirt TIMEOUT 60)
set_tests_properties(devirt.layout_control PROPERTIES LABELS devirt TIMEOUT 60 WILL_FAIL TRUE)

# real snapshot files, transformed by the stage, compiled with the game flags
if(EXISTS ${CMAKE_SOURCE_DIR}/game/include/types.h)
  set(_real)
  foreach(f ${RG_DEVIRT_REAL})
    list(APPEND _real ${RG_DEVIRT_OUT}/${f}.devirt.cpp)
  endforeach()
  add_library(rg_devirt_fixtures OBJECT ${_real})
  target_include_directories(rg_devirt_fixtures PRIVATE ${CMAKE_SOURCE_DIR}/include
                             ${CMAKE_SOURCE_DIR}/game/include)
  target_compile_options(rg_devirt_fixtures PRIVATE -w -include port/prelude.h)
  target_link_libraries(rg_devirt_fixtures PRIVATE rg_flags)
  add_dependencies(rg-devirt-layout rg_devirt_fixtures)
endif()
foreach(f ${RG_DEVIRT_REAL})
  add_test(NAME devirt.stage_${f}
           COMMAND ${RG_PYTHON} ${RG_DEVIRT_STAGE} ${CMAKE_CURRENT_SOURCE_DIR}/fixtures/${f}.cpp
                   ${RG_DEVIRT_OUT}/${f}.check.cpp)
  set_tests_properties(devirt.stage_${f} PROPERTIES LABELS devirt TIMEOUT 60)
endforeach()

# retail cross-check (tools/devirt_verify.py); exit 77 = game objects not built
set(_v ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/devirt_verify.py --objdir ${CMAKE_BINARY_DIR})
# game objects above -O1 (cmake/game.cmake RG_GAME_OPT) inline and unroll: extra call
# sites (`port-more`) are tolerated there; the controls stay strict (docs/UB-AUDIT.md)
set(_vtol)
if(RG_GAME_OPT AND NOT RG_GAME_OPT STREQUAL "-O1")
  set(_vtol --tolerate port-more)
endif()
add_test(NAME devirt.verify COMMAND ${_v} ${_vtol} --out ${RG_DEVIRT_OUT}/devirt_verify.tsv)
add_test(NAME devirt.verify_control_slot
         COMMAND ${_v} --fault slot+1 --out ${RG_DEVIRT_OUT}/devirt_verify_fault_slot.tsv)
add_test(NAME devirt.verify_control_voff
         COMMAND ${_v} --fault voff+4 --out ${RG_DEVIRT_OUT}/devirt_verify_fault_voff.tsv)
set_tests_properties(devirt.verify devirt.verify_control_slot devirt.verify_control_voff
                     PROPERTIES LABELS devirt TIMEOUT 900 SKIP_RETURN_CODE 77)

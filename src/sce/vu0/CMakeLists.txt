# SPDX-License-Identifier: CC0-1.0
# libvu0 functions the game calls on the VU0 model (the oracle), plus the native
# microprogram and the named contexts from src/native/vu0 (docs/BINDINGS.md,
# docs/NATIVE-CPU.md).  rg_sce_vu0 follows RG_VU0_MODE (top-level
# CMakeLists.txt); rg_sce_vu0_oracle is always the bring-up model (global
# register file, VU float rules) for the bindings tests, which check the
# model's register side effects across files.
foreach(t rg_sce_vu0 rg_sce_vu0_oracle)
  add_library(${t} STATIC
    sce_vu0.h
    libvu0.c
    ${CMAKE_SOURCE_DIR}/src/native/vu0/vu0_srt.c
    ${CMAKE_SOURCE_DIR}/src/native/vu0/vu0_ctx.c)
  target_include_directories(${t} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${t} PRIVATE rg_flags)
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()
target_compile_definitions(rg_sce_vu0 PRIVATE ${RG_VU0_DEFS})
target_compile_definitions(rg_sce_vu0_oracle PRIVATE RG_VU0_ORACLE=1)
target_link_libraries(rg_sce_vu0 PUBLIC rg_vu0)
target_link_libraries(rg_sce_vu0_oracle PUBLIC rg_vu0_oracle)

# vu0native: the native microprogram against the VU interpreter running the
# retail program (bit-exact with VU floats), the per-file register files, the
# native float rules.  Needs the retail ELF for the interpreter half (77 =
# skipped without it).
add_executable(rg-vu0native-tests vu0native_tests.c vu0native_ref.c)
target_include_directories(rg-vu0native-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg-vu0native-tests PRIVATE rg_sce_vu0_oracle rg_vu0_oracle rg_ps2_vif rg_vu_retail
  rg_ps2_vu rg_flags)
# the same sources under other modes, one object library per flavour
set(_vn_flavours
  "vu0native_local.c|RG_VU0_LOCAL=1,VNL_SIDE=a"
  "vu0native_local.c|RG_VU0_LOCAL=1,VNL_SIDE=b"
  "vu0native_local.c|RG_VU0_LOCAL=1,VNL_SIDE=ctx_a,VNL_CTX=1"
  "vu0native_local.c|RG_VU0_LOCAL=1,VNL_SIDE=ctx_b,VNL_CTX=1"
  "vu0native_ieee.c|RG_VU0_LOCAL=1,RG_VU0_IEEE=1"
  "${CMAKE_SOURCE_DIR}/src/native/vu0/vu0_srt.c|RG_VU0_LOCAL=1,RG_VU0_IEEE=1,rg_vu0_srt=rg_vu0_srt_ieee")
set(_vn_i 0)
foreach(f IN LISTS _vn_flavours)
  string(REPLACE "|" ";" _parts "${f}")
  list(GET _parts 0 _src)
  list(GET _parts 1 _defs)
  string(REPLACE "," ";" _defs "${_defs}")
  add_library(rg_vu0native_f${_vn_i} OBJECT ${_src})
  target_include_directories(rg_vu0native_f${_vn_i} PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_compile_definitions(rg_vu0native_f${_vn_i} PRIVATE ${_defs})
  target_link_libraries(rg_vu0native_f${_vn_i} PRIVATE rg_flags)
  target_link_libraries(rg-vu0native-tests PRIVATE rg_vu0native_f${_vn_i})
  math(EXPR _vn_i "${_vn_i} + 1")
endforeach()
if(WIN32)
  target_compile_definitions(rg-vu0native-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
add_test(NAME vu0native COMMAND rg-vu0native-tests)
set_tests_properties(vu0native PROPERTIES LABELS "port;vu0native" TIMEOUT 300 SKIP_RETURN_CODE 77)
add_test(NAME vu0native.control COMMAND rg-vu0native-tests --wrong)
set_tests_properties(vu0native.control PROPERTIES LABELS "port;vu0native" TIMEOUT 300
  WILL_FAIL TRUE)


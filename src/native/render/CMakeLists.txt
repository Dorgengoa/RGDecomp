# SPDX-License-Identifier: CC0-1.0
# Native renderer, scene side (docs/NATIVE-RENDER.md): the model program's
# semantics (nr_vu1), the mesh cache, draw records and the runtime wiring.
# The device side lives in src/gpu (gpu_nr_draw, nr_draw.hlsl).
add_library(rg_native_render STATIC nr.h nr_vu1.h nr_vu1.c nr_vu1sh.h nr_vu1sh.c nr_vu1ln.h nr_vu1ln.c nr_mesh.h nr_mesh.c nr_const.h nr_const.c nr_comp.h nr_comp.c nr_im.h nr_im.c nr_sfx.h nr_sfx.c nr_scene.c nr_hw.c nr_fx.c nr_vux.c nr_lnrm.h nr_lnrm.c
  nr_gs.h nr_gs.c nr_q.c nr_gsmem.h nr_gsmem.c nr_interp.h nr_interp.c nr_mem.h nr_mem.c)
target_include_directories(rg_native_render PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_render PUBLIC rg_ps2_gs rg_ps2_vif rg_ps2_vu PRIVATE rg_flags)
if(TARGET rg_gpu)
  target_link_libraries(rg_native_render PUBLIC rg_gpu)
  target_compile_definitions(rg_native_render PRIVATE RG_HAVE_GPU=1)
  # the native-only device (docs/NATIVE-RENDER.md "Checkpoint 10"): these compile to nothing
  # unless RG_NATIVE_ONLY (cmake/native_only.cmake's clone, which drops rg_gpu and rg_ps2_gs)
  get_property(_rg_gpu_gen GLOBAL PROPERTY RG_GPU_GEN_DIR)
  target_sources(rg_native_render PRIVATE nr_dev.cpp nr_d3d11.cpp nr_gfx.c nr_iprec.cpp nr_texrep.cpp)
  target_include_directories(rg_native_render PRIVATE ${_rg_gpu_gen} ${PROJECT_SOURCE_DIR}/src/gpu)
  target_link_libraries(rg_native_render PUBLIC d3d11 dxgi rg_settings)
  target_compile_definitions(rg_native_render PRIVATE _CRT_SECURE_NO_WARNINGS)
  add_dependencies(rg_native_render rg_gpu_shaders)
  set_source_files_properties(nr_dev.cpp nr_d3d11.cpp nr_gfx.c nr_iprec.cpp nr_texrep.cpp PROPERTIES COMPILE_OPTIONS -O2)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set_source_files_properties(nr_dev.cpp nr_d3d11.cpp PROPERTIES COMPILE_OPTIONS "-O2;-Wno-unused-parameter")
  endif()
  include(${CMAKE_CURRENT_SOURCE_DIR}/nr_vulkan.cmake)   # the Vulkan backend (docs/NATIVE-VULKAN.md)
elseif(RG_NATIVE_ONLY AND NOT WIN32)
  # Linux (docs/LINUX.md "Windowed build"): the native-only device on the Vulkan backend, no
  # rg_gpu (src/gpu is the D3D11 GS renderer, Windows only).  Default ON for a windowed build,
  # OFF for a console one (SDL_UNIX_CONSOLE_BUILD: the headless renderer, software GS).
  if(SDL_UNIX_CONSOLE_BUILD)
    set(_rg_nd_default OFF)
  else()
    set(_rg_nd_default ON)
  endif()
  option(RG_LINUX_NATIVE_DEVICE "Linux rg-game: native device on the Vulkan backend (else the headless renderer)" ${_rg_nd_default})
  if(RG_LINUX_NATIVE_DEVICE)
    include(${CMAKE_CURRENT_SOURCE_DIR}/nr_vulkan.cmake)
    get_target_property(_rg_nr_defs rg_native_render COMPILE_DEFINITIONS)
    if("RG_HAVE_VULKAN=1" IN_LIST _rg_nr_defs)
      target_sources(rg_native_render PRIVATE nr_dev.cpp nr_gfx.c nr_iprec.cpp nr_texrep.cpp)
      target_include_directories(rg_native_render PUBLIC ${PROJECT_SOURCE_DIR}/src/gpu)   # gpu.h for rg_runtime too
      target_link_libraries(rg_native_render PUBLIC rg_settings)
      set_source_files_properties(nr_gfx.c nr_iprec.cpp nr_texrep.cpp PROPERTIES COMPILE_OPTIONS -O2)
      set_source_files_properties(nr_dev.cpp PROPERTIES COMPILE_OPTIONS "-O2;-Wno-unused-parameter")
      # RG_HAVE_GPU only in the native-only clones (cmake/native_only.cmake RG_NONLY_DEFINITIONS):
      # the default-config libraries have no gpu_core.cpp here, tests linking them must not see it
      set_property(TARGET rg_native_render PROPERTY RG_NONLY_DEFINITIONS RG_HAVE_GPU=1)
      set_property(GLOBAL PROPERTY RG_NATIVE_DEVICE ON)
      message(STATUS "src/native/render: Linux native device on the Vulkan backend")
    else()
      message(WARNING "src/native/render: RG_LINUX_NATIVE_DEVICE needs the Vulkan backend (a SPIR-V dxc); "
                      "rg-game keeps the headless renderer")
    endif()
  endif()
endif()
# original port code (hot per-frame paths): -O2 like src/gpu (docs/PERF-3D.md fix 4)
set_source_files_properties(nr_vu1.c nr_vu1sh.c nr_vu1ln.c nr_mesh.c nr_const.c nr_comp.c nr_im.c nr_sfx.c nr_scene.c nr_fx.c nr_vux.c nr_lnrm.c nr_gs.c nr_q.c nr_gsmem.c nr_interp.c nr_mem.c PROPERTIES COMPILE_OPTIONS -O2)
if(WIN32)
  target_compile_definitions(rg_native_render PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_render PRIVATE -Wall -Wextra)
endif()

# ---- verification tools and tests (docs/NATIVE-RENDER.md "Verification") ----
# rg-nr-vutrace (VU1 census / corpus), rg-nr-nmcheck (program semantics vs the
# VU1 interpreter), rg-nr-meshcheck (mesh decoder vs the VIF), rg-nr-meshdump.
# The retail captures live in out/captures (game data, not committed): tests
# without them report SKIP.
add_executable(rg-nr-vutrace ${PROJECT_SOURCE_DIR}/tools/native/render_vutrace.c)
target_link_libraries(rg-nr-vutrace PRIVATE rg_ps2_vif rg_ps2_vu rg_flags)
add_executable(rg-nr-nmcheck ${PROJECT_SOURCE_DIR}/tools/native/render_nmcheck.c nr_vu1.c nr_vu1sh.c nr_vu1ln.c)
target_include_directories(rg-nr-nmcheck PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg-nr-nmcheck PRIVATE rg_flags)
add_executable(rg-nr-meshcheck ${PROJECT_SOURCE_DIR}/tools/native/render_meshcheck.c nr_mesh.c nr_mem.c)
target_include_directories(rg-nr-meshcheck PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg-nr-meshcheck PRIVATE rg_ps2_vif rg_ps2_vu rg_flags)
add_executable(rg-nr-vudis ${PROJECT_SOURCE_DIR}/tools/native/render_vudis.c)
target_link_libraries(rg-nr-vudis PRIVATE rg_ps2_vu rg_flags)
add_executable(rg-nr-meshdump ${PROJECT_SOURCE_DIR}/tools/native/render_meshdump.c nr_mesh.c nr_mem.c)
target_include_directories(rg-nr-meshdump PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg-nr-meshdump PRIVATE rg_flags)
foreach(t rg-nr-vutrace rg-nr-nmcheck rg-nr-meshcheck rg-nr-meshdump rg-nr-vudis)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
endforeach()

# HD texture replacement pieces (docs/TEXTURES.md "Checks"): names, lazy CPU copy vs an eager one,
# hashes, DDS block decoders; --control must fail
if(RG_NATIVE_ONLY)
  add_executable(rg-texrep-test ${PROJECT_SOURCE_DIR}/tools/hdtex/texrep_test.cpp nr_gsmem.c)
  target_include_directories(rg-texrep-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src/gpu)
  target_link_libraries(rg-texrep-test PRIVATE rg_ps2_gs rg_flags)
  if(WIN32)
    target_compile_definitions(rg-texrep-test PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  add_test(NAME native.texrep COMMAND rg-texrep-test)
  add_test(NAME native.texrep_control COMMAND rg-texrep-test --control)
  set_tests_properties(native.texrep native.texrep_control PROPERTIES LABELS native)
  set_tests_properties(native.texrep_control PROPERTIES WILL_FAIL TRUE)
endif()

set(_nr_caps "${PROJECT_SOURCE_DIR}/out/captures")
foreach(f 09002 24804)
  set(cap ${_nr_caps}/C_v${f}.vifcap)
  add_test(NAME native.meshcheck.v${f} COMMAND ${CMAKE_COMMAND} -DCAP=${cap}
           -DEXE=$<TARGET_FILE:rg-nr-meshcheck> -P ${CMAKE_CURRENT_SOURCE_DIR}/nr_test.cmake)
  add_test(NAME native.nmcheck.v${f} COMMAND ${CMAKE_COMMAND} -DCAP=${cap}
           -DVT=$<TARGET_FILE:rg-nr-vutrace> -DEXE=$<TARGET_FILE:rg-nr-nmcheck>
           -DCORPUS=${CMAKE_CURRENT_BINARY_DIR}/corp${f}.bin -P ${CMAKE_CURRENT_SOURCE_DIR}/nr_test.cmake)
  set_tests_properties(native.meshcheck.v${f} native.nmcheck.v${f} PROPERTIES
                       LABELS native SKIP_REGULAR_EXPRESSION "SKIP:")
endforeach()
# deliberate faults: must FAIL
foreach(c 1 2 3 4 5 6)
  add_test(NAME native.nmcheck_control${c} COMMAND ${CMAKE_COMMAND} -DCAP=${_nr_caps}/C_v24804.vifcap
           -DVT=$<TARGET_FILE:rg-nr-vutrace> -DEXE=$<TARGET_FILE:rg-nr-nmcheck> -DARGS=--control\;${c}
           -DCORPUS=${CMAKE_CURRENT_BINARY_DIR}/corp24804c${c}.bin -P ${CMAKE_CURRENT_SOURCE_DIR}/nr_test.cmake)
  set_tests_properties(native.nmcheck_control${c} PROPERTIES LABELS native WILL_FAIL TRUE)
endforeach()
add_test(NAME native.meshcheck_control COMMAND ${CMAKE_COMMAND} -DCAP=${_nr_caps}/C_v09002.vifcap
         -DEXE=$<TARGET_FILE:rg-nr-meshcheck> -DARGS=--control -P ${CMAKE_CURRENT_SOURCE_DIR}/nr_test.cmake)
set_tests_properties(native.meshcheck_control PROPERTIES LABELS native WILL_FAIL TRUE)

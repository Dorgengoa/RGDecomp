# SPDX-License-Identifier: CC0-1.0
# Hardware GS renderer (docs/GPU.md): Direct3D 11 backend, Windows only.
# Shaders are compiled at build time by the Windows SDK's fxc into headers.
if(NOT WIN32)
  message(STATUS "src/gpu: Direct3D 11 backend is Windows-only; skipped")
  return()
endif()

# fxc from the Windows SDK (vcvars puts WindowsSdkVerBinPath in the env;
# fall back to scanning the usual roots).
set(_rg_fxc_hints)
if(DEFINED ENV{WindowsSdkVerBinPath})
  list(APPEND _rg_fxc_hints "$ENV{WindowsSdkVerBinPath}/x64" "$ENV{WindowsSdkVerBinPath}/x86")
endif()
if(DEFINED ENV{WindowsSdkDir})
  file(GLOB _rg_sdk_bins "$ENV{WindowsSdkDir}/bin/10.*")
  foreach(b IN LISTS _rg_sdk_bins)
    list(APPEND _rg_fxc_hints "${b}/x64" "${b}/x86")
  endforeach()
endif()
find_program(RG_FXC NAMES fxc fxc.exe HINTS ${_rg_fxc_hints})
if(NOT RG_FXC)
  message(WARNING "src/gpu: fxc.exe (Windows SDK) not found; GPU renderer not built")
  return()
endif()
message(STATUS "src/gpu: fxc = ${RG_FXC}")

set(RG_GPU_SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(RG_GPU_GEN ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${RG_GPU_GEN})
set(RG_GPU_SHADER_HEADERS)
# entry  profile  source  extra-define
set(_rg_entries
  "VS_main|vs_5_0|gs_draw.hlsl"
  "PS_main|ps_5_0|gs_draw.hlsl"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1|PS_main_x"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_ROV=1|PS_main_rov"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ROV=1|PS_main_x_rov"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_ZROV=1|PS_main_z"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ZROV=1|PS_main_x_z"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_ROV=1 /DGS_ZROV=1|PS_main_rov_z"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ROV=1 /DGS_ZROV=1|PS_main_x_rov_z"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_NOTEX=1|PS_main_xn"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ROV=1 /DGS_NOTEX=1|PS_main_xn_rov"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ZROV=1 /DGS_NOTEX=1|PS_main_xn_z"
  "PS_main|ps_5_0|gs_draw.hlsl|/DGS_EXACT=1 /DGS_ROV=1 /DGS_ZROV=1 /DGS_NOTEX=1|PS_main_xn_rov_z"
  "CS_decode|cs_5_0|gs_draw.hlsl|/DGS_DECODE=1"
  "VS_quad|vs_5_0|gs_util.hlsl"
  "PS_load_color|ps_5_0|gs_util.hlsl"
  "PS_load_depth|ps_5_0|gs_util.hlsl"
  "PS_load_depth|ps_5_0|gs_util.hlsl|/DGS_DEPTH_RT=1|PS_load_depth_rt"
  "PS_copy_depth|ps_5_0|gs_util.hlsl"
  "PS_display|ps_5_0|gs_util.hlsl"
  "CS_wb_color|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_wb_depth|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_merge|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_clut|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_l2l_read|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_l2l_write|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "CS_xfer|cs_5_0|gs_util.hlsl|/DGS_MEM_RW_PASS=1"
  "PS_resample|ps_5_0|gs_post.hlsl"
  "PS_fxaa|ps_5_0|gs_post.hlsl"
  "PS_sharpen|ps_5_0|gs_post.hlsl"
  "PS_final|ps_5_0|gs_post.hlsl"
  "VS_nr|vs_5_0|nr_draw.hlsl"
  "VS_im|vs_5_0|nr_draw.hlsl"
  "PS_nr|ps_5_0|nr_draw.hlsl"
  "PS_nr|ps_5_0|nr_draw.hlsl|/DNR_ZROV=1|PS_nr_z"
  "PS_nr|ps_5_0|nr_draw.hlsl|/DNR_CROV=1|PS_nr_c"
  "PS_nr|ps_5_0|nr_draw.hlsl|/DNR_CROV=1 /DNR_ZROV=1|PS_nr_cz")
foreach(e IN LISTS _rg_entries)
  string(REPLACE "|" ";" _l "${e}")
  list(GET _l 0 _entry)
  list(GET _l 1 _prof)
  list(GET _l 2 _src)
  list(LENGTH _l _n)
  set(_def "")
  if(_n GREATER 3)
    list(GET _l 3 _def)
    separate_arguments(_def UNIX_COMMAND "${_def}")   # several /D flags
  endif()
  set(_name ${_entry})       # header / array name (a variant of an entry)
  if(_n GREATER 4)
    list(GET _l 4 _name)
  endif()
  set(_out ${RG_GPU_GEN}/${_name}.h)
  add_custom_command(
    OUTPUT ${_out}
    COMMAND ${RG_FXC} /nologo /O3 /Ges /T ${_prof} /E ${_entry} /Vn g_${_name}
            ${_def} /Fh ${_out} ${RG_GPU_SHADER_DIR}/${_src}
    DEPENDS ${RG_GPU_SHADER_DIR}/${_src} ${RG_GPU_SHADER_DIR}/gs_common.hlsli
    COMMENT "fxc ${_name} (${_prof})"
    VERBATIM)
  list(APPEND RG_GPU_SHADER_HEADERS ${_out})
endforeach()

# the shader headers as their own target: rg_gpu and the native-only device (rg_native_render's
# nr_dev.cpp / nr_d3d11.cpp, docs/NATIVE-RENDER.md "Checkpoint 10") both use them
add_custom_target(rg_gpu_shaders DEPENDS ${RG_GPU_SHADER_HEADERS})
set_property(GLOBAL PROPERTY RG_GPU_GEN_DIR ${RG_GPU_GEN})
# The D3D11 backend lives in src/native/render (nr_d3d11.cpp) since checkpoint 10: rg_gpu (the
# oracle twin's GS renderer) compiles it with RG_GPU_EXACT=1, the GS-exact batch path included.
set(RG_GPU_BACKEND_SRC ${PROJECT_SOURCE_DIR}/src/native/render/nr_d3d11.cpp)
add_library(rg_gpu STATIC
  gpu.h
  gpu_internal.h
  gpu_core.cpp
  ${RG_GPU_BACKEND_SRC}
  gpu_gfx.c
  ${RG_GPU_SHADER_HEADERS})
target_compile_definitions(rg_gpu PRIVATE RG_GPU_EXACT=1)
# Hot platform code (original port code, not the decompiled game): -O2.
# PLAN.md D2's -O1 is for the game sources until their UB audit; source
# options come after rg_flags' -O1 on the command line (docs/PERF-3D.md).
set_source_files_properties(gpu_core.cpp ${RG_GPU_BACKEND_SRC} gpu_gfx.c PROPERTIES COMPILE_OPTIONS -O2)
target_include_directories(rg_gpu PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rg_gpu PRIVATE ${RG_GPU_GEN})
target_link_libraries(rg_gpu PUBLIC rg_ps2_gs rg_flags d3d11 dxgi)
target_link_libraries(rg_gpu PRIVATE rg_settings)   # gpu_gfx.c reads graphics.*
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_gpu PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()
target_compile_definitions(rg_gpu PRIVATE _CRT_SECURE_NO_WARNINGS)
set(RG_GPU_AVAILABLE ON PARENT_SCOPE)

# rg-host-demo --gpu (src/host/demo/host_demo.c, RG_HAVE_GPU)
if(TARGET rg-host-demo)
  target_link_libraries(rg-host-demo PRIVATE rg_gpu)
  target_compile_definitions(rg-host-demo PRIVATE RG_HAVE_GPU=1)
endif()

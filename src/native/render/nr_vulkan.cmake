# SPDX-License-Identifier: CC0-1.0
# The Vulkan backend of the native device (docs/NATIVE-VULKAN.md): nr_vulkan.cpp + the vendored
# volk loader and Vulkan Memory Allocator (third_party/), the HLSL shaders of src/gpu/shaders
# compiled to SPIR-V by DXC (-spirv) into byte-array headers.  Included by
# src/native/render/CMakeLists.txt inside its native-device block; adds sources to
# rg_native_render and defines RG_HAVE_VULKAN=1 for it.  The exe loads the Vulkan loader at run
# time (volk), so it still starts without Vulkan; D3D11 stays the default backend
# (RG_GPU_API / display.backend select).
#   -DRG_GPU_VULKAN=OFF   leave the backend out
#   -DRG_DXC=<dxc>        a SPIR-V capable dxc (tools/native/fetch_dxc.py; the Windows SDK's dxc
#                         has no SPIR-V code generation)
option(RG_GPU_VULKAN "build the Vulkan backend of the native renderer (needs a SPIR-V dxc)" ON)
if(NOT RG_GPU_VULKAN)
  return()
endif()
set(_rg_dxc_hints "${PROJECT_SOURCE_DIR}/../tools/dxc/bin/x64")
if(DEFINED ENV{VULKAN_SDK})
  list(APPEND _rg_dxc_hints "$ENV{VULKAN_SDK}/Bin" "$ENV{VULKAN_SDK}/bin")
endif()
if(NOT RG_DXC)
  # a dxc that can emit SPIR-V: probe every candidate (the Windows SDK's one cannot)
  find_program(_rg_dxc_first NAMES dxc dxc.exe HINTS ${_rg_dxc_hints} NO_CACHE)
  foreach(c ${_rg_dxc_hints})
    foreach(n dxc dxc.exe)
      if(NOT RG_DXC AND EXISTS "${c}/${n}" AND NOT IS_DIRECTORY "${c}/${n}")
        set(RG_DXC "${c}/${n}")
      endif()
    endforeach()
  endforeach()
  if(NOT RG_DXC AND _rg_dxc_first)
    set(RG_DXC "${_rg_dxc_first}")
  endif()
  if(RG_DXC)
    execute_process(COMMAND "${RG_DXC}" -spirv -T vs_6_0 -E VS_quad -Fo "${CMAKE_CURRENT_BINARY_DIR}/dxc_probe.spv"
                            "${PROJECT_SOURCE_DIR}/src/gpu/shaders/gs_util.hlsl"
                    RESULT_VARIABLE _rg_dxc_rc OUTPUT_QUIET ERROR_QUIET)
    if(NOT _rg_dxc_rc EQUAL 0)
      message(WARNING "src/native/render: ${RG_DXC} cannot emit SPIR-V; Vulkan backend not built "
                      "(python tools/native/fetch_dxc.py, then -DRG_DXC=...)")
      set(RG_DXC "")
    endif()
  endif()
  set(RG_DXC "${RG_DXC}" CACHE FILEPATH "SPIR-V capable dxc for the Vulkan backend's shaders")
endif()
if(NOT RG_DXC)
  message(WARNING "src/native/render: no SPIR-V capable dxc; Vulkan backend not built "
                  "(python tools/native/fetch_dxc.py)")
  return()
endif()
message(STATUS "src/native/render: Vulkan backend, dxc = ${RG_DXC}")

set(_rg_vk_src ${PROJECT_SOURCE_DIR}/src/gpu/shaders)
set(_rg_vk_gen ${CMAKE_CURRENT_BINARY_DIR}/spv)
file(MAKE_DIRECTORY ${_rg_vk_gen})
# entry  stage  source  extra-defines  [name]   (the native device's shader set of nr_d3d11.cpp)
set(_rg_vk_entries
  "VS_quad|vs|gs_util.hlsl"
  "PS_load_color|ps|gs_util.hlsl"
  "PS_load_depth|ps|gs_util.hlsl"
  "PS_load_depth|ps|gs_util.hlsl|GS_DEPTH_RT=1|PS_load_depth_rt"
  "PS_copy_depth|ps|gs_util.hlsl"
  "PS_display|ps|gs_util.hlsl"
  "CS_wb_color|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_wb_depth|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_merge|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_clut|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_l2l_read|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_l2l_write|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_xfer|cs|gs_util.hlsl|GS_MEM_RW_PASS=1"
  "CS_decode|cs|gs_draw.hlsl|GS_DECODE=1"
  "PS_resample|ps|gs_post.hlsl"
  "PS_fxaa|ps|gs_post.hlsl"
  "PS_sharpen|ps|gs_post.hlsl"
  "PS_final|ps|gs_post.hlsl"
  "VS_nr|vs|nr_draw.hlsl"
  "VS_im|vs|nr_draw.hlsl"
  "PS_nr|ps|nr_draw.hlsl"
  "PS_nr|ps|nr_draw.hlsl|NR_ZROV=1|PS_nr_z"
  "PS_nr|ps|nr_draw.hlsl|NR_CROV=1|PS_nr_c"
  "PS_nr|ps|nr_draw.hlsl|NR_CROV=1 NR_ZROV=1|PS_nr_cz")
set(_rg_vk_headers)
foreach(e IN LISTS _rg_vk_entries)
  string(REPLACE "|" ";" _l "${e}")
  list(GET _l 0 _entry)
  list(GET _l 1 _stage)
  list(GET _l 2 _src)
  list(LENGTH _l _n)
  set(_defs)
  if(_n GREATER 3)
    list(GET _l 3 _d)
    separate_arguments(_d UNIX_COMMAND "${_d}")
    foreach(x ${_d})
      list(APPEND _defs "-D${x}")
    endforeach()
  endif()
  set(_name ${_entry})
  if(_n GREATER 4)
    list(GET _l 4 _name)
  endif()
  # one descriptor set; binding = register + 0 (b), 16 (t), 32 (s), 48 (u) (nr_vulkan.cpp
  # "Bindings"); vertex shaders flip Y so the framebuffer matches D3D's (SV_Position y down)
  set(_extra)
  if(_stage STREQUAL "vs")
    set(_extra -fvk-invert-y)
  endif()
  set(_out ${_rg_vk_gen}/vk_${_name}.h)
  add_custom_command(
    OUTPUT ${_out}
    COMMAND ${RG_DXC} -nologo -spirv -fspv-target-env=vulkan1.3 -fvk-use-dx-layout
            -fvk-b-shift 0 all -fvk-t-shift 16 all -fvk-s-shift 32 all -fvk-u-shift 48 all
            -Wno-ambig-lit-shift ${_extra} -O3 -T ${_stage}_6_0 -E ${_entry} ${_defs} -Vn g_spv_${_name} -Fh ${_out}
            ${_rg_vk_src}/${_src}
    DEPENDS ${_rg_vk_src}/${_src} ${_rg_vk_src}/gs_common.hlsli
    COMMENT "dxc -spirv ${_name}"
    VERBATIM)
  list(APPEND _rg_vk_headers ${_out})
endforeach()
add_custom_target(rg_vk_shaders DEPENDS ${_rg_vk_headers})

set(_rg_tp ${PROJECT_SOURCE_DIR}/third_party)
target_sources(rg_native_render PRIVATE nr_vulkan.cpp nr_vk_vma.cpp ${_rg_tp}/volk/volk.c)
target_include_directories(rg_native_render PRIVATE ${_rg_vk_gen} ${_rg_tp}/volk ${_rg_tp}/vulkan/include ${_rg_tp}/vma)
target_compile_definitions(rg_native_render PRIVATE RG_HAVE_VULKAN=1)
add_dependencies(rg_native_render rg_vk_shaders)
set_source_files_properties(nr_vulkan.cpp nr_vk_vma.cpp ${_rg_tp}/volk/volk.c PROPERTIES COMPILE_OPTIONS "-O2;-w")
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  set_source_files_properties(nr_vulkan.cpp PROPERTIES COMPILE_OPTIONS "-O2;-Wno-unused-parameter;-Wno-missing-field-initializers")
endif()
if(UNIX)
  target_link_libraries(rg_native_render PUBLIC ${CMAKE_DL_LIBS})
endif()

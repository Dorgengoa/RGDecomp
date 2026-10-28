# SPDX-License-Identifier: CC0-1.0
# rg_runtime: the platform glue that boots every model under the host shell
# and drives the virtual clock (docs/RUNTIME.md).  Needs src/host (RG_HOST).
add_library(rg_runtime STATIC rg_runtime.h runtime.c crt0.c fstats_sys.h fstats_sys.c)
target_include_directories(rg_runtime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_runtime PUBLIC
  rg_host
  rg_ps2_kernel rg_sce_kernel
  rg_ps2_gs rg_ps2_vu rg_vu0 rg_ps2_vif rg_ps2_dmac rg_sce_graphics rg_ps2_hwbus
  rg_native_fs rg_native_fs_oracle rg_native_audio
  rg_ps2_cdvd rg_sce_cdvd
  rg_ps2_iop rg_ps2_iop_hle rg_ps2_sif rg_sce_sif
  rg_ps2_padmc rg_sce_padmc
  rg_ps2_spu rg_ps2_sound
  rg_ps2_spin
  rg_flags)

# guest-side smoke workload shared by the demo and tests/runtime
add_library(rg_runtime_demo_guest STATIC demo/demo_guest.h demo/demo_guest.c)
target_include_directories(rg_runtime_demo_guest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/demo)
target_link_libraries(rg_runtime_demo_guest PUBLIC rg_runtime)

add_executable(rg-runtime-demo demo/runtime_demo.c)
target_link_libraries(rg-runtime-demo PRIVATE rg_runtime_demo_guest rg_runtime rg_flags)

foreach(t rg_runtime rg_runtime_demo_guest rg-runtime-demo)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

# $RG_FIELD_STATS host samples (fstats_sys.c: GetProcessMemoryInfo)
if(WIN32)
  target_link_libraries(rg_runtime PUBLIC psapi)
endif()

# GPU GS renderer (docs/GPU.md "Real game validation"): RG_GPU / cfg.gpu picks
# it at run time.  src/gpu is configured before this directory.
if(TARGET rg_gpu)
  target_link_libraries(rg_runtime PUBLIC rg_gpu)
  target_compile_definitions(rg_runtime PRIVATE RG_HAVE_GPU=1)
endif()
# native audio engine (docs/NATIVE-AUDIO.md): RG_AUDIO=native|hle|compare
target_compile_definitions(rg_runtime PRIVATE RG_HAVE_NATIVE_AUDIO=1)
# native renderer wiring (docs/NATIVE-RENDER.md): RG_RENDER=native
if(TARGET rg_native_render)
  target_link_libraries(rg_runtime PUBLIC rg_native_render)
  target_compile_definitions(rg_runtime PRIVATE RG_HAVE_NATIVE_RENDER=1)
endif()

# VU0 micro mode (vcallms on the VU interpreter) exists only in RG_VU0_MODE=model; local /
# native run the microprogram as C and never bind a VU0 (docs/NATIVE-CPU.md section 8)
if(RG_VU0_MODE STREQUAL "model")
  target_compile_definitions(rg_runtime PRIVATE RG_VU0_MICRO_BIND=1)
endif()

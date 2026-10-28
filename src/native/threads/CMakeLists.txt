# SPDX-License-Identifier: CC0-1.0
# Native threads and timing (docs/NATIVE-THREADS.md).  Added from src/sce/kernel/CMakeLists.txt
# (the game links it through rg_sce_kernel), so the top-level list stays untouched.
#
#   rg_native_fiber        host coroutines on fixed-address stacks (save states): the flows'
#                          stacks; shared with the HLE (src/ps2/kernel)
#   rg_native_kernel       the native kernel table: the frame-driven implementation of the ps2k
#                          API (kapi/ps2k.h) under rg_nk_* names; a default build's dispatcher
#                          (src/ps2/kernel/kdispatch.c) forwards to it for RG_THREADS=native
#   rg_native_kernel_ps2k  RG_NATIVE_ONLY: the same table under the real ps2k_* names; replaces
#                          rg_ps2_kernel (no HLE, no dispatcher) in rg-game
#   rg_native_spin         RG_NATIVE_ONLY: the spin stage's runtime over the native table;
#                          replaces rg_ps2_spin in rg-game
#   rg_native_threads      RG_THREADS mode, the frame driver (rg_frame.c), paced mode (rg_pace.c),
#                          the game's timer-0 frame clock over logic time (rg_logic_time.c)

# ---- host coroutines --------------------------------------------------------------------
add_library(rg_native_fiber STATIC fiber/fiber.h fiber/fiber_arena.h fiber/fiber_arena.c kapi/ps2k_ss.h)
if(WIN32)
  target_sources(rg_native_fiber PRIVATE fiber/fiber_win32.c)
else()
  target_sources(rg_native_fiber PRIVATE fiber/fiber_ucontext.c)
endif()
target_include_directories(rg_native_fiber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/fiber ${CMAKE_CURRENT_SOURCE_DIR}/kapi)
target_link_libraries(rg_native_fiber PRIVATE rg_flags)

# ---- the native kernel table ------------------------------------------------------------
set(_rg_nk_src kapi/ps2k.h kapi/ps2k_ss.h kapi/ps2k_rename.h kapi/ps2k_api.inc
  rg_nk_internal.h rg_nk.c rg_nk_irq.c rg_nk_ss.c)
add_library(rg_native_kernel STATIC ${_rg_nk_src})
target_include_directories(rg_native_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/kapi)
target_link_libraries(rg_native_kernel PUBLIC rg_native_fiber PRIVATE rg_flags)
set(_rg_nt_targets rg_native_fiber rg_native_kernel)
if(RG_NATIVE_ONLY)
  add_library(rg_native_kernel_ps2k STATIC ${_rg_nk_src})
  target_include_directories(rg_native_kernel_ps2k PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/kapi)
  target_link_libraries(rg_native_kernel_ps2k PUBLIC rg_native_fiber PRIVATE rg_flags)
  target_compile_definitions(rg_native_kernel_ps2k PRIVATE RG_NK_REAL_NAMES=1 RG_NATIVE_ONLY=1)
  add_library(rg_native_spin STATIC rg_spin_native.c)
  target_include_directories(rg_native_spin PUBLIC ${PROJECT_SOURCE_DIR}/src/ps2/spin)
  target_link_libraries(rg_native_spin PUBLIC rg_native_threads PRIVATE rg_flags)
  target_compile_definitions(rg_native_spin PRIVATE RG_NATIVE_ONLY=1)
  list(APPEND _rg_nt_targets rg_native_kernel_ps2k rg_native_spin)
endif()

# ---- RG_THREADS, the frame driver, paced mode -------------------------------------------
add_library(rg_native_threads STATIC rg_threads.h rg_threads_oracle.h rg_threads.c rg_frame.c rg_pace.h rg_pace.c
  rg_logic_time.c)
target_include_directories(rg_native_threads PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_threads PUBLIC rg_ps2_kernel PRIVATE rg_flags)
list(APPEND _rg_nt_targets rg_native_threads)

foreach(t ${_rg_nt_targets})
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

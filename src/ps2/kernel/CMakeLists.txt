# SPDX-License-Identifier: CC0-1.0
# EE kernel HLE core (docs/KERNEL.md): the oracle (RG_THREADS=hle|service|frame) and the
# kernel of the tests.  The ps2k API header is src/native/threads/kapi/ps2k.h; this library
# defines it as ps2k_hle_* and kdispatch.c defines ps2k_*, forwarding to the HLE or to the
# native kernel table (rg_native_kernel: RG_THREADS=native) by ps2k_init's cfg.native
# (docs/NATIVE-THREADS.md "Native kernel table").  RG_NATIVE_ONLY builds replace this library
# in rg-game by rg_native_kernel_ps2k (cmake/native_only.cmake).
add_library(rg_ps2_kernel STATIC
  ps2k.h
  ps2k_ss.h
  internal.h
  kcore.c
  kirq.c
  kdispatch.c
  # save states (docs/TEST-FIXTURES.md): kernel hook; the fixed-address fiber stacks are
  # rg_native_fiber (src/native/threads/fiber)
  kstate_ss.c)
target_include_directories(rg_ps2_kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_kernel PUBLIC rg_native_kernel rg_native_fiber rg_flags)
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_ps2_kernel PRIVATE -Wall -Wextra)
endif()

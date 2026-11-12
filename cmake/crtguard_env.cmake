# Build-time half of the wrong-CRT guard (cmake/crtguard.cmake): run by target rg_crt_env
# before anything else in the build dir.  -DRG_WANT=<VCToolsVersion> -DRG_LIBDIR=x86|x64
# -DRG_MODE=FATAL_ERROR|WARNING -DRG_BUILD_DIR=...
if("$ENV{RG_CRT_ENV_SKIP}" STREQUAL "1")
  message(STATUS "rg CRT guard: environment check SKIPPED (RG_CRT_ENV_SKIP=1; control runs only)")
  return()
endif()
set(_have "$ENV{VCToolsVersion}")
string(REPLACE "\\" "/" _lib "$ENV{LIB}")
string(TOLOWER "${_lib}" _lib)
string(TOLOWER "/msvc/${RG_WANT}/lib/${RG_LIBDIR}" _want_lib)
string(FIND "${_lib}" "${_want_lib}" _at)
if(NOT _have STREQUAL RG_WANT OR _at LESS 0)
  if(NOT _have)
    set(_have "unset: not a vcvars shell")
  endif()
  message(${RG_MODE} "rg CRT guard: this build runs outside the vcvars ${RG_LIBDIR} environment the build dir "
    "${RG_BUILD_DIR} was configured with (VCToolsVersion ${_have}, LIB without MSVC/${RG_WANT}/lib/${RG_LIBDIR}; "
    "want ${RG_WANT}).  clang / lld-link would compile and link another MSVC CRT / STL than the build dir's "
    "objects (docs/TOOLCHAIN.md \"Wrong CRT / STL\", \"MSVC toolset\").  Build with "
    "python tools/native/lane_build.py BUILD_DIR [TARGET], python tools/playtest/vcrun.py BUILD_DIR -- ninja TARGET, "
    "tools/build.ps1 or build_playtest.py.")
  # (FATAL_ERROR: every other target of the build dir waits for this one, so nothing was compiled)
endif()

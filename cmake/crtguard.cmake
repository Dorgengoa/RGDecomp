# Wrong-CRT guard (docs/TOOLCHAIN.md "Wrong CRT / STL"; lane integ4, 2026-11-07).
# 2026-11-10 (lane menuleft, USER): the build toolset is VS 2022 Build Tools, MSVC 14.44 (VS 2019
# was removed).  The game's one CRT dependency that changed (float sqrtf rounding) is mapped out
# of the CRT (port/sqrtf_map.h, cmake/game.cmake); the guard still keeps every build dir on ONE
# toolset (docs/TOOLCHAIN.md "MSVC toolset").  The notes below are from the VS 2019 era.
#
# clang / lld-link take the MSVC CRT, STL headers and libraries from the environment
# (VCToolsInstallDir / INCLUDE / LIB, set by `vcvarsall.bat x86`); without it they autodetect
# the NEWEST Visual Studio (VS 2022 here).  An i686 build dir configured inside vcvars and later
# rebuilt by plain `ninja` from an ordinary shell therefore compiles the changed files against
# VS 2022's STL and links VS 2022's CRT: other float helpers (_sqrtf ...), other pixels, and the
# golden route's run hash differs from field 24,894 (lane rtgi2).  Two checks, i686 Windows only:
#   1. before anything is built: target rg_crt_env (every target depends on it) fails unless
#      VCToolsVersion / LIB are the toolset this build dir was configured with
#      (RG_MSVC_TOOLS_VERSION, recorded at the first configure, which must run inside vcvars);
#   2. after rg-game / rg-game-oracle are linked: tools/native/crtcheck.py reads the link map
#      and fails (and renames the exe to *.wrongcrt) when the CRT objects are not VS 2019's.
# x64 Windows: check 1 only warns.  -DRG_CRT_GUARD=OFF removes both (experiments only).
# $RG_CRT_ENV_SKIP=1 skips check 1 for one build (the control run that proves check 2).
option(RG_CRT_GUARD "fail Windows builds run outside the vcvars environment they were configured with" ON)
set(RG_MSVC_TOOLS_DOC "14.44.35207")   # docs/TOOLCHAIN.md "MSVC toolset": VS 2022 Build Tools (USER 2026-11-10)

if(WIN32 AND RG_CRT_GUARD AND CMAKE_C_COMPILER_TARGET MATCHES "windows-msvc")
  set(_rg_vc "$ENV{VCToolsVersion}")
  if(NOT RG_MSVC_TOOLS_VERSION)
    if(NOT _rg_vc AND NOT RG_ARCH STREQUAL "i686")
      # x64: warn only (no i686-like pixel / hash difference seen); toolset taken as the documented one
      message(WARNING "rg CRT guard: x64 build dir configured outside vcvars x64 (VCToolsVersion unset); "
        "use tools/build.ps1 -Arch x64 (docs/TOOLCHAIN.md \"Wrong CRT / STL\")")
      set(_rg_vc "${RG_MSVC_TOOLS_DOC}")
    endif()
    if(NOT _rg_vc)
      message(FATAL_ERROR "rg CRT guard: configure this ${RG_ARCH} build dir inside a vcvars shell "
        "(tools/build.ps1, tools/playtest/build_playtest.py, tools/native/lane_build.py or "
        "tools/playtest/vcrun.py): VCToolsVersion is not set, so clang / lld-link would pick whatever "
        "MSVC CRT / STL they find (docs/TOOLCHAIN.md \"Wrong CRT / STL\").")
    endif()
    set(RG_MSVC_TOOLS_VERSION "${_rg_vc}" CACHE STRING
        "MSVC toolset (VCToolsVersion) this build dir is built with; checked before every build (cmake/crtguard.cmake)")
  endif()
  if(RG_ARCH STREQUAL "i686" AND NOT RG_MSVC_TOOLS_VERSION STREQUAL RG_MSVC_TOOLS_DOC)
    message(WARNING "rg CRT guard: i686 build dir on MSVC ${RG_MSVC_TOOLS_VERSION}, not the baselines' "
      "${RG_MSVC_TOOLS_DOC} (VS 2019 Build Tools): exes are not comparable with the gate baselines")
  endif()
  message(STATUS "rg CRT guard: MSVC ${RG_MSVC_TOOLS_VERSION} (${RG_ARCH})")
  set(_rg_crt_mode FATAL_ERROR)
  if(NOT RG_ARCH STREQUAL "i686")
    set(_rg_crt_mode WARNING)
  endif()
  set(_rg_crt_libdir "x86")
  if(RG_ARCH STREQUAL "x64")
    set(_rg_crt_libdir "x64")
  endif()
  add_custom_target(rg_crt_env ALL
    COMMAND ${CMAKE_COMMAND} -DRG_WANT=${RG_MSVC_TOOLS_VERSION} -DRG_LIBDIR=${_rg_crt_libdir}
            -DRG_MODE=${_rg_crt_mode} -DRG_BUILD_DIR=${CMAKE_BINARY_DIR}
            -P ${CMAKE_CURRENT_LIST_DIR}/crtguard_env.cmake
    COMMENT "rg CRT guard: MSVC ${RG_MSVC_TOOLS_VERSION} environment"
    VERBATIM)
endif()

# Called last in the top CMakeLists.txt: every target waits for rg_crt_env (so nothing is
# compiled outside the environment), the game exes get the post-link map check.
function(_rg_crtguard_targets dir out)
  get_property(_t DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
  get_property(_s DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
  foreach(s ${_s})
    _rg_crtguard_targets(${s} _sub)
    list(APPEND _t ${_sub})
  endforeach()
  set(${out} ${_t} PARENT_SCOPE)
endfunction()

function(rg_crtguard_finalize)
  if(NOT TARGET rg_crt_env)
    return()
  endif()
  _rg_crtguard_targets(${CMAKE_SOURCE_DIR} _all)
  foreach(t ${_all})
    if(NOT t STREQUAL "rg_crt_env")
      get_target_property(_ty ${t} TYPE)
      if(NOT _ty STREQUAL "INTERFACE_LIBRARY")
        add_dependencies(${t} rg_crt_env)
      endif()
    endif()
  endforeach()
  if(RG_ARCH STREQUAL "i686" AND RG_PYTHON)
    # the build dir's toolset (14.44 / 14.29) when crtcheck knows it: the map must be that one
    string(REGEX MATCH "^[0-9]+[.][0-9]+" _rg_tk "${RG_MSVC_TOOLS_VERSION}")
    set(_rg_tk_arg "")
    if(_rg_tk STREQUAL "14.44" OR _rg_tk STREQUAL "14.29")
      set(_rg_tk_arg --toolset ${_rg_tk})
    endif()
    foreach(t rg-game rg-game-oracle)
      if(TARGET ${t})
        add_custom_command(TARGET ${t} POST_BUILD
          COMMAND ${RG_PYTHON} ${CMAKE_SOURCE_DIR}/tools/native/crtcheck.py --quiet --fail-rename ${_rg_tk_arg}
                  $<TARGET_FILE:${t}>
          VERBATIM)
      endif()
    endforeach()
  endif()
endfunction()

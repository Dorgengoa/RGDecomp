# SPDX-License-Identifier: CC0-1.0
# RG_NATIVE_ONLY (docs/NATIVE-ONLY.md, PLAN.md D9 "Native end state"): rg-game links no
# IOP / SIF / pad+card server / sound HLE / SPU2 / CDVD sector model / FS oracle.
#
# How: the libraries the game links are left as they are (tests, demos and tools keep
# linking the oracles through them); for rg-game, every library in its link closure that
# reaches an oracle, or whose sources have oracle branches, gets a native-only CLONE:
# same sources, same properties, compiled with RG_NATIVE_ONLY=1 (src/native/iop/rg_iop.h:
# RG_IOP_ORACLE 0), linking the clones of its dependencies and none of the dropped
# libraries.  A clone keeps the original's OUTPUT_NAME (in <build>/nonly/), so the map
# names `rg_runtime:runtime.c.obj` as before (save-state policy rows in
# src/savestate/ss_map.c and tools/native/link_audit.py match on those names).
# Dropped libraries still give their include directories (headers only: types and
# constants the guarded code names).
#
#   rg_native_only_map(<out-var> <lib>...)   the rg-game link list, native-only
#
# Included by cmake/game_link.cmake when RG_NATIVE_ONLY is ON.

# libraries rg-game must not link (the ctest native_only.link_audit checks the result)
set(RG_NONLY_DROP
  rg_ps2_sif rg_ps2_iop rg_ps2_iop_hle rg_ps2_padmc rg_ps2_sound rg_snd_tools rg_ps2_spu
  rg_ps2_cdvd rg_native_fs_oracle)
# replaced by a native implementation of the same SDK surface.  The EE kernel HLE goes too
# (docs/NATIVE-THREADS.md "Native-only"): the native kernel table under the real ps2k names
# (no scheduler, no dispatcher), the spin runtime over it and libkernl without the census
# recorder.  A replacement's own dependencies are mapped like any library's (it is cloned
# when one of them changes, e.g. rg_native_threads -> its clone).
set(RG_NONLY_REPLACE rg_sce_cdvd=rg_sce_cdvd_native rg_ps2_kernel=rg_native_kernel_ps2k
  rg_ps2_spin=rg_native_spin rg_sce_kernel=rg_sce_kernel_native
  rg_sce_graphics=rg_sce_graphics_native rg_ps2_hwbus=rg_ovl_data)
# the renderer lane's models that left rg-game (docs/NATIVE-RENDER.md "DMA without the DMAC",
# "Hardware register sites"): libdma moves the sends itself (rg_sce_graphics_native), the frame
# chain is walked natively, the GS privileged / VIF1_FBRST sites go through port/hwaccess.h;
# RG_OVL_DATA keeps its own library (rg_ovl_data, what rg_ps2_hwbus linked for it).  VIF1 /
# VU1 went in 2026-10-18 (8) ("VU1 programs at the walker"): the walker feeds the GS itself and
# hands VU work to nr_vux.c (VU memory, resident microcode, the translated programs)
list(APPEND RG_NONLY_DROP rg_ps2_dmac rg_ps2_vif rg_ps2_vu)
# The GS model and its GPU renderer went at checkpoint 10 (docs/NATIVE-RENDER.md): the native
# state block, GIF input and device (rg_native_render's nr_gs.c / nr_dev.cpp / nr_d3d11.cpp).
# Only where the native device exists (the D3D11 backend: rg_gpu builds); headless Linux builds
# keep feeding the software GS model (docs/LINUX.md).
if(TARGET rg_gpu)
  list(APPEND RG_NONLY_DROP rg_gpu rg_ps2_gs)
endif()
# VU0 (docs/NATIVE-CPU.md section 9): libvu0 as plain C lanes + the microprogram and the
# shared contexts (rg_native_vu0) in place of the libvu0 transcription on the VU register
# struct; RG_VU0_MODE=model keeps the model on purpose
if(NOT RG_VU0_MODE STREQUAL "model")
  list(APPEND RG_NONLY_REPLACE rg_sce_vu0=rg_native_vu0)
endif()
# Overlays (docs/OVERLAY.md section 8): the native module table (rg_native_ovl + the
# generated rg_ovl_native_game objects, cmake/game_link.cmake) in place of the arena
# manager, its binding (and through it the RG_OVL_DATA resolver, rg_ovl_data) and the arena
if(RG_NATIVE_OVL)
  list(APPEND RG_NONLY_REPLACE rg_ps2_overlay=rg_native_ovl)
  list(APPEND RG_NONLY_DROP rg_ps2_overlay_bind rg_ovl_arena)
endif()
# sources with oracle branches (#if RG_IOP_ORACLE / RG_THREADS_ORACLE / RG_NATIVE_ONLY):
# always cloned
set(RG_NONLY_GUARDED rg_runtime rg_sce_sif rg_sce_padmc rg_native_iop rg_native_audio
  rg_native_threads rg_native_render)

# include directories a dropped library (and what it links) would have given
function(_rg_nonly_dropped_includes tgt out)
  set(dirs)
  set(todo ${tgt})
  set(seen)
  while(todo)
    list(POP_FRONT todo t)
    if(t IN_LIST seen OR NOT TARGET ${t})
      continue()
    endif()
    list(APPEND seen ${t})
    get_target_property(inc ${t} INTERFACE_INCLUDE_DIRECTORIES)
    if(inc)
      list(APPEND dirs ${inc})
    endif()
    get_target_property(il ${t} INTERFACE_LINK_LIBRARIES)
    if(il)
      foreach(d ${il})
        string(REGEX REPLACE "^\\$<LINK_ONLY:(.*)>$" "\\1" d "${d}")
        list(APPEND todo ${d})
      endforeach()
    endif()
  endwhile()
  list(REMOVE_DUPLICATES dirs)
  set(${out} "${dirs}" PARENT_SCOPE)
endfunction()

# map one link item: "" (dropped), the item itself, a replacement or a clone
function(_rg_nonly_item item out)
  get_property(have GLOBAL PROPERTY _RG_NONLY_DONE_${item} SET)
  if(have)
    get_property(v GLOBAL PROPERTY _RG_NONLY_DONE_${item})
    set(${out} "${v}" PARENT_SCOPE)
    return()
  endif()
  set(v "${item}")
  set(repl)
  foreach(r ${RG_NONLY_REPLACE})
    string(REPLACE "=" ";" r "${r}")
    list(GET r 0 from)
    list(GET r 1 to)
    if(item STREQUAL from)
      set(repl ${to})
    endif()
  endforeach()
  if(item IN_LIST RG_NONLY_DROP)
    set(v "")
  elseif(repl)
    _rg_nonly_item(${repl} v)
  elseif(TARGET ${item})
    get_target_property(type ${item} TYPE)
    get_target_property(imported ${item} IMPORTED)
    get_target_property(aliased ${item} ALIASED_TARGET)
    if(type STREQUAL "STATIC_LIBRARY" AND NOT imported AND NOT aliased)
      get_target_property(ll ${item} LINK_LIBRARIES)
      get_target_property(il ${item} INTERFACE_LINK_LIBRARIES)
      if(NOT ll)
        set(ll)
      endif()
      if(NOT il)
        set(il)
      endif()
      set(changed 0)
      set(new_ll)
      set(new_il)
      set(drop_inc)
      foreach(d ${ll})
        if(d MATCHES "^::@")
          continue()       # cross-directory scope markers: target names are global
        endif()
        _rg_nonly_item("${d}" m)
        if(NOT m STREQUAL d)
          set(changed 1)
        endif()
        if(m)
          list(APPEND new_ll ${m})
        elseif(TARGET ${d})
          _rg_nonly_dropped_includes(${d} di)
          list(APPEND drop_inc ${di})
        endif()
      endforeach()
      foreach(d ${il})
        if(d MATCHES "^::@")
          continue()
        endif()
        set(wrap 0)
        if(d MATCHES "^\\$<LINK_ONLY:(.*)>$")
          set(wrap 1)
          set(d "${CMAKE_MATCH_1}")
        endif()
        _rg_nonly_item("${d}" m)
        if(NOT m STREQUAL d)
          set(changed 1)
        endif()
        if(m)
          if(wrap)
            list(APPEND new_il "$<LINK_ONLY:${m}>")
          else()
            list(APPEND new_il ${m})
          endif()
        elseif(TARGET ${d})
          _rg_nonly_dropped_includes(${d} di)
          list(APPEND drop_inc ${di})
        endif()
      endforeach()
      if(changed OR item IN_LIST RG_NONLY_GUARDED)
        set(v ${item}_nonly)
        get_target_property(srcs ${item} SOURCES)
        get_target_property(sdir ${item} SOURCE_DIR)
        set(abs)
        set(gen 0)
        foreach(s ${srcs})
          string(FIND "${s}" "${CMAKE_BINARY_DIR}" bpos)
          if(bpos EQUAL 0)
            set(gen 1)     # a generated file: build the original first
          endif()
          if(s MATCHES "\\.(h|hpp|inl)$")
            continue()     # headers: not compiled (a generated one comes from the original)
          endif()
          if(NOT IS_ABSOLUTE "${s}" AND NOT s MATCHES "^\\$<")
            set(s "${sdir}/${s}")
          endif()
          list(APPEND abs "${s}")
        endforeach()
        add_library(${v} STATIC ${abs})
        foreach(p INCLUDE_DIRECTORIES COMPILE_DEFINITIONS COMPILE_OPTIONS COMPILE_FEATURES
                  C_STANDARD CXX_STANDARD C_EXTENSIONS CXX_EXTENSIONS MSVC_RUNTIME_LIBRARY
                  INTERFACE_INCLUDE_DIRECTORIES INTERFACE_COMPILE_DEFINITIONS
                  INTERFACE_COMPILE_OPTIONS INTERFACE_LINK_OPTIONS INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)
          get_target_property(pv ${item} ${p})
          if(pv)
            set_property(TARGET ${v} PROPERTY ${p} "${pv}")
          endif()
        endforeach()
        list(REMOVE_DUPLICATES drop_inc)
        if(drop_inc)
          target_include_directories(${v} PUBLIC ${drop_inc})
        endif()
        target_compile_definitions(${v} PRIVATE RG_NATIVE_ONLY=1)
        if(rg_ps2_gs IN_LIST RG_NONLY_DROP)
          target_compile_definitions(${v} PRIVATE RG_NATIVE_GS=1)   # no GS model: the native state block (nr_gs.h)
        endif()
        get_target_property(oname ${item} OUTPUT_NAME)
        if(NOT oname)
          set(oname ${item})
        endif()
        set_target_properties(${v} PROPERTIES OUTPUT_NAME ${oname}
          ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/nonly)
        set_property(TARGET ${v} PROPERTY LINK_LIBRARIES "${new_ll}")
        set_property(TARGET ${v} PROPERTY INTERFACE_LINK_LIBRARIES "${new_il}")
        if(gen)
          add_dependencies(${v} ${item})   # generated sources / headers of the original
        endif()
        get_target_property(mdeps ${item} MANUALLY_ADDED_DEPENDENCIES)
        if(mdeps)
          add_dependencies(${v} ${mdeps})  # e.g. rg_native_render -> rg_gpu_shaders
        endif()
        set_property(GLOBAL APPEND PROPERTY RG_NONLY_CLONES ${item})
      endif()
    endif()
  endif()
  set_property(GLOBAL PROPERTY _RG_NONLY_DONE_${item} "${v}")
  set(${out} "${v}" PARENT_SCOPE)
endfunction()

function(rg_native_only_map out)
  set(r)
  foreach(l ${ARGN})
    if(TARGET ${l} OR l IN_LIST RG_NONLY_DROP)
      _rg_nonly_item(${l} m)
      if(m)
        list(APPEND r ${m})
      endif()
    else()
      list(APPEND r ${l})
    endif()
  endforeach()
  set(${out} "${r}" PARENT_SCOPE)
endfunction()

# SPDX-License-Identifier: CC0-1.0
# Sound HLE: sdr_driver 0x80000701 (+ Standard Kit SK blocks) and pcm_mixer 0x123456
# over the SPU2 engine (docs/SOUND.md, docs/SOUND-PROTOCOL.md).
add_library(rg_ps2_sound STATIC
  snd.h snd_internal.h snd_hd.h
  snd_srv.c snd_synth.c snd_seq.c snd_hd.c)
target_include_directories(rg_ps2_sound PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_ps2_sound PUBLIC rg_ps2_spu rg_ps2_sif rg_ps2_iop PRIVATE rg_flags)

# Tools/tests only: game archive + .snd pack reader and an EE-driver stand-in.
add_library(rg_snd_tools STATIC snd_pack.h snd_pack.c snd_eesim.h snd_eesim.c)
target_include_directories(rg_snd_tools PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_snd_tools PUBLIC rg_ps2_sound PRIVATE rg_flags)

add_executable(rg-sound-play rg_sound_play.c)
target_link_libraries(rg-sound-play PRIVATE rg_snd_tools rg_ps2_sound rg_flags)

foreach(t rg_ps2_sound rg_snd_tools rg-sound-play)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

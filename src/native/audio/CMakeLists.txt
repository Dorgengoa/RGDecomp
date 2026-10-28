# SPDX-License-Identifier: CC0-1.0
# Native audio engine (docs/NATIVE-AUDIO.md): banks, sequences, SE notes, PCM streams,
# float mixing.  No SIF/IOP/SPU2 model.  ra_host.c (env, logs, WAV, runtime glue) and
# ra_present.c (the presentation mix: per-source volumes) are classified HOST for save
# states (src/savestate/ss_map.c); the rest is model state.
add_library(rg_native_audio STATIC
  rg_audio.h rg_audio_game.h ra_internal.h ra_hd.h
  ra_hd.c ra_mix.c ra_synth.c ra_seq.c ra_engine.c ra_game.c ra_host.c ra_present.c)
target_include_directories(rg_native_audio PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_native_audio PRIVATE rg_flags)
if(WIN32)
  target_compile_definitions(rg_native_audio PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg_native_audio PRIVATE -Wall -Wextra)
endif()

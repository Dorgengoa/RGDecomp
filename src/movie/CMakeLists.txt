# SPDX-License-Identifier: CC0-1.0
# Movie playback (docs/MOVIE.md): CC0 MPEG-2 decoder for the converted movies, the
# SShd/SSbd audio re-encoder, and the movie service that replaces the game's movie layer.
# No external dependencies.  Tests: tests/movie (ctest -L movie).
add_library(rg_movie STATIC
  movie.h mv_internal.h
  mv_dec.c mv_vlc.c mv_idct.c mv_color.c mv_audio.c mv_service.c)
target_include_directories(rg_movie PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_movie PRIVATE rg_flags)
if(NOT WIN32)
  target_link_libraries(rg_movie PUBLIC m)
endif()

# Game-facing glue for the movie-layer overrides (movie_game.h): one global service on
# the kernel's virtual clock.  The final game link needs rg_movie_game (and, with the
# runtime, rg_movie_runtime + a call to rg_movie_runtime_attach()).
add_library(rg_movie_game STATIC movie_game.h mv_game.c)
target_include_directories(rg_movie_game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rg_movie_game PUBLIC rg_movie rg_ps2_kernel PRIVATE rg_flags)
set(RG_MOVIE_TARGETS rg_movie rg_movie_game rg-movie-play)
if(TARGET rg_runtime)
  # data root from the runtime config, attached via rg_runtime_set_service_hook (the IPU
  # hwbus hooks and DMAC ch3/4 bindings are gone: docs/NATIVE-CPU.md section 8)
  add_library(rg_movie_runtime STATIC mv_runtime.c)
  target_link_libraries(rg_movie_runtime PUBLIC rg_movie_game rg_runtime
    PRIVATE rg_flags)
  list(APPEND RG_MOVIE_TARGETS rg_movie_runtime)
endif()

# rg-movie-play: headless decode/hash/yuv/service simulation; --window/--png with RG_HOST.
add_executable(rg-movie-play rg_movie_play.c)
target_link_libraries(rg-movie-play PRIVATE rg_movie rg_flags)
if(TARGET rg_host)
  target_link_libraries(rg-movie-play PRIVATE rg_host)
  target_compile_definitions(rg-movie-play PRIVATE RG_MOVIE_HAVE_HOST=1)
endif()

foreach(t IN LISTS RG_MOVIE_TARGETS)
  if(WIN32)
    target_compile_definitions(${t} PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(${t} PRIVATE -Wall -Wextra)
  endif()
endforeach()

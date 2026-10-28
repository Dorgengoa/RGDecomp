# SPDX-License-Identifier: CC0-1.0
# Movie tests (docs/MOVIE.md "Tests").  ctest -L movie
add_executable(rg-movie-tests movie_tests.c)
target_link_libraries(rg-movie-tests PRIVATE rg_movie rg_flags)
target_include_directories(rg-movie-tests PRIVATE ${CMAKE_SOURCE_DIR}/src/movie)
if(WIN32)
  target_compile_definitions(rg-movie-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(rg-movie-tests PRIVATE -Wall -Wextra)
endif()

# RG_DATA: the extracted game data with data/converted/MOVIE (PLAN D8). Tests that need it
# exit 77 (skipped) without it; it defaults to <repo>/data when the converted movies exist.
if(NOT DEFINED RG_MOVIE_DATA)
  if(DEFINED ENV{RG_DATA})
    set(RG_MOVIE_DATA $ENV{RG_DATA})
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/data/converted/MOVIE/00/GAMEOVER.mpg)
    set(RG_MOVIE_DATA ${CMAKE_SOURCE_DIR}/data)
  else()
    set(RG_MOVIE_DATA "")
  endif()
endif()
# FFmpeg is a verification tool only (never linked): the PSNR test runs it when present.
find_program(RG_FFMPEG NAMES ffmpeg PATHS C:/ffmpeg/bin NO_DEFAULT_PATH)
find_program(RG_FFMPEG NAMES ffmpeg)
if(NOT RG_FFMPEG)
  set(RG_FFMPEG "")
endif()

set(RG_MOVIE_TESTS vlc idct color audio_ss resolve service_sm service_skip service_restart
    service_pause service_loop service_error av_sync av_sync_30 retail_cadence determinism_synth
    real_frames real_hashes real_timestamps real_service real_av_sync real_determinism
    real_psnr)
foreach(t IN LISTS RG_MOVIE_TESTS)
  add_test(NAME movie.${t} COMMAND rg-movie-tests ${t})
  set_tests_properties(movie.${t} PROPERTIES TIMEOUT 900 LABELS movie SKIP_RETURN_CODE 77
    ENVIRONMENT "RG_DATA=${RG_MOVIE_DATA};RG_FFMPEG=${RG_FFMPEG};RG_MOVIE_FIXTURES=${CMAKE_CURRENT_SOURCE_DIR}")
endforeach()

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   av_sync_control:  retail pacing (one frame per game frame, audio free-running) on a
#                     29.97 fps / 48048 Hz movie must break the 1-frame A/V bound
#   hashes_control:   the reference hash list with one frame's hash flipped
#   retail_cadence_control: expects a new frame at every VBlank pop in retail mode
#                     (retail is one frame per two VBlanks, VALIDATION.md 6)
foreach(t av_sync hashes retail_cadence)
  add_test(NAME movie.${t}_control COMMAND rg-movie-tests ${t}_control)
  set_tests_properties(movie.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 900 LABELS movie
    ENVIRONMENT "RG_DATA=${RG_MOVIE_DATA};RG_MOVIE_FIXTURES=${CMAKE_CURRENT_SOURCE_DIR}")
endforeach()

# rg-movie-play smoke runs (skipped without data)
if(RG_MOVIE_DATA)
  add_test(NAME movie.play_tool COMMAND rg-movie-play --data ${RG_MOVIE_DATA} --bench 00/GAMEOVER)
  add_test(NAME movie.play_tool_service COMMAND rg-movie-play --data ${RG_MOVIE_DATA} --service 01/01_11)
  set_tests_properties(movie.play_tool movie.play_tool_service PROPERTIES TIMEOUT 300 LABELS movie)
endif()

# game-facing glue (needs the runtime, i.e. RG_HOST; the IPU binding test went with the
# IPU hooks: docs/NATIVE-CPU.md section 8)
if(TARGET rg_movie_runtime)
  add_executable(rg-movie-glue-tests movie_glue_tests.c)
  target_link_libraries(rg-movie-glue-tests PRIVATE rg_movie_runtime rg_movie_game rg_flags)
  if(WIN32)
    target_compile_definitions(rg-movie-glue-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
  endif()
  if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(rg-movie-glue-tests PRIVATE -Wall -Wextra)
  endif()
  foreach(t game)
    add_test(NAME movie.glue_${t} COMMAND rg-movie-glue-tests ${t})
    set_tests_properties(movie.glue_${t} PROPERTIES TIMEOUT 300 LABELS movie SKIP_RETURN_CODE 77
      ENVIRONMENT "RG_DATA=${RG_MOVIE_DATA}")
  endforeach()
endif()

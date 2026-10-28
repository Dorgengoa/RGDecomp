# SPDX-License-Identifier: CC0-1.0
# Sound tests (docs/SOUND.md).  ctest -L sound
add_executable(rg-sound-tests sound_tests.c)
target_link_libraries(rg-sound-tests PRIVATE rg_snd_tools rg_ps2_sound rg_ps2_spu rg_ps2_sif rg_ps2_iop rg_flags)
if(WIN32)
  target_compile_definitions(rg-sound-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# RG_DATA: the extracted game data (PLAN D8). Tests that need it exit 77 (skipped)
# when it is not set; it defaults to <repo>/data when that folder holds the archives.
if(NOT DEFINED RG_SOUND_DATA)
  if(DEFINED ENV{RG_DATA})
    set(RG_SOUND_DATA $ENV{RG_DATA})
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/data/DATA0_0.HD6)
    set(RG_SOUND_DATA ${CMAKE_SOURCE_DIR}/data)
  else()
    set(RG_SOUND_DATA "")
  endif()
endif()

set(RG_SOUND_TESTS adpcm adsr pitch loop hd_synthetic se_keyon midi pcm_ring movie
    movie_refill render_hash reverb hd_real se_keyon_real modhsyn_bend modhsyn_volume)
foreach(t IN LISTS RG_SOUND_TESTS)
  add_test(NAME sound.${t} COMMAND rg-sound-tests ${t})
  set_tests_properties(sound.${t} PROPERTIES TIMEOUT 120 LABELS sound SKIP_RETURN_CODE 77
    ENVIRONMENT "RG_DATA=${RG_SOUND_DATA};RG_IOP_QUIET=1")
endforeach()

# Deliberately-wrong controls: each must FAIL, proving its check is armed.
#   adpcm_control:    expects a wrong filter-1 sample
#   pcm_ring_control: expects the mixed block one DMA half (1024 frames) early
#   movie_control:    expects the movie read position to advance at 44.1 kHz
#   movie_refill_control: the EE refills from the unit being played (no input buffer):
#                     preset units are overwritten before they are heard
#   modhsyn_bend_control:   expects the old bend depth (>> 14: -4 semitones for bend 0)
#   modhsyn_volume_control: expects the old volume product (0x3FFF * vol / 127)
foreach(t adpcm pcm_ring movie movie_refill modhsyn_bend modhsyn_volume)
  add_test(NAME sound.${t}_control COMMAND rg-sound-tests ${t}_control)
  set_tests_properties(sound.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 120 LABELS sound
    ENVIRONMENT "RG_IOP_QUIET=1")
endforeach()

# rg-sound-play smoke: render an SE from the real data to a WAV (skipped without data).
if(RG_SOUND_DATA)
  add_test(NAME sound.play_tool COMMAND rg-sound-play --data ${RG_SOUND_DATA}
    --snd snd2/sy_000.snd --prog 3 --len 1 -o ${CMAKE_CURRENT_BINARY_DIR}/sy_000_p3.wav)
  set_tests_properties(sound.play_tool PROPERTIES TIMEOUT 120 LABELS sound
    ENVIRONMENT "RG_IOP_QUIET=1")
endif()

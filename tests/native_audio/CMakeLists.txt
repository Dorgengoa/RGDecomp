# SPDX-License-Identifier: CC0-1.0
# Native audio engine tests (docs/NATIVE-AUDIO.md).  ctest -L audio
# The oracle (the bring-up sound HLE, rg_snd_tools) is linked into the test only.
add_executable(native-audio-tests native_audio_tests.c)
target_link_libraries(native-audio-tests PRIVATE rg_native_audio rg_snd_tools rg_ps2_sound rg_ps2_spu
  rg_ps2_sif rg_ps2_iop rg_flags)
if(WIN32)
  target_compile_definitions(native-audio-tests PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

if(NOT DEFINED RG_AUDIO_DATA)
  if(DEFINED ENV{RG_DATA})
    set(RG_AUDIO_DATA $ENV{RG_DATA})
  elseif(EXISTS ${CMAKE_SOURCE_DIR}/data/DATA0_0.HD6)
    set(RG_AUDIO_DATA ${CMAKE_SOURCE_DIR}/data)
  else()
    set(RG_AUDIO_DATA "")
  endif()
endif()

foreach(t adpcm_same ids pcm se_compare seq_compare source_gain)
  add_test(NAME audio.${t} COMMAND native-audio-tests ${t})
  set_tests_properties(audio.${t} PROPERTIES TIMEOUT 300 LABELS audio SKIP_RETURN_CODE 77
    ENVIRONMENT "RG_DATA=${RG_AUDIO_DATA};RG_IOP_QUIET=1;RG_QUIET=1;RG_AUDIO=native")
endforeach()
# Deliberately-wrong controls (the engine one semitone sharp): each must FAIL.
foreach(t pcm se_compare seq_compare)
  add_test(NAME audio.${t}_control COMMAND native-audio-tests ${t}_control)
  set_tests_properties(audio.${t}_control PROPERTIES WILL_FAIL TRUE TIMEOUT 300 LABELS audio
    ENVIRONMENT "RG_DATA=${RG_AUDIO_DATA};RG_IOP_QUIET=1;RG_QUIET=1;RG_AUDIO=native")
endforeach()

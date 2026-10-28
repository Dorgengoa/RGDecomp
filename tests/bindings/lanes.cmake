# Override lanes with a test suite: name + its test file + the override
# sources it exercises.  Generated from build/bind-i686/lane_<lane>.tsv
# `#test-sources` rows; edit by hand.
set(RG_BT_LANES gamecop2 gspktee l5math platform vcallms)
set(RG_BT_LANE_SRCS
  ${CMAKE_SOURCE_DIR}/tests/bindings/ovr_gamecop2.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecDot3_1cba90.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecLengthSq_1cb470.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecLength_1cb4c0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecCross_1cb9f0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecSub_1cbd00.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecDivScalar_1cbbf0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecScaleToLength_1cb510.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MatMul_1cb700.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecNormalize_1cbb80.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxInverseAffine_1cb640.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/TriNormalDot_1cb600.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/model/VertsPackQuantized_164bb0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecMinMax_1cb570.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecLerp_1cbb20.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MatMulVec4Args_1cb7f0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/script/FixCameraRecInit_193860.c
  ${CMAKE_SOURCE_DIR}/tests/bindings/ovr_gspktee.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktWriteAD_13ec80.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktSetRGBAQ_13ee40.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktSetRGBAQVec_13edd0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktSetUV_13ed60.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktSetXYZPixel_13f110.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktSetXYZf_13f060.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktOpenGifTag_13f3b0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktBeginPrimAD_13f6b0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gs/GsPktFinalizeTags_13f260.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/container/DListNodeAdvance_42eb00.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/container/MotionListIsFinished_171d90.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/container/MotionListFindSubEntry_172430.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/sound/EventVoicePendingPop_24e6b0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/chara/CharaTableEntryGetWaitFrameParam_2260c0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/ui/MesWinAddCharY_274d10.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/anim/MotionPlayerGetBlendMaybe_172ce0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/chara/SurfaceParamFindByTriAttr_23a2b0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecCopy_1cbe30.c
  ${CMAKE_SOURCE_DIR}/tests/bindings/ovr_l5math.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/Vu0InnerProduct_13bd60.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecDistance_13d3d0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecDistanceXZ_13d390.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecLengthSq_13d440.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxIdentity_13d2e0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxMul_13d240.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxInverse_13cf40.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxProjectPoint_13c8c0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MtxTransformPoints_13c810.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/AabbContainsPoint_13e130.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/AabbOverlap_13e0e0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/vec/VecTriCross_13de70.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/math/PointInTriangle2D_13d4d0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/math/SegmentSphereIntersect_13da60.c
  # platform: interrupt handlers under the kernel/hwbus models, the dtor
  # chain, NameTableNodeSetImage, MSL ostream (src/crt).  Entries whose override
  # was dropped (game C since d784320c) fall back to game/ (CMakeLists.txt)
  ${CMAKE_SOURCE_DIR}/tests/bindings/ovr_platform.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gfx/GfxVblankStartHandler_15df20.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/gfx/Vif1IntcHandler_15e170.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/sound/SoundVblankIntrHandler_1bd6f0.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/movie/MovieDmacHandler_1d4b10.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/movie/MovieVblankHandler_1d4c90.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/sys/RegisterGlobalObject_100dc0.c
  ${CMAKE_SOURCE_DIR}/game/src/main/gfx/NameTableNodeSetImage_15a640.c
  # vcallms: VU0 micro mode on the shared register file (needs the retail ELF)
  ${CMAKE_SOURCE_DIR}/tests/bindings/ovr_vcallms.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MatFromSRTVu0_13bc90.c
  ${CMAKE_SOURCE_DIR}/overrides/src/main/matrix/MatRotateVu0_13bc20.c
)

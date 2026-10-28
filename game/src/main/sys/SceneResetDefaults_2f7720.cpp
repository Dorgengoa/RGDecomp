/* rgp:protos */
#line 1
#include "types.h"
extern "C" {

extern void ParticleSwirlReset_17d750(void *arg0);
extern void SceneSetTimeOfDay_1c5200(void *arg0, f32 arg1);
extern void ColorFromRgba128_1ce5f0(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void GameSceneSetTint_1ce940(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void GameSceneTimeScaleReset_1cecf0(void *arg0);
extern float SunFlareFadeOut_1cf4d0(void *, s32);
extern void SunFlareSetAlpha_1cf500(void *arg0, f32 arg1);
extern void SunFlareSetMaxAlpha_1cf510(void *arg0, f32 arg1);
extern void ScreenFadeInit_1cf770(void *arg0);
extern void GameSceneDoorGlareInit_1cf7c0(void *arg0);
extern void GameSceneSetCBlurEnable_1cf7e0(void *arg0, s32 arg1);
extern void GameSceneObjsResetCBlurMaybe_1cf8a0(void *arg0);
extern void GameSceneCBlurInit_1cf990(void *arg0, s32 arg1);
extern void GameSceneSoundInit_1d1260(void *arg0);
extern void *GetCurrentScene_1f5be0(void);

class VC_0 {
public:
    u8 pad[0x4394];
    VC_VPTR_MEMBER;
    void f() { VCM0(void, 0xC); }
};
class VC_1 {
public:
    u8 pad[0x4394];
    VC_VPTR_MEMBER; void f() { VCM0(void, 0x8); }
};
void SceneResetDefaults_2f7720(void)
{
    void *temp_16;
    void *temp_2;
    void *vtbl;

    temp_2 = GetCurrentScene_1f5be0();
    vtbl = *(void **)((u8 *)temp_2 + 0x4394);
    ((VC_0 *)(temp_2))->f();
    ((VC_1 *)(temp_2))->f();
    GameSceneSoundInit_1d1260(temp_2);
    ParticleSwirlReset_17d750((u8 *)temp_2 + 0x59E0);
    ScreenFadeInit_1cf770(temp_2);
    GameSceneCBlurInit_1cf990(temp_2, 0x30A);
    GameSceneObjsResetCBlurMaybe_1cf8a0(temp_2);
    *(s32 *)((u8 *)temp_2 + 0x5CF0) = 0x316;
    *(s32 *)((u8 *)temp_2 + 0x5CF4) = 4;
    SceneSetTimeOfDay_1c5200(temp_2, 12.0f);
    GameSceneDoorGlareInit_1cf7c0(temp_2);
    SunFlareFadeOut_1cf4d0(temp_2, 0);
    SunFlareSetMaxAlpha_1cf510(temp_2, 0.0f);
    SunFlareSetAlpha_1cf500(temp_2, 0.0f);
    GameSceneTimeScaleReset_1cecf0(temp_2);
    *(s32 *)((u8 *)temp_2 + 0x5DFC) = 0;
    GameSceneSetTint_1ce940(temp_2, 0, 0x80, 0x80, 0x80);
    GameSceneSetCBlurEnable_1cf7e0(temp_2, 1);
    temp_16 = (u8 *)temp_2 + 0x58A0;
    ColorFromRgba128_1ce5f0(temp_16, 0x80, 0x80, 0x80, 0x80);
    *(s16 *)((u8 *)temp_16 + 0x12) = 1;
    *(s8 *)((u8 *)temp_16 + 0x11) = 0;
    *(s16 *)((u8 *)temp_16 + 0x14) = 0;
    *(s16 *)((u8 *)temp_16 + 0x16) = 0;
}

}

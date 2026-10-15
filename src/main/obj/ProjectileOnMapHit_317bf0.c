#pragma optimization_level 3
#pragma opt_propagation off
#include "types.h"
#pragma opt_common_subs off

extern void VecScale_13be00(void *arg0, void *arg1, f32 arg2);
extern void VecAdd_13be20(void *arg0, void *arg1, void *arg2);
extern void VecSub_13be40(void *arg0, void *arg1, void *arg2);
extern f32 Vu0InnerProduct_13d300(void *arg0, void *arg1);
extern f32 VecLengthSq_13d440(void *arg0);
extern void SoundPlayScaledVolume_1b9520(s32 arg0, s32 arg1, f32 arg2, s32 arg3);
extern f32 VecLengthSq_1cb470(void *arg0);
extern void VecScaleToLength_1cb510(void *arg0, void *arg1, f32 arg2);
extern void VecLinearCombine_1cb8b0(void *arg0, void *arg1, void *arg2, f32 arg3, f32 arg4);
extern void VecSub_1cbd00(void *arg0, void *arg1, void *arg2);
extern s32 GameSceneSoundSlot1GetHandle_1d07b0(s32 arg0);
extern s32 GetCurrentScene_1f5be0(void);
extern void EffectSpawnWaterSplash_2d8400(s16 arg0, void *arg1);
extern void JudgeObjectOnMapHit_3141f0(void);
extern f32 D_0047D1DC;
extern f32 D_0047D274;
extern f32 D_0047D27C;

void ProjectileOnMapHit_317bf0(void *arg0, void *arg1)
{
    u8 sp70[0x10];
    u8 sp60[0x10];
    u8 sp50[0x10];
    u8 sp40[0x10];
    u8 *p;
    s32 x;
    f32 temp_f20;
    f32 temp_f20_2;

    JudgeObjectOnMapHit_3141f0();
    if ((*(s32 *)((u8 *)arg0 + 0x80) & 4) && (*(s32 *)((u8 *)arg0 + 0x7C) & 8)) {
        VecLinearCombine_1cb8b0(sp70, (u8 *)arg0 + 0x1B0, (u8 *)arg0 + 0x1A0, D_0047D274 * *(f32 *)((u8 *)arg1 + 0x28), 1.0f);
        *(f32 *)(sp70 + 4) += 1.0f;
        x = GameSceneSoundSlot1GetHandle_1d07b0(GetCurrentScene_1f5be0());
        SoundPlayScaledVolume_1b9520(x, 0x3A, 1.0f, 0);
        EffectSpawnWaterSplash_2d8400(*(s16 *)((u8 *)arg0 + 0x86), sp70);
        *(f32 *)((u8 *)arg0 + 0xCC) = 30.0f;
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) & 1) {
        VecLinearCombine_1cb8b0((u8 *)arg0 + 0x180, (u8 *)arg0 + 0x1B0, (u8 *)arg0 + 0x1A0, D_0047D274 * *(f32 *)((u8 *)arg1 + 0x2C), 1.0f);
        temp_f20 = D_0047D1DC + *(f32 *)((u8 *)arg0 + 0x190);
        VecSub_13be40(sp60, (u8 *)arg0 + 0x180, (u8 *)arg1 + 0x30);
        if (VecLengthSq_1cb470(sp60) <= (temp_f20 * temp_f20)) {
            p = sp60;
            VecScaleToLength_1cb510(p, p, temp_f20);
            VecAdd_13be20((u8 *)arg0 + 0x180, (u8 *)arg1 + 0x30, sp60);
        }
        VecScale_13be00(sp50, (u8 *)arg1 + 0x40, Vu0InnerProduct_13d300((u8 *)arg0 + 0x1B0, (u8 *)arg1 + 0x40) / VecLengthSq_13d440((u8 *)arg1 + 0x40));
        VecSub_1cbd00(sp40, (u8 *)arg0 + 0x1B0, sp50);
        VecLinearCombine_1cb8b0((u8 *)arg0 + 0x1B0, sp40, sp50, D_0047D27C, -(*(f32 *)((u8 *)arg0 + 0x1C8)));
    }
}

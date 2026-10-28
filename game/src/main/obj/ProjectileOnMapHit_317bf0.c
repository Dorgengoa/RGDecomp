/* rgp:protos */
#define RGP_SELF_ProjectileOnMapHit_317bf0 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#pragma opt_propagation off
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1DC;
extern f32 D_0047D274;
extern f32 D_0047D27C;

void ProjectileOnMapHit_317bf0(void *arg0, void *arg1, int rgp_a2)
{ RG_VU0_FRAME;
    u8 sp70[0x10] __attribute__((aligned(16)));
    u8 sp60[0x10] __attribute__((aligned(16)));
    u8 sp50[0x10] __attribute__((aligned(16)));
    u8 sp40[0x10] __attribute__((aligned(16)));
    u8 *p;
    s32 x;
    f32 temp_f20;
    f32 temp_f20_2;

    JudgeObjectOnMapHit_3141f0((void *)arg0, (int)arg1, (int)rgp_a2);
    if ((*(s32 *)((u8 *)arg0 + 0x80) & 4) && (*(s32 *)((u8 *)arg0 + 0x7C) & 8)) {
        VecLinearCombine_1cb8b0(sp70, (u8 *)arg0 + 0x1B0, (u8 *)arg0 + 0x1A0, D_0047D274 * *(f32 *)((u8 *)arg1 + 0x28), 1.0f);
        *(f32 *)(sp70 + 4) += 1.0f;
        x = GameSceneSoundSlot1GetHandle_1d07b0(GetCurrentScene_1f5be0());
        SoundPlayScaledVolume_1b9520(x, 0x3A, 0, 1.0f);
        EffectSpawnWaterSplash_2d8400(*(s16 *)((u8 *)arg0 + 0x86), sp70);
        *(f32 *)((u8 *)arg0 + 0xCC) = 30.0f;
    }
    if (*(s32 *)((u8 *)arg0 + 0x80) & 1) {
        VecLinearCombine_1cb8b0((u8 *)arg0 + 0x180, (u8 *)arg0 + 0x1B0, (u8 *)arg0 + 0x1A0, D_0047D274 * *(f32 *)((u8 *)arg1 + 0x2C), 1.0f);
        temp_f20 = D_0047D1DC + *(f32 *)((u8 *)arg0 + 0x190);
        VecSub_13be40(sp60, (u8 *)arg0 + 0x180, (u8 *)arg1 + 0x30);
        if (VecLengthSq_1cb470(sp60, 0) <= (temp_f20 * temp_f20)) {
            p = sp60;
            VecScaleToLength_1cb510(p, p, temp_f20);
            VecAdd_13be20((u8 *)arg0 + 0x180, (u8 *)arg1 + 0x30, sp60);
        }
        VecScale_13be00(sp50, (u8 *)arg1 + 0x40, Vu0InnerProduct_13d300((u8 *)arg0 + 0x1B0, (u8 *)arg1 + 0x40) / VecLengthSq_13d440((u8 *)arg1 + 0x40));
        VecSub_1cbd00(sp40, (u8 *)arg0 + 0x1B0, sp50);
        VecLinearCombine_1cb8b0((u8 *)arg0 + 0x1B0, sp40, sp50, D_0047D27C, -(*(f32 *)((u8 *)arg0 + 0x1C8)));
    }
}

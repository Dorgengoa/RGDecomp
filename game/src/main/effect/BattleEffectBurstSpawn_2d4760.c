/* rgp:protos */
#define RGP_SELF_BattleEffectBurstSpawn_2d4760 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern f32 D_0047D278 __attribute__((section(".sdata")));
extern f32 D_0047D1E0 __attribute__((section(".sdata")));
extern f32 D_0047D1E8 __attribute__((section(".sdata")));


/*rgp*/
/*rgp*/
/*rgp*/

void BattleEffectBurstSpawn_2d4760(void *p, void *src)
{
    u8 *q;
    u8 *r;
    s32 i;
    s32 j;

    q = (u8 *)p;
    sceVu0CopyVector(q + 0x10, src);
    for (i = 0; i < 0x40; i++) {
        *(q + i * 0x40 + 0x54) = 0;
    }
    *(s32 *)(q + 0x00) = 1;
    *(q + 0x54) = 1;
    *(s32 *)(q + 0x58) = 0;
    *(f32 *)(q + 0x44) = D_0047D278;
    *(f32 *)(q + 0x50) = D_0047D1E0;
    sceVu0CopyVector(q + 0x20, q + 0x10);
    *(q + 0x94) = 1;
    *(s32 *)(q + 0x98) = 1;
    *(f32 *)(q + 0x84) = 3.0f;
    *(f32 *)(q + 0x90) = 1.0f;
    sceVu0CopyVector(q + 0x60, q + 0x10);
    *(q + 0xD4) = 1;
    *(s32 *)(q + 0xD8) = 2;
    *(f32 *)(q + 0xC4) = 2.0f;
    *(f32 *)(q + 0xD0) = 1.0f;
    sceVu0CopyVector(q + 0xA0, q + 0x10);
    *(q + 0x114) = 1;
    *(s32 *)(q + 0x118) = 4;
    *(f32 *)(q + 0x104) = 2.0f;
    *(f32 *)(q + 0x110) = D_0047D1E8;
    sceVu0CopyVector(q + 0xE0, q + 0x10);
    for (j = 0; j < 0x10; j++) {
        r = q + j * 0x40;
        *(r + 0x154) = 1;
        *(s32 *)(r + 0x158) = 3;
        *(f32 *)(r + 0x144) = 2.0f;
        *(f32 *)(r + 0x150) = 1.0f;
        *(f32 *)(r + 0x140) = RandRangeFloat_1ca5d0(2.0f);
        sceVu0CopyVector(q + (j + 3) * 0x40 + 0x20, q + 0x10);
        *(f32 *)(r + 0x130) = RandRangeFloat_1ca5d0(10.0f) - 5.0f;
        *(f32 *)(r + 0x134) = RandRangeFloat_1ca5d0(10.0f) - 5.0f;
        *(f32 *)(r + 0x138) = RandRangeFloat_1ca5d0(10.0f) - 5.0f;
        *(f32 *)(r + 0x13C) = 1.0f;
        VecNormalize_13bd90(q + (j + 4) * 0x40 + 0x30, q + (j + 4) * 0x40 + 0x30);
    }
}

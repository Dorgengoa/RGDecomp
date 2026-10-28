/* rgp:protos */
#define RGP_SELF_CharaUpdateLocomotionMotionMaybe_21c970 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off
#pragma opt_unroll_loops off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D94C;
extern f32 D_0047DB54;

void CharaUpdateLocomotionMotionMaybe_21c970(u8 *arg0)
{
    char buf[0x20] __attribute__((aligned(16)));
    f32 d;
    f32 r;
    s32 k;
    s32 n;
    char *p;
    u32 cnt;

    if (!(*(s32 *)(arg0 + 0xA44) & 0x1000000)) {
        return;
    }
    if (*(s32 *)(arg0 + 0x3F4) == 0) {
        return;
    }
    if (*(u8 **)(arg0 + 0x42C) == 0) {
        return;
    }
    n = *(s16 *)(arg0 + 0xA34);
    if (n != 2 && n != 1) {
        return;
    }
    if (*(f32 *)(arg0 + 0xAD0) < 5.0f) {
        return;
    }
    d = VecDistSqXZ_1cb390(arg0 + 0x70, arg0 + 0x20);
    { f32 t = *(f32 *)(*(u8 **)(arg0 + 0x42C) + 0xC); r = 0.25f * t; }
    k = 0;
    if (!(d <= r * r)) {
        k = *(s16 *)(arg0 + 0xA34);
    }
    if (k == 0) {
        n = *(s16 *)(arg0 + 0xA2E);
        if (n == 0) {
            goto chk;
        }
        if (n == 1) {
        chk:
            if (!(d <= D_0047DB54)) {
                k = 1;
            }
        }
    }
    if (k == 1) {
        n = *(s16 *)(arg0 + 0xA2E);
        if (n == 2) {
            goto set2;
        }
        if (n == 3) {
        set2:
            k = 2;
        }
    }
    p = buf;
    cnt = 0x20;
    if (p != 0) {
        do {
            *p = 0;
            cnt--;
            p++;
        } while (cnt != 0);
    }
    switch (k) {
    case 0:
        ActCfgTableGetStandMotionName_21f590(*(s32 *)(arg0 + 0x428), buf, *(s16 *)(arg0 + 0xA2E));
        if (((unsigned char)StrEqualNonNull_1ca6c0(buf, ModelObjGetMotionName_1add90(*(s32 *)(arg0 + 0x3F4)))) != 0) {
            return;
        }
        if (CharaIsPlayedMotion_2124f0(arg0, buf) != 0) {
            return;
        }
        CharaPlayMotion_212590(arg0, *(s32 *)(arg0 + 0x3F4), buf, 0, D_0047D94C);
        *(f32 *)(arg0 + 0xAD0) = 0.0f;
        { f32 x = RandFloat_13c010(); *(f32 *)(arg0 + 0xAD8) = 150.0f * x + 150.0f; }
        break;
    case 2:
        ActCfgTableGetRunMotionName_21f570(*(s32 *)(arg0 + 0x428), buf, *(s16 *)(arg0 + 0xA2E));
        if (((unsigned char)StrEqualNonNull_1ca6c0(buf, ModelObjGetMotionName_1add90(*(s32 *)(arg0 + 0x3F4)))) != 0) {
            return;
        }
        if (CharaIsPlayedMotion_2124f0(arg0, buf) != 0) {
            return;
        }
        CharaPlayMotion_212590(arg0, *(s32 *)(arg0 + 0x3F4), buf, 0, D_0047D94C);
        *(f32 *)(arg0 + 0xAD0) = 0.0f;
        break;
    case 1:
        ActCfgTableGetWalkMotionName_21f550(*(s32 *)(arg0 + 0x428), buf, *(s16 *)(arg0 + 0xA2E));
        if (((unsigned char)StrEqualNonNull_1ca6c0(buf, ModelObjGetMotionName_1add90(*(s32 *)(arg0 + 0x3F4)))) != 0) {
            return;
        }
        if (CharaIsPlayedMotion_2124f0(arg0, buf) != 0) {
            return;
        }
        CharaPlayMotion_212590(arg0, *(s32 *)(arg0 + 0x3F4), buf, 0, D_0047D94C);
        *(f32 *)(arg0 + 0xAD0) = 0.0f;
        break;
    }
}

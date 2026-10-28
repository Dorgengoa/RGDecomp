/* rgp:protos */
#define RGP_SELF_Character2Draw_1ae920 1
#include "port/game_protos.h"
#line 1
/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/Character2Draw_1ae920.s and build/b_drafts/Character2Draw_1ae920.txt
   (m2c draft already generated, just not worked). */
/* s49m: MATCH */
#include "types.h"

typedef rg_u128 u128;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { u128 q[4]; } M4;

typedef struct Req {
    s32 a;
    s32 b;
    u8 pad8[0xC8];
    u128 posD0;
    u8 padE0[0xC0];
} Req;

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

s32 Character2Draw_1ae920(u8 *o)
{
    Req sp80 __attribute__((aligned(16)));
    V4 sp70 __attribute__((aligned(16)));
    V4 sp60 __attribute__((aligned(16)));
    s32 h;
    s32 s;
    s32 i;
    s32 r;
    f32 f;

    h = GetDrawCtx_15de80();
    sp80.b = 0;
    sp80.a = -1;
    LightStateInit_156b50(&sp80);
    s = ((s32)LightStatePush_1429f0(h, &sp80, 1));
    if (*(s32 *)(o + 0x778) > 0) {
        for (i = 0; i < 4; i++) {
            u8 *p = o + i * 16;
            VecAdd_13be20(p + 0x630, p + 0x630, p + 0x670);
            VecAdd_13be20(p + 0x6F0, p + 0x6F0, p + 0x730);
        }
        VecAdd_13be20(o + 0x5A0, o + 0x5A0, o + 0x5B0);
        VecAdd_13be20(o + 0x5D0, o + 0x5D0, o + 0x5E0);
        *(s32 *)(o + 0x778) -= 1;
    } else {
        *(s32 *)(o + 0x778) = 0;
        ((u128 *)(o + 0x630))[0] = ((u128 *)(o + 0x5F0))[0];
        ((u128 *)(o + 0x630))[1] = ((u128 *)(o + 0x5F0))[1];
        ((u128 *)(o + 0x630))[2] = ((u128 *)(o + 0x5F0))[2];
        ((u128 *)(o + 0x630))[3] = ((u128 *)(o + 0x5F0))[3];
        ((u128 *)(o + 0x6F0))[0] = ((u128 *)(o + 0x6B0))[0];
        ((u128 *)(o + 0x6F0))[1] = ((u128 *)(o + 0x6B0))[1];
        ((u128 *)(o + 0x6F0))[2] = ((u128 *)(o + 0x6B0))[2];
        ((u128 *)(o + 0x6F0))[3] = ((u128 *)(o + 0x6B0))[3];
        sceVu0CopyVector(o + 0x5A0, o + 0x590);
        sceVu0CopyVector(o + 0x5D0, o + 0x5C0);
    }
    if (*(s32 *)(o + 0x778) > 0 || *(s32 *)(o + 0x774) >= 10) {
        LightStateSetMatrices_15cc00(o + 0x630, o + 0x6F0);
        if (*(s32 *)(o + 0x788) == 0) {
            sp80.posD0 = *(u128 *)(o + 0x5D0);
        }
        if (*(s32 *)(o + 0x780) == 0) {
            f = *(f32 *)(o + 0x784);
            if (!(f <= 0.0f)) {
                if (!(f <= 1.0f)) {
                    *(f32 *)(o + 0x784) = 1.0f;
                }
                LightStateGetAmbient_15cb10(&sp70);
                VecScale_13be00(&sp70, &sp70, *(f32 *)(o + 0x784));
                VecScale_13be00(&sp60, o + 0x5A0, 1.0f - *(f32 *)(o + 0x784));
                VecAdd_13be20(&sp70, &sp70, &sp60);
                LightStateSetAmbient_15cb30(&sp70);
            } else {
                LightStateSetAmbient_15cb30(o + 0x5A0);
            }
        }
    }
    DrawListAddLightPacket_148120(h);
    r = ModelObjExDraw_1ad7a0(o, 0, 0, 0);
    *(s32 *)(o + 0x780) -= 1;
    *(f32 *)(o + 0x784) = 0.0f;
    if (*(s32 *)(o + 0x780) < 0) {
        *(s32 *)(o + 0x780) = 0;
    }
    LightStateSetCurrent_142920(h, s);
    return r;
}

/* rgp:protos */
#define RGP_SELF_MotionEventSePlay_1b1250 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045A9A8[];

s32 MotionEventSePlay_1b1250(void *arg0, void *arg1, s32 arg2) {
    volatile s32 sp7C;
    s32 p;
    s32 sum;
    f32 f21;
    f32 f20;
    u8 *q;
    u8 *name;
    s32 v;
    s32 n;
    s32 t;

    p = *(s32 *)((u8 *)arg0 + 4);
    if (p == 0) {
        return 0;
    }
    name = (u8 *)arg1 + 0x30;
    if (name == NULL) {
        p = -1;
    } else if (*(s8 *)((u8 *)arg1 + 0x30) == 0x2D) {
        p = -1;
    } else {
            v = SoundBankIdFromPrefix_1baa40(name);
            if (v >= 0) {
                p = v;
            } else {
                p = *(s32 *)((u8 *)p + 0x4FC);
            }
    }
    q = *(u8 **)((u8 *)arg0 + 4);
    t = *(s32 *)(q + 0x534);
    sum = *(s32 *)((u8 *)arg1 + 0x28) + t;
    f21 = *(f32 *)(q + 0x508);
    f20 = *(f32 *)(q + 0x50C);
    if (*(s8 *)((u8 *)arg1 + 0x30) == 0x2D && Strncasecmp_134ce8((u8 *)arg1 + 0x30, D_0045A9A8, 2) == 0) {
        t = *(s32 *)((u8 *)arg1 + 0x28);
        q = *(u8 **)((u8 *)arg0 + 4);
        n = *(s32 *)(q + 0x554);
        sp7C = t;
        if (n < 4) {
            
            *(s32 *)(q + 0x554) = n + 1;
            *(s32 *)(q + n * 4 + 0x558) = t;
        }
        return 1;
    }
    if (arg2 == 0) {
        SoundPlayScaledVolPan_1b9680(p, sum, SoundNextPlayHandle_1b81c0(), f21, f20);
    } else if (*(s32 *)(*(u8 **)((u8 *)arg0 + 4) + 0x518) != 0) {
        t = sum % 31 + 1;
        *(s32 *)((u8 *)arg1 + 0x2C) = t;
        SoundNoteListPush_1b4cd0(*(s32 *)(*(u8 **)((u8 *)arg0 + 4) + 0x518), p, sum, 3, t, f21, f20);
    }
    return 1;
}

#include "types.h"
#pragma opt_propagation off

typedef struct Inner001b0dc0 {
    u8 pad0[0x53C];
    u8 *unk53C;
} Inner001b0dc0;

typedef struct A0_001b0dc0 {
    u8 pad0[4];
    Inner001b0dc0 *unk4;
} A0_001b0dc0;

typedef struct A1_001b0dc0 {
    u8 pad0[0x28];
    s32 unk28;
    u8 pad2C[4];
    volatile s32 unk30;
} A1_001b0dc0;

extern f32 EffDefGetDurationByHandle_1a0a50(u8 *, s32);
extern void EffInstStop_1a0db0(u8 *, s32);
extern void EffInstSetAutoDestroy_1a0dd0(u8 *, s32);
extern void MotionEventEffectSpawn_1b0e90(s32 *, Inner001b0dc0 *, A1_001b0dc0 *);
extern void StrMapGetValue_1b13e0(s32 *, u8 *, s32);

s32 MotionEventEffectFire_1b0dc0(A0_001b0dc0 *arg0, A1_001b0dc0 *arg1) {
    s32 sp3C;
    s32 sp38;
    u8 *t;
    s32 b;

    if (arg0->unk4 == NULL) {
        return 0;
    }
    MotionEventEffectSpawn_1b0e90(&sp3C, arg0->unk4, arg1);
    t = arg0->unk4->unk53C;
    if (t != NULL) {
        StrMapGetValue_1b13e0(&sp38, t + 0xB0, arg1->unk28);
        if (EffDefGetDurationByHandle_1a0a50(t, sp38) >= 0.0f) {
            EffInstSetAutoDestroy_1a0dd0(t, sp3C);
            arg1->unk30 = 0;
        } else {
            b = (arg1->unk30 != 0) ^ 1;
            if (!b) {
                EffInstStop_1a0db0(t, arg1->unk30);
            }
            arg1->unk30 = sp3C;
        }
    }
    return 1;
}

#include "types.h"

typedef struct {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
} BF;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
    u8 pad10[0x409 - 0x10];
    BF f;
} O;

extern s32 GetStatusEffect_2d9010(void);
extern void StatusEffectStart_33c240(s32, s32, s32, s32);

s32 UnitOnAppearStartStatusFx_3bce00(O *arg0) {
    s32 r;

    if (arg0->f.b6) {
        return 0;
    }
    arg0->f.b6 = 1;
    r = GetStatusEffect_2d9010();
    if (arg0->f.b2) {
        if (r != 0) {
            StatusEffectStart_33c240(r, 0xB, arg0->unkC, -1);
        }
    }
    if (arg0->f.b3) {
        if (r != 0) {
            StatusEffectStart_33c240(r, 0xA, arg0->unkC, -1);
        }
    }
    return 1;
}

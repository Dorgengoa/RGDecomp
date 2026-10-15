#include "types.h"

struct S003bd990 {
    u8 pad0[0xC];
    s32 fC;
    u8 pad10[0x3F9];
    u8 f409_0 : 2;
    u8 bit3 : 1;
    u8 f409_4 : 5;
};

extern void *GetStatusEffect_2d9010(void);
extern void StatusEffectStart_33c240(void *r, s32 a, s32 b, s32 c);
extern void StatusEffectStopMatching_33c1c0(void *r, s32 a, s32 b);

void UnitSetStatusFxFlagA_3bd990(struct S003bd990 *p0, u8 flag, s32 force)
{
    void *r;

    if (p0->bit3 == flag && force == 0) {
        return;
    }
    p0->bit3 = flag;
    r = GetStatusEffect_2d9010();
    if (r == 0) {
        return;
    }
    if (p0->bit3 != 0) {
        StatusEffectStart_33c240(r, 0xB, p0->fC, -1);
    } else {
        StatusEffectStopMatching_33c1c0(r, 0xB, p0->fC);
    }
}

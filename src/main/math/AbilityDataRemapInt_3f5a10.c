#include "types.h"

extern s32 AbilityDataGetRemapOutLo_3f5be0(s32 p0);
extern s32 AbilityDataGetRemapOutHi_3f5bb0(s32 p0);
extern s32 AbilityDataGetRemapInLo_3f5b80(s32 p0);
extern s32 AbilityDataGetRemapInHi_3f5b50(s32 p0);

extern f32 D_0047D258;

s32 AbilityDataRemapInt_3f5a10(s32 a0, s32 a1, s32 a2)
{
    s32 lo1, val1, d1;
    s32 lo2, val2, d2;
    f32 ratio;
    s32 result;

    lo1 = AbilityDataGetRemapOutLo_3f5be0(a0);
    val1 = AbilityDataGetRemapOutHi_3f5bb0(a0);
    if (val1 < lo1) {
        val1 = lo1;
    }
    d1 = val1 - lo1;

    lo2 = AbilityDataGetRemapInLo_3f5b80(a0);
    val2 = AbilityDataGetRemapInHi_3f5b50(a0);
    if (val2 < lo2) {
        val2 = lo2;
    }
    d2 = val2 - lo2;

    ratio = 0.0f;
    if (d2 > 0) {
        ratio = (f32)d1 / (f32)d2;
    }

    if (a1 < lo2) {
        a1 = lo2;
    } else if (val2 < a1) {
        a1 = val2;
    }
    result = a1 - lo2;

    return lo1 + (s32)(D_0047D258 + ratio * (f32)result) - (-a2);
}

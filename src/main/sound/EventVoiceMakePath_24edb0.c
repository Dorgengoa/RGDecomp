#include "types.h"

#pragma divbyzerocheck on

extern void Sprintf_1343b8(void *dst, const void *fmt, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void PathLocalize_1c28c0(s32 ctx, void *buf);
extern const u8 D_0045EC50[];

void EventVoiceMakePath_24edb0(s32 dummy0, s32 arg1, s32 arg2)
{
    u8 sp20[0x80];
    s32 hi;
    s32 lo;

    hi = arg1 / 100000000;
    lo = (arg1 - hi * 100000000) / 10000;
    Sprintf_1343b8(sp20, D_0045EC50, hi, lo, hi, lo, arg1 % 10000);
    PathLocalize_1c28c0(arg2, sp20);
}

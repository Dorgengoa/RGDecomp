#pragma warn_illpragma on
#pragma opt_unpromotetypes on
#include "types.h"

s32 AreaBoxContainsPointXZ_1e9310(void *arg0, void *arg1, f32 r)
{
    f32 t0;
    f32 t1;
    f32 x;
    f32 z;
    f32 n;
    f32 y;

    x = *(f32 *)((u8 *)arg1 + 0x0) - *(f32 *)((u8 *)arg0 + 0x28);
    z = *(f32 *)((u8 *)arg1 + 0x8) - *(f32 *)((u8 *)arg0 + 0x30);
    y = 0.0f;
    t1 = x * *(f32 *)((u8 *)arg0 + 0x3C) + z * *(f32 *)((u8 *)arg0 + 0x40);
    t0 = *(f32 *)((u8 *)arg0 + 0x24) + r;
    if (t1 > t0) return 0;
    n = -t0;
    if (t1 < n) return 0;
    t1 = x * *(f32 *)((u8 *)arg0 + 0x34) + y * 0.0f + z * *(f32 *)((u8 *)arg0 + 0x38);
    t0 = *(f32 *)((u8 *)arg0 + 0x1C) + r;
    if (t1 > t0) return 0;
    n = -t0;
    if (t1 < n) return 0;
    return 1;
}

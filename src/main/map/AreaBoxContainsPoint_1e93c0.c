#pragma warn_illpragma on
#pragma opt_unpromotetypes on
#include "types.h"

s32 AreaBoxContainsPoint_1e93c0(void *arg0, void *arg1, f32 r)
{
    f32 t0;
    f32 t1;
    f32 x;
    f32 z;
    f32 n;

    t1 = *(f32 *)((u8 *)arg1 + 0x4) - *(f32 *)((u8 *)arg0 + 0x2C);
    t0 = *(f32 *)((u8 *)arg0 + 0x20) + r;
    if (t1 > t0) return 0;
    n = -t0;
    if (t1 < n) return 0;
    x = *(f32 *)((u8 *)arg1 + 0x0) - *(f32 *)((u8 *)arg0 + 0x28);
    z = *(f32 *)((u8 *)arg1 + 0x8) - *(f32 *)((u8 *)arg0 + 0x30);
    t1 = x * *(f32 *)((u8 *)arg0 + 0x3C) + z * *(f32 *)((u8 *)arg0 + 0x40);
    t0 = *(f32 *)((u8 *)arg0 + 0x24) + r;
    if (t1 > t0) return 0;
    n = -t0;
    if (t1 < n) return 0;
    t1 = x * *(f32 *)((u8 *)arg0 + 0x34) + z * *(f32 *)((u8 *)arg0 + 0x38);
    t0 = *(f32 *)((u8 *)arg0 + 0x1C) + r;
    if (t1 > t0) return 0;
    n = -t0;
    if (t1 < n) return 0;
    return 1;
}

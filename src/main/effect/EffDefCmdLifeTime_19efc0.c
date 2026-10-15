#include "types.h"

/* The first block re-stores 0x28 and 0x34 with the values they already hold:
   the loads of both fields are scheduled ahead of the stores, which is what
   the lwc1 $f2,0x34 / lwc1 $f0,0x28 / swc1 $f0,0x28 sequence is. */

extern f32 VariantGetFloat_15f740(void *);

s32 EffDefCmdLifeTime_19efc0(u8 *args, s32 n, void **ctx)
{
    u8 *o = (u8 *)ctx[0];
    u8 *y;
    f32 a;
    f32 b;
    f32 c;
    f32 keep;

    if (*(void **)(o + 0x28) == 0) {
        return 0;
    }
    a = VariantGetFloat_15f740(args);
    y = *(u8 **)(o + 0x28);
    *(f32 *)(y + 0x24) = a;
    keep = *(f32 *)(y + 0x34);
    *(f32 *)(y + 0x28) = *(f32 *)(y + 0x28);
    *(f32 *)(y + 0x2C) = *(f32 *)(y + 0x24) + *(f32 *)(y + 0x28);
    *(f32 *)(y + 0x34) = keep;
    b = VariantGetFloat_15f740(args + 8);
    c = 0.0f;
    if (n >= 2) {
        c = VariantGetFloat_15f740(args + 0x10);
    }
    y = *(u8 **)(o + 0x28);
    *(f32 *)(y + 0x28) = b;
    *(f32 *)(y + 0x2C) = *(f32 *)(y + 0x24) + *(f32 *)(y + 0x28);
    *(f32 *)(y + 0x34) = c;
    return 1;
}
